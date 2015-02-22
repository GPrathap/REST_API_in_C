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
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "../../libs/headerfile/baseStruct.h"
#include "../../libs/headerfile/dbrequest.h"

int main(){
        sqlite3 *db=NULL;
        char *errmsg = 0;
        const char *sql;
        const char* data = "Callback function called\n";
        int status=connectToDatabase(&db);
        if(status==0)
        {
            printf("Can not connect to the database, may be path is not valid. Please check it again or no permission to open it\n");
            return -1;
        }
        sql=createUserTable("USER");
        status=executeSQLStatement(&db,sql,(void*)data,&errmsg,"Normal user table was created\n",callbackSelect);
        if(status==0)
        {
            printf("Error while creating a user table\n");
            return -1;
        }
        sql=createUserTable("APIUSER");
        status=executeSQLStatement(&db,sql,(void*)data,&errmsg,"API user table was created\n",callbackSelect);
        if(status==0)
        {
            printf("Error while creating API user table\n");
            return -1;
        }
        sql=createAPIUser("provider1","provider1");
        status=executeSQLStatement(&db,sql,(void*)data,&errmsg,"Provider1 was inserted into api user table\n",callbackSelect);
        if(status==0)
        {
            printf("Error while creating provider1 user\n");
            return -1;
        }
        printf("Initial configuration is done ! \n");
        sqlite3_close(db);
        return 0;
}

