#include <stdio.h>
#include <curl/curl.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

#include "../../libs/headerfile/curlreq.h"
#include "./headerfile/mainHeader.h"

char *addAPI(char* reqbody,char* url,int memorySize)
{
         //make a hashmap and add all request data as key-value pairs
         struct keyValue_struct *reqData = NULL;
         add_toList(&reqData,reqbody,'&','=');

         //get username from hashmap
         struct keyValue_struct *username=getValue("username",&reqData);

         //get the cookie value from database
         char* cookie=getPreviousCookieValue(username->value,"APIUSER");
         if(cookie==NULL){
                printf("{error:\"true\",message:\"You have not been  signed up yet\"}\n");
                return NULL;
         }
         //sent a request to backend server
         struct response_data *res_data=addAPIRequest(reqbody,cookie,memorySize,url);
         if(res_data==NULL){

            printf("{error:\"true\",message:\"Backend server not responding\"}\n");
            return NULL;

         }
        //get the response of backend server
         char* clientRes=addAPIResponse(res_data->res_body);
         if(clientRes==NULL)
         {

            printf("{error:\"true\",message:\"Empty response body from backend server\"}\n");
            return NULL;

         }
        //finally update user details
         char* dbstatus=databaseHandlerAPIadd(reqbody,res_data->res_cookie);

         if(dbstatus==NULL)
         {
              return NULL;
         }

         return "API is added successfull\n";

}
char* addAPIResponse(char* rest)
{
    // make hashmap add all response body data as key-value pairs
     struct keyValue_struct *users = NULL;
     char* temp1=str_replace(rest,"{","");
     char* temp2=str_replace(temp1,"}","");
     char* res=str_replace(temp2,"\"","");
     add_toList(&users,res,',',':');

     //get error value from hashmap
     struct keyValue_struct *s=getValue("error",&users);
     char buffer[100];
     strcpy(buffer,s->value);
     //remove unwanted withspaces
     char* value=str_trim(buffer);

     if(strcmp(value,"false")!=0){

         struct keyValue_struct *msg=getValue("message",&users);

         printf("{error:\"true\",message:\"%s\"}\n",msg->value);
         return NULL;

     }else{


        return "Ok";

     }

}
char* databaseHandlerAPIadd(char* username,char* cookie)
{
        //pointer to database
        sqlite3 *db=NULL;
        //ponter to a error message
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
        //update user details
        sql=updateLoginAPIUser(cookie,username);
        status=executeSQLStatement(&db,sql,(void*)data,&errmsg,"Operation done successfully\n",callbackSelect);

        if(status==0)
        {
            return NULL;
        }
        //close database connection
        sqlite3_close(db);

        return "Ok";
}

struct response_data *addAPIRequest(char* reqbody,char* cookie,int memorySize,char* url)
{
    return makeCURLRequest(reqbody,cookie,memorySize,url);

}

