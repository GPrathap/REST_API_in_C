#include <stdio.h>
#include <curl/curl.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>


#include "../../libs/headerfile/curlreq.h"

#include "./headerfile/mainHeader.h"

char *generateApplicationKey(char* reqbody,char* url,int memorySize)
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
                printf("{error:\"true\",message:\"You have not been  signed up yet\"}\n");
                return NULL;
         }
    //make request to backend server
         struct response_data *res_data=generateApplicationKeyRequest(reqbody,cookie,memorySize,url);

         if(res_data==NULL)
         {

            printf("{error:\"true\",message:\"Backend server not responding\"}\n");
            return NULL;

         }
    //if response is present analyze response data
         char* clientRes=generateApplicationKeyResponse(res_data->res_body,res_data->res_cookie,&resData);
         if(clientRes==NULL)
         {

            printf("{error:\"true\",message:\"Empty response body from backend server\"}\n");
            return NULL;

         }
    //finally save accesstoken and some importance stuff in database
         char* dbstatus=databaseHandlerGenerateApplication(&resData,username->value);

         if(dbstatus==NULL)
         {
              return NULL;
         }


         return "Ok";

}







char* generateApplicationKeyResponse(char* rest,char* cookie,struct keyValue_struct** list)
{



    //create hashmap using response of backend server
     addToListFromJSONGeneratedKeys(rest,list);
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

         printf("{error:\"true\",message:\"%s\"}\n",msg->value);
         return NULL;

     }else{


        return "Ok";

     }

}
char* databaseHandlerGenerateApplication(struct keyValue_struct** list,char* username)
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
        printf("{error:\"false\",message:\"Generating an application key is done done successfully \",keys:{consumerKey:\"%s\",accessToken:\"%s\",consumerSecret:\"%s\"}}\n",consumerKey->value,accessToken->value,consumerSecret->value);
        return "Ok";
}

struct response_data *generateApplicationKeyRequest(char* reqbody,char* cookie,int memorySize,char* url)
{
         return makeCURLRequest(reqbody,cookie,memorySize,url);
}
