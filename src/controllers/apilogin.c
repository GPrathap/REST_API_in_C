#include <stdio.h>
#include <curl/curl.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

#include "../../libs/headerfile/curlreq.h"

#include "./headerfile/mainHeader.h"

char *apiLogin(char* reqbody,char* url,int memorySize)
{
        //sent a request to backend server
         struct response_data *res_data=apiLoginRequest(reqbody,"",memorySize,url);
         if(res_data==NULL)
         {

            printf("{error:\"true\",message:\"Backend server not responding\"}\n");
            return NULL;

         }
        //get the response of backend server
         char* clientRes=apiLoginResponse(res_data->res_body);
         if(clientRes==NULL)
         {

            printf("{error:\"true\",message:\"Empty response body from backend server\"}\n");
            return NULL;

         }
        //finally update user details
         char* dbstatus=databaseHandlerAPI(reqbody,res_data->res_cookie);

         if(dbstatus==NULL)
         {
            return NULL;
         }

         return " login successfull\n";

}

char* databaseHandlerAPI(char* reqbody,char* cookie)
{
        //pointer to database
        sqlite3 *db=NULL;
        char *errmsg = 0;
        const char *sql;
        const char* data = "Callback function called\n";
        struct keyValue_struct *reqData = NULL;
        //ponter to a error message
        add_toList(&reqData,reqbody,'&','=');

        //try to connect to database
        int status=connectToDatabase(&db);

        if(status==0)
        {
            printf("Cant open the database \n");
            return NULL;
        }

        //get username from hashmap
        struct keyValue_struct *username=getValue("username",&reqData);
        //update user details
        sql=updateLoginAPIUser(cookie,username->value);
        status=executeSQLStatement(&db,sql,(void*)data,&errmsg,"Operation done successfully\n",callbackSelect);

        if(status==0)
        {
            return NULL;
        }
        //close database connection
        sqlite3_close(db);
        printf("{error:\"false\",message:\"You have been successfully logged in\"}\n");
        return "Ok";
}

char* apiLoginResponse(char* rest)
{

     // make hashmap add all response body data as key-value pairs
     struct keyValue_struct *users = NULL;
     char* temp1=str_replace(rest,"{","");
     char* temp2=str_replace(temp1,"}","");
     char* res=str_replace(temp2,"\"","");
     add_toList(&users,res,',',':');

     struct keyValue_struct *s=getValue("error",&users);
     char buffer[100];
     strcpy(buffer,s->value);
     char* value=str_trim(buffer);

     if(strcmp(value,"false")!=0){

         struct keyValue_struct *msg=getValue("message",&users);
         printf("{error:\"true\",message:\"%s\"}\n",msg->value);
         return NULL;

     }else{


        return "Ok";

     }

}

struct response_data *apiLoginRequest(char* reqbody,char* cookie,int memorySize,char* url)
{

        return makeCURLRequest(reqbody,cookie,memorySize,url);
}

