#include <stdio.h>
#include <curl/curl.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>



#include "../curl/curlreq.h"


char *signup(char* reqbody);
struct response_data *signupRequest(char* reqbody,char* cookie,int memorySize,char* url);
char* signupResponse(char* res);
char* databaseHandler(char* reqbody,char* cookie);

int main()
{
            //set the content type as text/html
            printf("Content-type: text/html\n\n");
            if(strcmp(getenv("REQUEST_METHOD"),"GET")==0){
                            printf("<H3>Page is not found</h3>\n");
                            return 0;
            }

            //char *s=getenv("CONTENT_LENGTH");
            int i=atoi(getenv("CONTENT_LENGTH"));
            //Shows you CONTENT_LENGTH works
            //printf("%s\n<br />",s);
            //Shows you it was converted to int
            //printf("%d\n<br />",i);
            char *tmp;
            //allocate memory for request body
            tmp=malloc(i+20);
            //read request body from stdin
            int lenOfRead=fread(tmp,i,1,stdin); //read from stdin something of i bytes to tmp
            if(lenOfRead==0){
                printf("Post request is empty\n");
            }





         //make a process to do request,response and database handle
        char* statusSignup=signup(tmp);
        if(statusSignup==NULL){
            printf("Some thing wrong with your response\n");
        }else{
             printf("%s\n",statusSignup);
        }

    return 0;
}

char *signup(char* reqbody)
{

        //send a request to backend server
         struct response_data *res_data=signupRequest(reqbody,"",200,"http://localhost:9763/store/site/blocks/user/sign-up/ajax/user-add.jag");
         if(res_data==NULL){

            printf("Backend server is down try again later (:\n");
            return NULL;

         }
        //get response from backend server
         char* clientRes=signupResponse(res_data->res_body);
         if(clientRes==NULL)
         {

            printf("Interanl server error \n");
            return NULL;

         }

//user details is updated
char* dbstatus=databaseHandler(reqbody,res_data->res_cookie);

         if(dbstatus==NULL)
         {
            return NULL;
         }

         return "You have been successfully signed in.\n";

}

char* databaseHandler(char* reqbody,char* cookie)
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

char* signupResponse(char* rest)
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

         printf("Signup error : %s\n", msg->value);
         return NULL;

     }else{


        return "Ok";

     }

}

struct response_data *signupRequest(char* reqbody,char* cookie,int memorySize,char* url)
{

    return makeCURLRequest(reqbody,cookie,memorySize,url);

}