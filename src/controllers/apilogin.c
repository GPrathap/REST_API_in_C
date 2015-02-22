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

char *apiLogin(char* reqbody,char* url,int memorySize)
{
         struct response_data *res_data=apiLoginRequest(reqbody,"",memorySize,url);
         if(res_data==NULL)
         {
            printf("{error:\"true\",message:\"Backend server not responding\"}\n");
            return NULL;
         }
         char* clientRes=apiLoginResponse(res_data->res_body);
         if(clientRes==NULL)
         {
            printf("{error:\"true\",message:\"Empty response body from backend server\"}\n");
            return NULL;
         }
         char* dbstatus=databaseHandlerAPI(reqbody,res_data->res_cookie);
         if(dbstatus==NULL)
         {
            return NULL;
         }
         return " login successfull\n";

}

char* databaseHandlerAPI(char* reqbody,char* cookie)
{
        sqlite3 *db=NULL;
        char *errmsg = 0;
        const char *sql;
        const char* data = "Callback function called\n";
        struct keyValue_struct *reqData = NULL;
        add_toList(&reqData,reqbody,'&','=');
        int status=connectToDatabase(&db);
        if(status==0)
        {
            printf("Cant open the database \n");
            return NULL;
        }
        struct keyValue_struct *username=getValue("username",&reqData);
        sql=updateLoginAPIUser(cookie,username->value);
        status=executeSQLStatement(&db,sql,(void*)data,&errmsg,"Operation done successfully\n",callbackSelect);
        if(status==0)
        {
            return NULL;
        }
        sqlite3_close(db);
        printf("{error:\"false\",message:\"You have been successfully logged in\"}\n");
        return "Ok";
}

char* apiLoginResponse(char* rest)
{
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
         printf("{error:\"true\",message:\"%s\"}\n",msg->value);
         return NULL;
     }else{
        return "Ok";
     }

}

struct response_data *apiLoginRequest(char* reqbody,char* cookie,int memorySize,char* url)
{
        return makeCURLRequest(reqbody,cookie,memorySize,url);
}

