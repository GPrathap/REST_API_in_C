

#include <stdio.h>
#include <curl/curl.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

#include "../curl/curlreq.h"
#include "../json/json.h"
#include "../json/buf/buf.h"
#include "../json/jsmn/jsmn.h"

char *addSubscription(char* reqbody);
struct response_data *addSubscriptionRequest(char* reqbody,char* cookie,int memorySize,char* url);
char* addSubscriptionResponse(char* res);
char* databaseHandler(char* reqbody,char* cookie);



int main()
{

            printf("Content-type: text/html\n\n");
    //only allowed post request only 
            if(strcmp(getenv("REQUEST_METHOD"),"GET")==0){
                            printf("<H3>Page is not found</h3>\n");
                            return 0;
            }

            //char *s=getenv("CONTENT_LENGTH");
            int i=atoi(getenv("CONTENT_LENGTH"));

           //printf("%s\n<br />",s); //Shows you CONTENT_LENGTH works
            //printf("%d\n<br />",i); //Shows you it was converted to int
            char *tmp;
    //allocate memory for request body data
            tmp=malloc(i+20);
    //read from stdin something of i bytes to tmp
           int lenOfRead=fread(tmp,i,1,stdin);
           if(lenOfRead==0){
                printf("Post request is empty\n");
            }

    //execute process to handle request to backend server
            char* statusaddSubscription=addSubscription(tmp);
            if(statusaddSubscription==NULL){

                printf("Some thing wrong with the response of backend server \n");

            }else{

                printf("%s\n",statusaddSubscription);

            }
    return 0;
}

char *addSubscription(char* reqbody)
{
    //request data struct
         struct keyValue_struct *reqData = NULL;
    //add request data into hasmap for later usage
         add_toList(&reqData,reqbody,'&','=');
    //get the username of the cilent
         struct keyValue_struct *username=getValue("username",&reqData);
    //get the privioes cookie value if it is existed  
         char* cookie=getPreviousCookieValue(username->value,"USER");
         if(cookie==NULL){
                printf("You have not been  signed up yet\n");
                return NULL;
         }

    //Now make request to backend server 
         struct response_data *res_data=addSubscriptionRequest(reqbody,cookie,4096,"http://localhost:9763/store/site/blocks/subscription/subscription-add/ajax/subscription-add.jag");
         if(res_data==NULL){

            printf("Backend server is down try again later (:\n");
            return NULL;

         }
    //If response is there, to  handle the response 
         char* clientRes=addSubscriptionResponse(res_data->res_body);
         if(clientRes==NULL)
         {

            printf("Interanl server error (:\n");
            return NULL;

         }
    //finally call the database handle to save the new cookie value of user
         char* dbstatus=databaseHandler(reqbody,res_data->res_cookie);

         if(dbstatus==NULL)
         {
              return NULL;
         }


         return "Your subscription is accepted successfully\n";

}







char* addSubscriptionResponse(char* rest)
{
    //hashmap to pointer
    struct keyValue_struct *users = NULL;
    // char* temp1=str_replace(rest,"{","");
    // char* temp2=str_replace(temp1,"}","");
    // char* res=str_replace(temp2,"\"","");
    // add_toList(&users,res,',',':');*/
    //filter the repose data into hashmap 
     addToListFromJSON(rest,&users);
    //get error value from hashmap 
     struct keyValue_struct *s=getValue("error",&users);
     char buffer[100];
     strcpy(buffer,s->value);
    //remove unwanted spaces 
     char* value=str_trim(buffer);
    //if there is an error has happened in backed server 
     if(strcmp(value,"false")!=0){

         struct keyValue_struct *msg=getValue("message",&users);
         //fprintf(stderr, "addSubscription error : %s\n", msg->value);
         printf("addSubscription error : %s\n", msg->value);
         return NULL;

     }else{


        return "Ok";

     }

}
char* databaseHandler(char* username,char* cookie)
{
    //pointer  to database 
        sqlite3 *db=NULL;
    //pointer to an  error message
        char *errmsg = 0;
    //sql query string
        const char *sql;
        const char* data = "Callback function called\n";
    //try to connect to database
        int status=connectToDatabase(&db);

        if(status==0)
        {
            return NULL;
        }
    //Update user cookie value 
        sql=updateLogin(cookie,username);
        //sql=createUserTable();
        status=executeSQLStatement(&db,sql,(void*)data,&errmsg,"Operation done successfully\n",callbackSelect);

        if(status==0)
        {
            return NULL;
        }
    //close the database connection
        sqlite3_close(db);

        return "Ok";
}

struct response_data *addSubscriptionRequest(char* reqbody,char* cookie,int memorySize,char* url)
{

    return makeCURLRequest(reqbody,cookie,memorySize,url);

}
