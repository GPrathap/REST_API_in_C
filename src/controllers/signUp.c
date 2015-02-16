#include <stdio.h>
#include <curl/curl.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

#include "../../libs/headerfile/curlreq.h"

#include "./headerfile/mainHeader.h"

char *signUp(char* reqbody,char* url,int memorySize)
{
              //send a request to backend server
                 struct response_data *res_data=signUpRequest(reqbody,"",memorySize,url);
                 if(res_data==NULL){

                    printf("{error:\"true\",message:\"Backend server not responding\"}\n");
                    return NULL;

                 }
                //get response from backend server
                 char* clientRes=signUpResponse(res_data->res_body);
                 if(clientRes==NULL)
                 {

                    printf("{error:\"true\",message:\"Empty response body from backend server\"}\n");
                    return NULL;

                 }

                //user details is updated
                char* dbstatus=databaseHandlerSignUp(reqbody,res_data->res_cookie);

                 if(dbstatus==NULL)
                 {
                    return NULL;
                 }

                 printf("{error:\"false\",message:\"You have been successfully signed in.\"}\n");
                 return "Ok";

}

char* databaseHandlerSignUp(char* reqbody,char* cookie)
{
    //a pointer to the database
            sqlite3 *db=NULL;
        //a pointer to the error message
            char *errmsg = 0;
        //sql query string
            const char *sql;
            const char* data = "Callback function called\n";
        //a pointer to the hashmap
            struct keyValue_struct *reqData = NULL;
        //split request into key-value pair and save it in hashmap
            add_toList(&reqData,reqbody,'&','=');

        //getKeyValue(&reqData);
        //try to connect to the database
            int status=connectToDatabase(&db);

            if(status==0)
            {
                return NULL;
            }
              //get user information from hashmap and create user and save it in database
            struct keyValue_struct *username=getValue("username",&reqData);
            struct keyValue_struct *password=getValue("password",&reqData);
            sql=createUser(username->value,password->value,cookie);

            status=executeSQLStatement(&db,sql,(void*)data,&errmsg,"Operation done successfully\n",callbackSelect);

            if(status==0)
            {
                return NULL;
            }

            sqlite3_close(db);

            return "Ok";
}

char* signUpResponse(char* rest)
{

    //a pointer to the hashmap
         struct keyValue_struct *users = NULL;
         char* temp1=str_replace(rest,"{","");
         char* temp2=str_replace(temp1,"}","");
         char* res=str_replace(temp2,"\"","");
        //split response of backend server  into key-value pair and save it in hashmap
         add_toList(&users,res,',',':');

        //get the error value of backend server
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

struct response_data *signUpRequest(char* reqbody,char* cookie,int memorySize,char* url)
{

    return makeCURLRequest(reqbody,cookie,memorySize,url);

}