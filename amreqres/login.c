#include <stdio.h>
#include <curl/curl.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

#include "../curl/curlreq.h"


char *login(char* reqbody);
struct response_data *loginRequest(char* reqbody,char* cookie,int memorySize,char* url);
char* loginResponse(char* res);
char* databaseHandler(char* reqbody,char* cookie);

int main()
{
    //set the content type as text/html
            printf("Content-type: text/html\n\n");
    //GET requests are not allowed
            if(strcmp(getenv("REQUEST_METHOD"),"GET")==0){
                 printf("<H3>Page is not found</h3>\n");
                 return 0;
            }
            //char *s=getenv("CONTENT_LENGTH");
            int i=atoi(getenv("CONTENT_LENGTH"));

           // printf("%s\n<br />",s); //Shows you CONTENT_LENGTH works
           // printf("%d\n<br />",i); //Shows you it was converted to int
            char *tmp;
    //allocate memory to store request body data
            tmp=malloc(i+20);
    //read request data from stdin
            int lenOfRead=fread(tmp,i,1,stdin); //read from stdin something of i bytes to tmp
            if(lenOfRead==0){
                printf("Post request is empty\n");
            }

    //make a process to handle the login request/response and db handling
        char* statuslogin=login(tmp);
        if(statuslogin==NULL){
            printf("Something wrong with the response of backend server\n");
        }else{
             printf("%s\n",statuslogin);
        }


    return 0;
}

char *login(char* reqbody)
{

    //make request to backend server
         struct response_data *res_data=loginRequest(reqbody,"",400,"http://localhost:9763/store/site/blocks/user/login/ajax/login.jag");
         if(res_data==NULL){

            printf("Backend server is down try again later (:\n");
            return NULL;

         }
    //get the response from backend server
         char* clientRes=loginResponse(res_data->res_body);
         if(clientRes==NULL)
         {

            printf("Interanl server error (:\n");
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
        sql=updateLogin(cookie,username->value);
        status=executeSQLStatement(&db,sql,(void*)data,&errmsg,"Operation done successfully\n",callbackSelect);

        if(status==0)
        {
            return NULL;
        }

        sqlite3_close(db);

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

         printf("login error : %s\n", msg->value);
         return NULL;

     }else{


        return "Ok";

     }

}

struct response_data *loginRequest(char* reqbody,char* cookie,int memorySize,char* url)
{
        return makeCURLRequest(reqbody,cookie,memorySize,url);
}

