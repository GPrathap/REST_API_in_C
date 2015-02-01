#include <stdio.h>
#include <curl/curl.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

#include "../hedder/uthash.h"
#include "../dbrequest/dbrequest.h"
#include "../json/json.h"
#include "../json/buf/buf.h"
#include "../json/jsmn/jsmn.h"

char *getApplicationDetails(char* reqbody);
struct response_data *getApplicationDetailsRequest(char* reqbody,char* cookie);
char* getApplicationDetailsResponse(char* res);
char* databaseHandler(char* reqbody,char* cookie);



int main()
{


           //char *s=getenv("CONTENT_LENGTH");
            int i=atoi(getenv("CONTENT_LENGTH"));
    //set content type as text/html
            printf("Content-type: text/html\n\n");
           // printf("%s\n<br />",s); //Shows you CONTENT_LENGTH works
           // printf("%d\n<br />",i); //Shows you it was converted to int
            char *tmp;
    //allocate memory to store request body data
            tmp=malloc(i+20);
    //read request body data from stdin
            int lenOfRead=fread(tmp,i,1,stdin); //read from stdin something of i bytes to tmp
            if(lenOfRead==0){
                printf("Post request is empty\n");
            }
    //make a process to handle backe server response
            char* statusgetApplicationDetails=getApplicationDetails(tmp);
            if(statusgetApplicationDetails==NULL){

                printf("Some thing wrong with your response\n");

            }else{

                printf("%s\n",statusgetApplicationDetails);

            }


    printf("%s\n",statusgetApplicationDetails);
    return 0;
}

char *getApplicationDetails(char* reqbody)
{
         struct keyValue_struct *reqData = NULL;
    //add request data to hashmap for later usage
         add_toList(&reqData,reqbody,'&','=');
    //get the username from hashmap
         struct keyValue_struct *username=getValue("username",&reqData);
    //get previous cookie value from database
         char* cookie=getPreviousCookieValue(username->value,"USER");
         if(cookie==NULL){
                printf("You have not been signed up yet\n");
                return NULL;
         }
    //get repose data of the backend server
         struct response_data *res_data=getApplicationDetailsRequest(reqbody,cookie);

         if(res_data==NULL){

            printf("Backend server is down try again later (:\n");
            return NULL;

         }
    //handler for handle repose of backend server
         char* clientRes=getApplicationDetailsResponse(res_data->res_body);
         if(clientRes==NULL)
         {

            printf("Interanl server error (:\n");
            return NULL;

         }
    //save cookie value in the database
         char* dbstatus=databaseHandler(reqbody,res_data->res_cookie);

         if(dbstatus==NULL)
         {
              return NULL;
         }


         return "Your application details are below\n";

}







char* getApplicationDetailsResponse(char* rest)
{


    //pointer to request body data hashmap
     struct keyValue_struct *users = NULL;
     //char* temp1=str_replace(rest,"{","");
     //char* temp2=str_replace(temp1,"}","");
     //char* res=str_replace(temp2,"\"","");
     //add_toList(&users,res,',',':');
    //split request body data into key and value and add it to hashmap
     addToListFromJSON(rest,&users);

    //get the error value
     struct keyValue_struct *s=getValue("error",&users);
     char buffer[100];
     strcpy(buffer,s->value);
    //remove unwanted spaces
     char* value=str_trim(buffer);

     if(strcmp(value,"false")!=0){

         struct keyValue_struct *msg=getValue("message",&users);
         printf("getApplicationDetails error : %s\n", msg->value);
         return NULL;

     }else{

        fprintf(stdout, "get application is done\n");
        return "Ok";

     }

}
char* databaseHandler(char* username,char* cookie)
{
    //pointer to database
        sqlite3 *db=NULL;
    //pointer  to  the error message
        char *errmsg = 0;
    //sql query string
        const char *sql;
        const char* data = "Callback function called\n";
    //try to connect to the database
        int status=connectToDatabase(&db);

        if(status==0)
        {
            return NULL;
        }
    //update user details(cookie value )
        sql=updateLogin(cookie,username);
        //sql=createUserTable();
        status=executeSQLStatement(&db,sql,(void*)data,&errmsg,"Operation done successfully\n",callbackSelect);

        if(status==0)
        {
            return NULL;
        }

        sqlite3_close(db);

        return "Ok";
}

struct response_data *getApplicationDetailsRequest(char* reqbody,char* cookie)
{

        CURL *curl;

        struct url_data data;
        data.size = 0;
        data.data = malloc(4096); /* reasonable size initial buffer */

        if(NULL == data.data) {

                    fprintf(stderr, "Failed to allocate memory.\n");
                    return NULL;
        }

        struct site_cookie cookiec;
        cookiec.size=0;
        cookiec.cookie=malloc(256);
        if(NULL == cookiec.cookie) {

                    fprintf(stderr, "Failed to allocate memory.\n");
                    return NULL;
        }

        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Accept: Subscription/x-www-form-urlencoded");
        headers = curl_slist_append(headers, "Content-Type: Subscription/x-www-form-urlencoded");
        headers = curl_slist_append(headers, "charsets: utf-8");


        struct response_data* res_data;
        res_data=malloc(sizeof(struct response_data));
        res_data->res_body=malloc(1000);
        res_data->res_cookie=malloc(256);

        if(NULL == res_data->res_body || NULL==res_data->res_cookie) {

                    fprintf(stderr, "Failed to allocate memory.\n");
                    return NULL;

        }

        buf_t *buf = buf_size(NULL, BUFFER_SIZE);

        data.data[0] = '\0';
        cookiec.cookie[0]= '\0';
        res_data->res_body[0]='\0';
        res_data->res_cookie[0]='\0';

        CURLcode res;
        curl_global_init(CURL_GLOBAL_ALL);
        curl = curl_easy_init();
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
        curl_easy_setopt(curl,CURLOPT_HTTPHEADER,headers);
        curl_easy_setopt(curl, CURLOPT_URL,"http://localhost:9763/store/site/blocks/application/application-list/ajax/application-list.jag?action=getApplications");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, fetch_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, buf);
        curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, header_callback);
        curl_easy_setopt(curl, CURLOPT_HEADERDATA,&cookiec);
        curl_easy_setopt(curl, CURLOPT_COOKIE,cookie);
        res=curl_easy_perform(curl);

        if(res != CURLE_OK){

            fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(res));
            return NULL;

        }

         curl_easy_cleanup(curl);

         char *jsonstr = buf_tostr(buf);
         free(buf->data);
         free(buf);
         strcpy(res_data->res_body,jsonstr);
         strcpy(res_data->res_cookie,cookiec.cookie);


        return res_data;

}
