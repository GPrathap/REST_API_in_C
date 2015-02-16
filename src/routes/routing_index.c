
#include <stdio.h>
#include <curl/curl.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include<pthread.h>
/**
* @param MAXBUFLEN configuration file's size*/
#define MAXBUFLEN 2000

#include "fcgi_stdio.h"
#include "../../libs/headerfile/curlreq.h"
#include "../controllers/headerfile/mainHeader.h"

struct keyValue_struct*  endpointConfiguration=NULL;
char* initialize(struct keyValue_struct** endpointConfig);
void* handler(void* args);
char* getUrl(char* key);

pthread_t tid[1];
pthread_mutex_t lock;

int main(){

    /*
    initialize database connection(make a persistent connection to database) , structs
    which are to used. Initialization section, which is executed only once.
    */
    int err;
    initialize(&endpointConfiguration);
    //getKeyValue(&endpointConfiguration);
    /*
    The FCGI_Accept blocks until a client request comes in, and then returns 0.
    If there is a system failure, or the system administrator terminates the process,
    Accept will return -1.
    */

    while (FCGI_Accept() >= 0) {

        //set the content type as text/html
        printf("Content-type: text/html\n\n");
        int i=atoi(getenv("CONTENT_LENGTH"));
        char *requestBody;
        //allocate memory for request body
        requestBody=malloc(i+2);
        //read from stdin(request body) something of i bytes to requestBody
        int lenOfRead=fread(requestBody,i,1,stdin);
        if(lenOfRead==0){

             printf("{error:\"true\",message:\"%s-Request body has been corrupted\"}\n",getenv("REQUEST_METHOD"));
             return 0;

        }

        //handle request according to the request action
        //initialize the thread
        if (pthread_mutex_init(&lock, NULL) != 0)
        {
             printf("{error:\"true\",message:\"Internal server error-a thread initialization error\"}\n");
             return 0;
        }
        //create a thread
        err = pthread_create(&(tid[0]), NULL, &handler,(void*)requestBody);
        if (err != 0){
            printf("{error:\"true\",message:\"Internal server error- thread creation error due to not enough storage\"}\n");
        }
        //wait until thread is finished
        pthread_join(tid[0], NULL);
        //finally destroy the lock
        pthread_mutex_destroy(&lock);

        // handler((void*)requestBody);
    }

    return 0;

}

/**
 * get url for given action
 * @param       key   (ex:signUp,login and so on...)
*/
char* getUrl(char* key) {
    struct keyValue_struct *s;
    //travel through hashmap and print all key-value pairs
    for(s=endpointConfiguration; s != NULL; s=(struct keyValue_struct*)(s->hh.next)) {
                if(strcmp(key,s->key)==0){
                         return s->value;
                 }
    }
    return NULL;
}

/**
 * used to initialize endpoint configuration
 * @param       endpointConfig   endpoint urls with action(ex : signUp, login , ...)
*/
char* initialize(struct keyValue_struct** endpointConfig){


        FILE *fp;
        char initInfo[2000];
        //open configuration file
        fp = fopen("./endpointConfig.txt", "r");
        if (fp != NULL)
        {
            size_t newLen = fread(initInfo, sizeof(char), MAXBUFLEN, fp);
            if (newLen == 0) {
                printf("{error:\"true\",message:\"Internal server error-cannot read configuration file\"}\n");
            } else {
                //Just to be safe
                initInfo[newLen-1] = '\0';
            }

            fclose(fp);
        }
        else
        {
            printf("{error:\"true\",message:\"Internal server error-configuration file does not exist\"}\n");
            return NULL;
        }
        char* res=str_replace(initInfo,"\"","");
        //read all properties from configuration file and insert into hashmap as key-value pair
        add_toList(&endpointConfiguration,res,',','=');
        if(endpointConfiguration==NULL)
        {
            return NULL;
        }
        return "Ok";
}


void* handler(void* args){
    //start acquiring lock
    pthread_mutex_lock(&lock);
    //cast void pointer into char pointer
    char* requestBody=(char*)args;
    //a pointer to the hashmap
    struct keyValue_struct *reqData = NULL;
    //split request into key-value pair and save it in hashmap
    add_toList(&reqData,requestBody,'&','=');
    //get action
    struct keyValue_struct *action=getValue("action",&reqData);
    char* actionMethod=action->value;
    if(strcmp(actionMethod,"addUser")==0)
    {
        signUp(requestBody,getUrl("signUp"),200);
    }
    else if(strcmp(actionMethod,"login")==0)
    {
        action=getValue("tag",&reqData);
        actionMethod=action->value;
        if(strcmp(actionMethod,"api")!=0)
        {
            login(requestBody,getUrl("login"),200);
        }
        else
        {
            apiLogin(requestBody,getUrl("loginAPI"),1000);
        }
    }
    else if(strcmp(actionMethod,"addApplication")==0)
    {
         addApplication(requestBody,getUrl("addApplication"),1200);
    }
    else if(strcmp(actionMethod,"addAPISubscription")==0)
    {
        addSubscription(requestBody,getUrl("addSubscription"),4096);
    }
    else if(strcmp(actionMethod,"generateApplicationKey")==0)
    {
        generateApplicationKey(requestBody,getUrl("generateApplicationKey"),4096);
    }
    else if(strcmp(actionMethod,"addAPI")==0)
    {
        addAPI(requestBody,getUrl("addAPI"),1000);
    }
    else if(strcmp(actionMethod,"updateStatus")==0)
    {
         publishAPI(requestBody,getUrl("publishAPI"),4000);
    }

    pthread_mutex_unlock(&lock);
    return NULL;
}