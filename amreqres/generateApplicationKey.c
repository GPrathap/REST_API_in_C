#include <stdio.h>
#include <curl/curl.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>


#include "../json/json.h"
#include "../json/buf/buf.h"
#include "../json/jsmn/jsmn.h"
#include "../curl/curlreq.h"

char *generateApplicationKey(char* reqbody);
struct response_data *generateApplicationKeyRequest(char* reqbody,char* cookie,int memorySize,char* url);
char* generateApplicationKeyResponse(char* res,char* cookie,struct keyValue_struct** list);
char* databaseHandler(struct keyValue_struct** list,char* username);



int main()
{

            printf("Content-type: text/html\n\n");
    //POST is the only allowed method
            if(strcmp(getenv("REQUEST_METHOD"),"GET")==0)
            {
                            printf("<H3>Page is not found</h3>\n");
                            return 0;
            }

           // char *s=getenv("CONTENT_LENGTH");
            int i=atoi(getenv("CONTENT_LENGTH"));
            //printf("%s\n<br />",s); //Shows you CONTENT_LENGTH works
            //printf("%d\n<br />",i); //Shows you it was converted to int
            char *tmp;
    //allocate memory for request body
            tmp=malloc(i+20);
    //read post request data from stdin
            int lenOfRead=fread(tmp,i,1,stdin); //read from stdin something of i bytes to tmp
            if(lenOfRead==0){
                printf("Post request is empty\n");
            }
    //execute a process to handle request to backend server
            char* statusgenerateApplicationKey=generateApplicationKey(tmp);
            if(statusgenerateApplicationKey==NULL){

                printf("Some thing wrong with your response\n");

            }else{

                printf("%s\n",statusgenerateApplicationKey);

            }

    return 0;
}

char *generateApplicationKey(char* reqbody)
{
    //pointer to the repose data struct
         struct keyValue_struct *reqData = NULL;
         struct keyValue_struct *resData = NULL;
    //add request body data into hashmap
         add_toList(&reqData,reqbody,'&','=');
    //get username of user form hashmap
         struct keyValue_struct *username=getValue("username",&reqData);
    //get previous cookie value from database
         char* cookie=getPreviousCookieValue(username->value,"USER");
         if(cookie==NULL)
         {
                printf("You have not been signed up yet\n");
                return NULL;
         }
    //make request to backend server
         struct response_data *res_data=generateApplicationKeyRequest(reqbody,cookie,1000,"http://localhost:9763/store/site/blocks/subscription/subscription-add/ajax/subscription-add.jag");

         if(res_data==NULL)
         {

            printf("Backend server is down try again later (:\n");
            return NULL;

         }
    //if response is present analyze response data
         char* clientRes=generateApplicationKeyResponse(res_data->res_body,res_data->res_cookie,&resData);
         if(clientRes==NULL)
         {

            printf("Interanl server error (:\n");
            return NULL;

         }
    //finally save accesstoken and some importance stuff in database
         char* dbstatus=databaseHandler(&resData,username->value);

         if(dbstatus==NULL)
         {
              return NULL;
         }


         return "Generating an application key is done done successfully \n";

}







char* generateApplicationKeyResponse(char* rest,char* cookie,struct keyValue_struct** list)
{


     //struct keyValue_struct *users = NULL;
     //char* temp1=str_replace(rest,"{","");
     //char* temp2=str_replace(temp1,"}","");
     //char* res1=str_replace(rest,"\"","");
     //add_toList(&users,res,',',':');
    //create hashmap using response of backend server
     addToListFromJSONGenerateKey(rest,list);
    //add new cookie value to database
     add_item("cookie",cookie,list);
    //get the error value
     struct keyValue_struct *s=getValue("error",list);
     char buffer[100];
     strcpy(buffer,s->value);
    //remove unwanted spaces
     char* value=str_trim(buffer);

     if(strcmp(value,"false")!=0){

         struct keyValue_struct *msg=getValue("message",list);

         printf("generateApplicationKey error : %s\n", msg->value);
         return NULL;

     }else{


        return "Ok";

     }

}
char* databaseHandler(struct keyValue_struct** list,char* username)
{
    //pointer to the database
        sqlite3 *db=NULL;
    //pointer to the error message
        char *errmsg = 0;
    //sql string
        const char *sql;
        const char* data = "Callback function called\n";



    //trying to connect to database
        int status=connectToDatabase(&db);

        if(status==0)
        {
            return NULL;
        }

    //get consumer key, access token and consumersecret from database and send it to client
        struct keyValue_struct *consumerKey=getValue("consumerKey",list);
        struct keyValue_struct *accessToken=getValue("accessToken",list);
        struct keyValue_struct *consumerSecret=getValue("consumerSecret",list);

    //update user subscription details
        sql=updateSubscriptionDetails(consumerKey->value,accessToken->value,consumerSecret->value,username);
        status=executeSQLStatement(&db,sql,(void*)data,&errmsg,"Operation done successfully\n",callbackSelect);

        if(status==0)
        {
            return NULL;
        }
    //finally close the database connection
        sqlite3_close(db);

        return "Ok";
}

struct response_data *generateApplicationKeyRequest(char* reqbody,char* cookie,int memorySize,char* url)
{
         return makeCURLRequest(reqbody,cookie,memorySize,url);
}
