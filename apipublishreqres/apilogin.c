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
            //char *s=getenv("CONTENT_LENGTH");
            int i=atoi(getenv("CONTENT_LENGTH"));
        	printf("Content-type: text/html\n\n");
        	//printf("%s\n<br />",s); //Shows you CONTENT_LENGTH works
        	//printf("%d\n<br />",i); //Shows you it was converted to int
        	char *tmp;
        	//allocate memory for request body data
        	tmp=malloc(i+20);
        	//read request from stdin
         	int lenOfRead=fread(tmp,i,1,stdin); //read from stdin something of i bytes to tmp
         	if(lenOfRead==0){
         	    printf("Post request is empty\n");
         	}

        char* statuslogin=login(tmp);
        if(statuslogin==NULL){
            printf("Some thing wrong with your response\n");
        }else{
             printf("%s\n",statuslogin);
        }



    return 0;
}

char *login(char* reqbody)
{

        //sent a request to backend server
         struct response_data *res_data=loginRequest(reqbody,"",1000,"http://localhost:9763/publisher/site/blocks/user/login/ajax/login.jag");
         if(res_data==NULL)
         {

            printf("Backend server is down try again later (:\n");
            return NULL;

         }
        //get the response of backend server
         char* clientRes=loginResponse(res_data->res_body);
         if(clientRes==NULL)
         {

            printf("Interanl server error (:\n");
            return NULL;

         }
        //finally update user details
         char* dbstatus=databaseHandler(reqbody,res_data->res_cookie);

         if(dbstatus==NULL)
         {
            return NULL;
         }

         return " login successfull\n";

}

char* databaseHandler(char* reqbody,char* cookie)
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

        return "Ok";
}

char* loginResponse(char* rest)
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

