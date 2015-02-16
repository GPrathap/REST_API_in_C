#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>
#include "../resources/externalLibs/headerfile/uthash.h"
#include "./headerfile/dbrequest.h"
#include "./headerfile/baseStruct.h"


/* Execute SQL statement */
int executeSQLStatement(sqlite3 **db,const char* sql,void *data, char **errmsg,char *successCon,int (*callback)(void *, int,  char **, char **))
{


       int rc;
       rc = sqlite3_exec(*db, sql,callback, data,errmsg);
       if( rc != SQLITE_OK ){

             printf("{error:\"true\",message:\"SQL error: %s\"}\n",*errmsg);
             return 0;

       }else{

            return 1;
       }
       //sqlite3_close(db);
}

char *createUserTable(char* userType)
{           /* Create SQL statement */
         char* sql;
         if(strcmp(userType,"APIUSER")==0) {
                        sql = "CREATE TABLE APIUSER("  \
                              "USERNAME TEXT PRIMARY KEY NOT NULL," \
                              "PASSWORD  TEXT    NOT NULL, COOKIE TEXT);";
                        return sql;
         }
        sql = "CREATE TABLE USER("  \
                  "USERNAME TEXT PRIMARY KEY     NOT NULL," \
                  "PASSWORD  TEXT    NOT NULL," \
                  "COOKIE  TEXT," \
                  "ACCESSTOKEN   TEXT," \
                  "CONSUMERKEY   TEXT," \
                  "CONSUMERSECRET  TEXT );";
        return sql;
}
char* removeTable(char* TableName){
    char* sql=malloc(200);
    char* tmp="DROP TABLE ";
    strcpy(sql,tmp);
    strcat(sql,TableName);
    strcat(sql,";");
    return sql;
}
char *createAPIUser(char* username,char* password)
{           /* Create SQL statement */
                 char* sql;
                 sql=malloc(200);
                 sprintf(sql, "INSERT INTO APIUSER (USERNAME,PASSWORD)VALUES (' %s ','%s');",username,password);
                 return sql;

}

char* createUser(char* username,char* password,char* cookie)
{
      char* sql;
      sql=malloc(200);
      sprintf(sql, "INSERT INTO USER (USERNAME,PASSWORD,COOKIE)VALUES ('%s','%s','%s');",username,password,cookie);
      return sql;
}

char *getAllUsers()
{

        char* sql;
        sql = "SELECT * from USER";
        return sql;

}

char *updateCookie(char* cookie,char* username)
{
             char* sql;
             sql=malloc(400);
             sprintf(sql, "UPDATE USER set COOKIE = '%s'where USERNAME='%s';",cookie,username);
             return sql;

}

char *updateLoginAPIUser(char* cookie,char* username)
{
             char* sql;
             sql=malloc(400);
             sprintf(sql, "UPDATE APIUSER set COOKIE = '%s'  where USERNAME='%s';",cookie,username);
             return sql;

}

char *updateSubscriptionDetails(char* consumerKey,char* accessToken,char* consumerSecret, char* username )
{
             char* sql;

             sql=malloc(400);
             sprintf(sql, "UPDATE USER set CONSUMERKEY = '%s',ACCESSTOKEN ='%s' ,CONSUMERSECRET= '%s'  where USERNAME='%s';",consumerKey,accessToken,consumerSecret,username);
             return sql;

}

char* getCookieValue(char* username,char* userType)
{
        char* sql;
        sql=malloc(256);
        sprintf(sql, "SELECT COOKIE from %s where USERNAME='%s';",userType,username);
        return sql;
}

char *createSQLStatementDelete()
{

        char* sql;
        sql = "DELETE from USER where USERNAME='Geesara'; " \
                "SELECT * from USER";
        return sql;

}

int connectToDatabase(sqlite3 **db)
{
       /* Open database */
       int  rc;
       rc = sqlite3_open(DB_PATH, db);
       if( rc ){

          printf("{error:\"true\",message:Can't open database: %s\"}\n",sqlite3_errmsg(*db));

          return 0;
       }else{

          return 1;
       }
}

 int callbackCookie(void *siteCookie, int argc, char **argv, char **azColName)
{

      int i;
      struct site_cookie *siteCookieVal;
      siteCookieVal=(struct site_cookie*)siteCookie;
      for(i=0; i<argc; i++){

         siteCookieVal->size=100;
         siteCookieVal->cookie=malloc(256);
         strcpy(siteCookieVal->cookie,argv[i]);
      }
      printf("\n");
      return 0;

}

/*print all uses in the database*/
 int callbackSelect(void *data, int argc, char **argv, char **azColName)
{
      int i;
      fprintf(stderr, "%s: ", (const char*)data);
      for(i=0; i<argc; i++){
         printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
      }
      printf("\n");
      return 0;
}
/*
this callback function is used to get cookie value from a  http response in curl
this functions is called aysconaslly and buffer will return http headder details one at time
so have tract when is the cookie value was return and if it is so save cookie value in given
struct
*/
 size_t header_callback(char *buffer,size_t size,size_t nitems,struct site_cookie *cookiec)
{
    if(strlen(buffer)>12)
    {
             char dest[11];
             strncpy(dest, buffer,10);

             if(strcmp(dest,"Set-Cookie")==0)
             {
                       char** cookieKeyValue=str_split(buffer,':');
                       cookiec->size=100;
                       cookiec->cookie=malloc(256);
                       char* temp1=str_replace(cookieKeyValue[1],"\r","");
                       char* temp2=str_replace(temp1,"\n","");
                       strcpy(cookiec->cookie,temp2);


             }
    }
    return nitems;
}

/*this callback function is used to get response body data  from a  http response in curl
    this function is called aysconasllyand and http response data comming from void* ptr
    so have to grab those data save it in url_data struct
    */
size_t body_callback(void *ptr, size_t size, size_t nmemb, struct url_data *data)
{
    size_t index = data->size;
    size_t n = (size * nmemb);
    char* tmp;

    data->size+=(size * nmemb);

    #ifdef DEBUG
    //fprintf(stderr, "data at %p size=%ld nmemb=%ld\n", ptr, size, nmemb);

    #endif
    tmp = realloc(data->data, data->size + 1); /* +1 for '\0' */

    if(tmp) {
        data->data = tmp;
    }
    else {

        if(data->data) {
            free(data->data);
        }
        fprintf(stdout, "\n");
        printf("{error:\"true\",message:\"Failed to allocate memory\"}\n");
        return 0;
    }

    memcpy((data->data + index), ptr, n);
    data->data[data->size] = '\0';

    return size * nmemb;
}

char* getPreviousCookieValue(char* username,char* userType)
{
      sqlite3 *db=NULL;
      char *errmsg = 0;
      const char *sql;
      // const char* data = "Callback function called\n";
      struct site_cookie *siteCookie;
      siteCookie=malloc(sizeof(struct site_cookie));
      siteCookie->size=0;
      siteCookie->cookie=malloc(256);

      if(NULL == siteCookie->cookie) {


           printf("{error:\"true\",message:\"Failed to allocate memory.\"}");
           return NULL;

      }
      //struct keyValue_struct *reqData = NULL;
      int status=connectToDatabase(&db);

       if(status==0)
       {

           printf("{error:\"true\",message:\"Cant open the database \"}");
           return NULL;
       }

       sql=getCookieValue(username,userType);
       status=executeSQLStatement(&db,sql,(void*)siteCookie,&errmsg,NULL,callbackCookie);

       if(status==0)
       {
            return NULL;
       }

       sqlite3_close(db);

       return siteCookie->cookie;

}

