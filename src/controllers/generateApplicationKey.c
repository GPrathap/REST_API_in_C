/*
 * Copyright (c) 2015, WSO2 Inc. (http://www.wso2.org) All Rights Reserved.
 *
 *  WSO2 Inc. licenses this file to you under the Apache License,
 *  Version 2.0 (the "License"); you may not use this file except
 *  in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing,
 *  software distributed under the License is distributed on an
 *  "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 *  KIND, either express or implied. See the License for the
 *  specific language governing permissions and limitations
 *  under the License.
 */
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
         struct keyValue_struct *reqData = NULL;
         struct keyValue_struct *resData = NULL;
         add_toList(&reqData,reqbody,'&','=');
         struct keyValue_struct *username=getValue("username",&reqData);
         char* cookie=getPreviousCookieValue(username->value,"USER");
         if(cookie==NULL)
         {
                printf("{error:\"true\",message:\"You have not been  signed up yet\"}\n");
                return NULL;
         }
         struct response_data *res_data=generateApplicationKeyRequest(reqbody,cookie,memorySize,url);
         if(res_data==NULL)
         {
            printf("{error:\"true\",message:\"Backend server not responding\"}\n");
            return NULL;
         }
         char* clientRes=generateApplicationKeyResponse(res_data->res_body,res_data->res_cookie,&resData);
         if(clientRes==NULL)
         {
            printf("{error:\"true\",message:\"Empty response body from backend server\"}\n");
            return NULL;
         }
         char* dbstatus=databaseHandlerGenerateApplication(&resData,username->value);
         if(dbstatus==NULL)
         {
              return NULL;
         }
         return "Ok";
}

char* generateApplicationKeyResponse(char* rest,char* cookie,struct keyValue_struct** list)
{
     addToListFromJSONGeneratedKeys(rest,list);
     add_item("cookie",cookie,list);
     struct keyValue_struct *s=getValue("error",list);
     char buffer[100];
     strcpy(buffer,s->value);
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
        sqlite3 *db=NULL;
        char *errmsg = 0;
        const char *sql;
        const char* data = "Callback function called\n";
        int status=connectToDatabase(&db);
        if(status==0)
        {
            return NULL;
        }
        struct keyValue_struct *consumerKey=getValue("consumerKey",list);
        struct keyValue_struct *accessToken=getValue("accessToken",list);
        struct keyValue_struct *consumerSecret=getValue("consumerSecret",list);
        sql=updateSubscriptionDetails(consumerKey->value,accessToken->value,consumerSecret->value,username);
        status=executeSQLStatement(&db,sql,(void*)data,&errmsg,"Operation done successfully\n",callbackSelect);
        if(status==0)
        {
            return NULL;
        }
        sqlite3_close(db);
        printf("{error:\"false\",message:\"Generating an application key is done done successfully \",keys:{consumerKey:\"%s\",accessToken:\"%s\",consumerSecret:\"%s\"}}\n",consumerKey->value,accessToken->value,consumerSecret->value);
        return "Ok";
}

struct response_data *generateApplicationKeyRequest(char* reqbody,char* cookie,int memorySize,char* url)
{
         return makeCURLRequest(reqbody,cookie,memorySize,url);
}
