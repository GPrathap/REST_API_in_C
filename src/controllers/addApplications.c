#include <stdio.h>
#include <curl/curl.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>





#include "../../libs/headerfile/curlreq.h"
#include "./headerfile/mainHeader.h"

/*Forward request to backend server get the response back and forward to where it came*/
char *addApplication(char* reqbody,char* url,int memorySize)
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

                printf("{error:\"true\",message:\"You have not been  signed up yet\"}\n");
                return NULL;
         }
         struct response_data *res_data=addApplicationRequest(reqbody,cookie,memorySize,url);
         if(res_data==NULL){

                printf("{error:\"true\",message:\"Backend server not responding\"}\n");
                return NULL;

         }
         //if there is a response from back end server it is handled by this function
         char* clientRes=addApplicationResponse(res_data->res_body);
         //something went wrong in server itself may be database access error or something which is not expected
         if(clientRes==NULL)
         {

                printf("{error:\"true\",message:\"Empty response body from backend server\"}\n");
                return NULL;

         }

         char* dbstatus=databaseHandlerApplicaation(reqbody,res_data->res_cookie);

         if(dbstatus==NULL)
         {
              return NULL;
         }

         printf("{error:\"false\",message:\"Application is added\"}\n");
         return "Ok";

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
         printf("{error:\"true\",message:\"%s\"}\n",msg->value);
         return NULL;

     }
     return "Ok";

}
char* databaseHandlerApplicaation(char* username,char* cookie)
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
        sql=updateCookie(cookie,username);
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
