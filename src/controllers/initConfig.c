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
        //sql=createUserTable();
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

