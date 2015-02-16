

#include <stdio.h>
#include <curl/curl.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

#include "../../libs/headerfile/curlreq.h"
#include "./headerfile/mainHeader.h"

char *addSubscription(char* reqbody,char* url,int memorySize)
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
                printf("{error:\"true\",message:\"You have not been  signed up yet\"}\n");
                return NULL;
         }

    //Now make request to backend server 
         struct response_data *res_data=addSubscriptionRequest(reqbody,cookie,memorySize,url);
         if(res_data==NULL){

           printf("{error:\"true\",message:\"Backend server not responding\"}\n");
            return NULL;

         }
    //If response is there, to  handle the response 
         char* clientRes=addSubscriptionResponse(res_data->res_body);
         if(clientRes==NULL)
         {

            printf("{error:\"true\",message:\"Empty response body from backend server\"}\n");
            return NULL;

         }
    //finally call the database handle to save the new cookie value of user
         char* dbstatus=databaseHandlerSubscription(reqbody,res_data->res_cookie);

         if(dbstatus==NULL)
         {
              return NULL;
         }

        printf("{error:\"false\",message:\"Your subscription is accepted successfully\"}\n");
        return "Ok";

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
         printf("{error:\"true\",message:\"%s\"}\n",msg->value);
         return NULL;

     }else{


        return "Ok";

     }

}
char* databaseHandlerSubscription(char* username,char* cookie)
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
        sql=updateCookie(cookie,username);
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
