#include <stdio.h>
#include <curl/curl.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

#include "../../libs/headerfile/curlreq.h"
#include "./headerfile/mainHeader.h"

char *login(char* reqbody,char* url,int memorySize)
{
    //make request to backend server
         struct response_data *res_data=loginRequest(reqbody,"",memorySize,url);
         if(res_data==NULL){

            printf("{error:\"true\",message:\"Backend server not responding\"}\n");
            return NULL;

         }
    //get the response from backend server
         char* clientRes=loginResponse(res_data->res_body);
         if(clientRes==NULL)
         {

            printf("{error:\"true\",message:\"Empty response body from backend server\"}\n");
            return NULL;

         }
    //save user details in database
         char* dbstatus=databaseHandler(reqbody,res_data->res_cookie);

         if(dbstatus==NULL)
         {
            return NULL;
         }

         return "You have been successfully logged in\n";

}

char* databaseHandler(char* reqbody,char* cookie)
{
    //ponter to the database
        sqlite3 *db=NULL;
    //pointer to the error message
        char *errmsg = 0;
    //sql query string
        const char *sql;
        const char* data = "Callback function called\n";
        struct keyValue_struct *reqData = NULL;
    //get all request data and put it into hashmap as key-value pair
        add_toList(&reqData,reqbody,'&','=');


    //try to connect to the database
        int status=connectToDatabase(&db);

        if(status==0)
        {
            printf("Cant open the database \n");
            return NULL;
        }
        struct keyValue_struct *username=getValue("username",&reqData);
    //update user details
        sql=updateCookie(cookie,username->value);
        status=executeSQLStatement(&db,sql,(void*)data,&errmsg,"Operation done successfully\n",callbackSelect);

        if(status==0)
        {
            return NULL;
        }

        sqlite3_close(db);
        printf("{error:\"false\",message:\"You have been successfully logged in\"}\n");
        return "Ok";
}

char* loginResponse(char* rest)
{


     //create pointer to  hashmap
     struct keyValue_struct *users = NULL;
     char* temp1=str_replace(rest,"{","");
     char* temp2=str_replace(temp1,"}","");
     char* res=str_replace(temp2,"\"","");
     //get response of backend server and split it into key-value pair and save it hashmap
     add_toList(&users,res,',',':');

     //get the error value
     struct keyValue_struct *s=getValue("error",&users);
     char buffer[100];
     strcpy(buffer,s->value);
    //remove unwanted spaces
     char* value=str_trim(buffer);

     if(strcmp(value,"false")!=0){

         struct keyValue_struct *msg=getValue("message",&users);

         printf("{error:\"true\",message:\"%s\"}\n",msg->value);
         return NULL;

     }else{


        return "Ok";

     }

}

struct response_data *loginRequest(char* reqbody,char* cookie,int memorySize,char* url)
{
        return makeCURLRequest(reqbody,cookie,memorySize,url);
}

