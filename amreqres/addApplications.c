#include <stdio.h>
#include <curl/curl.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

#include "../curl/curlreq.h"


char *addApplication(char* reqbody);
struct response_data *addApplicationRequest(char* reqbody,char* cookie,int memorySize,char* url);
char* addApplicationResponse(char* res);
char* databaseHandler(char* username,char* cookie);

int main()
{

            printf("Content-type: text/html\n\n");
            if(strcmp(getenv("REQUEST_METHOD"),"GET")==0){
                            printf("<H3>Page is not found</h3>\n");
                            return 0;
            }
            //char *s=getenv("CONTENT_LENGTH");
            int i=atoi(getenv("CONTENT_LENGTH"));

            //printf("%s\n<br />",s); //shows you CONTENT_LENGTH works
            //printf("%d\n<br />",i); //shows you it was converted to int
            char *requestBody;
            requestBody=malloc(i+20);
            //read from stdin something of i bytes to requestBody
            int lenOfRead=fread(requestBody,i,1,stdin);
            if(lenOfRead==0){
                printf("Post request is empty\n");
            }

            char* statusaddApplication=addApplication(requestBody);
            if(statusaddApplication==NULL){
                printf("Something wrong with the response of backend server\n");
            }else{
                printf("%s\n",statusaddApplication);
            }

    return 0;
}
//Forward request to backend server get the response back and forward to where it came
char *addApplication(char* reqbody)
{
        //request body data
         struct keyValue_struct *reqData = NULL;
         //split request body data into key and value and add it to hasmap to latter usage
         add_toList(&reqData,reqbody,'&','=');
         //username of the client
         struct keyValue_struct *username=getValue("username",&reqData);
         //get the previous cookie value from database and set it into next upcoming request.
         char* cookie=getPreviousCookieValue(username->value,"USER");
         if(cookie==NULL){
                printf("You have not been  signed up yet\n");
                return NULL;
         }
         struct response_data *res_data=addApplicationRequest(reqbody,cookie,1200,"http://localhost:9763/store/site/blocks/application/application-add/ajax/application-add.jag");
         if(res_data==NULL){

            printf("Backend server is down try again later (:\n");
            return NULL;

         }
         //if there is a response from back end server it is handled by this function
         char* clientRes=addApplicationResponse(res_data->res_body);
         //something went wrong in server itself may be database access error or something which is not expected
         if(clientRes==NULL)
         {

            printf("Internal server error (:\n");
            return NULL;

         }

         char* dbstatus=databaseHandler(reqbody,res_data->res_cookie);

         if(dbstatus==NULL)
         {
              return NULL;
         }


         return "Application is added\n";

}


char* addApplicationResponse(char* rest)
{


    //response is a json object so to get content
     struct keyValue_struct *users = NULL;
     char* temp1=str_replace(rest,"{","");
     char* temp2=str_replace(temp1,"}","");
     char* res=str_replace(temp2,"\"","");

    //then add into hashmap as key and value for latter usage
     add_toList(&users,res,',',':');

    //getting error message from server
     struct keyValue_struct *s=getValue("error",&users);
    //remove unwanted spaces
     char buffer[100];
     strcpy(buffer,s->value);
     char* value=str_trim(buffer);

    //if there is an error in response
     if(strcmp(value,"false")!=0){

    //send the error message to client
         struct keyValue_struct *msg=getValue("message",&users);
           printf("addApplication error : %s\n", msg->value);
         return NULL;

     }else{

            return "Ok";

     }

}
char* databaseHandler(char* username,char* cookie)
{
        //pointer to database
        sqlite3 *db=NULL;
        // get error message
        char *errmsg = 0;
        //sql string
        const char *sql;
        const char* data = "Callback function called\n";
        //connect to the database
        int status=connectToDatabase(&db);

        if(status==0)
        {
                return NULL;
        }
        //update cookie value of the user for latter usage
        sql=updateLogin(cookie,username);
        //execute sqlite command
        status=executeSQLStatement(&db,sql,(void*)data,&errmsg,"Operation done successfully\n",callbackSelect);

        if(status==0)
        {
            return NULL;
        }
        //finally close the database connection
        sqlite3_close(db);

        return "Ok";
}

struct response_data *addApplicationRequest(char* reqbody,char* cookie,int memorySize,char* url)
{
       return  makeCURLRequest(reqbody,cookie,memorySize,url);

}
