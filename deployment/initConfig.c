#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "../baseStruct/baseStruct.h"
#include "../dbrequest/dbrequest.h"

int main(){

        sqlite3 *db=NULL;
        char *errmsg = 0;
        const char *sql;
        const char* data = "Callback function called\n";


        int status=connectToDatabase(&db);

        if(status==0)
        {
            printf("Can not connect to the database may be part is not valid. Please check it again or no permission to open it\n");
            return -1;
        }

        sql=createUserTable();
        //sql=createUserTable();
        status=executeSQLStatement(&db,sql,(void*)data,&errmsg,"Normal user table was created\n",callbackSelect);

        if(status==0)
        {
            printf("Error while creating normal user table\n");
            return -1;
        }

        sql=createAPIUserTable();
        //sql=createUserTable();
        status=executeSQLStatement(&db,sql,(void*)data,&errmsg,"API user table was created\n",callbackSelect);

        if(status==0)
        {
            printf("Error while creating API user table\n");
            return -1;
        }

        sql=createAPIUser("provider1","provider1");
        status=executeSQLStatement(&db,sql,(void*)data,&errmsg,"Provider1was created\n",callbackSelect);

        if(status==0)
        {
            printf("Error while creating provider1 user\n");
            return -1;
        }
        printf("Initial configuration is done ! \n");
        sqlite3_close(db);

        return 0;

}


