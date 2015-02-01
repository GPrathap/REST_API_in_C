#include <stdio.h>
#include <curl/curl.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

#include "../curl/curlreq.h"


char *publishAPI(char* reqbody);
struct response_data *publishAPIRequest(char* reqbody,char* cookie,int memorySize,char* url);
char* publishAPIResponse(char* res);
char* databaseHandler(char* username,char* cookie);

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
            char* statuspublishAPI=publishAPI(tmp);
            if(statuspublishAPI==NULL){
                printf("Something wrong with your response\n");
            }else{
                printf("%s\n",statuspublishAPI);
            }



    return 0;
}

char *publishAPI(char* reqbody)
{       //make a hashmap and add all request data as key-value pairs
         struct keyValue_struct *reqData = NULL;
         add_toList(&reqData,reqbody,'&','=');
        //get username from hashmap
         struct keyValue_struct *username=getValue("username",&reqData);
        //get the cookie value from database
         char* cookie=getPreviousCookieValue(username->value,"APIUSER");
         if(cookie==NULL){
                printf("You have not been login or signed up yet\n");
                return NULL;
         }
         //sent a request to backend server
         struct response_data *res_data=publishAPIRequest(reqbody,cookie,4096,"http://localhost:9763/publisher/site/blocks/life-cycles/ajax/life-cycles.jag");
         if(res_data==NULL){

            printf("Backend server is down try again later (:\n");
            return NULL;

         }
        //get the response of backend server
         char* clientRes=publishAPIResponse(res_data->res_body);
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


         return " Publishing an API is done donesuccessfully\n";

}
char* publishAPIResponse(char* rest)
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
     //remove unwanted withspaces
     char* value=str_trim(buffer);
    //get error value from hashmap
     if(strcmp(value,"false")!=0){

         struct keyValue_struct *msg=getValue("message",&users);

         printf("publishAPI error : %s\n", msg->value);
         return NULL;

     }else{


        return "Ok";

     }

}
char* databaseHandler(char* username,char* cookie)
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

struct response_data *publishAPIRequest(char* reqbody,char* cookie,int memorySize,char* url)
{

        return makeCURLRequest(reqbody,cookie,memorySize,url);

}

