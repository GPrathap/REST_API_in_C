#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>
#include "../hedder/uthash.h"
#include "dbrequest.h"
#include "../baseStruct/baseStruct.h"

/*
int main(int argc, char* argv[])
{
   sqlite3 *db=NULL;
   char *errmsg = 0;
   int  rc;
   const char *sql;
   const char* data = "Callback function called\n";
   connectToDatabase(&db);

   sql=createUser("gfg","fdhg","hdfg");
   executeSQLStatement(&db,sql,(void*)data,&errmsg,"Operation done successfully\n");

   sql=updateLogin("gfhgsyfgsydfrysgfudsgfy","Geesara");
   executeSQLStatement(&db,sql,(void*)data,&errmsg,"Operation done successfully\n");

   sql=updateSubscriptionDetails("kd45666666666","ydyf99999999","dgfydgddddddd","Prathap1");
   executeSQLStatement(&db,sql,(void*)data,&errmsg,"Operation done successfully\n");

   sqlite3_close(db);

   return 0;
}
*/

/* Execute SQL statement */
int executeSQLStatement(sqlite3 **db,const char* sql,void *data, char **errmsg,char *successCon,int (*callback)(void *, int,  char **, char **))
{


       int rc;
       rc = sqlite3_exec(*db, sql,callback, data,errmsg);
       if( rc != SQLITE_OK ){
            fprintf(stdout, "SQL error: %s\n", *errmsg);
            sqlite3_free(*errmsg);
            return 0;
       }else{
            fprintf(stdout,"%s\n",successCon);
            return 1;
       }
       //sqlite3_close(db);
}
char *createUserTable()
{           /* Create SQL statement */
            char* sql;
            sql = "CREATE TABLE USER("  \
                  "USERNAME TEXT PRIMARY KEY     NOT NULL," \
                  "PASSWORD  TEXT    NOT NULL," \
                  "COOKIE  TEXT," \
                  "ACCESSTOKEN   TEXT," \
                  "CONSUMERKEY   TEXT," \
                  "CONSUMERSECRET  TEXT );";
            return sql;
}
char *createAPIUserTable()
{           /* Create SQL statement */
            char* sql;
            sql = "CREATE TABLE APIUSER("  \
                  "USERNAME TEXT PRIMARY KEY NOT NULL," \
                  "PASSWORD  TEXT    NOT NULL, COOKIE TEXT);";
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

                 char* temp="INSERT INTO APIUSER (USERNAME,PASSWORD)VALUES ('";
                 strcpy(sql,temp);
                 strcat(sql,username);
                 strcat(sql,"','");
                 strcat(sql,password);
                 strcat(sql,"');");

                 return sql;

}

char* createUser(char* username,char* password,char* cookie)
{
      char* sql;
      sql=malloc(200);

      char* temp="INSERT INTO USER (USERNAME,PASSWORD,COOKIE)VALUES ('";
      strcpy(sql,temp);
      strcat(sql,username);
      strcat(sql,"','");
      strcat(sql,password);
      strcat(sql,"','");
      strcat(sql,cookie);
      strcat(sql,"');");

      return sql;
}

char *getAllUsers()
{

        char* sql;
        sql = "SELECT * from USER";
        return sql;

}

char *updateLogin(char* cookie,char* username)
{
             char* sql;
             sql=malloc(400);

             char* temp="UPDATE USER set COOKIE = '";
             strcpy(sql,temp);
             strcat(sql,cookie);
             strcat(sql,"'  where USERNAME='");
             strcat(sql,username);
             strcat(sql,"';");
             strcat(sql," SELECT * from USER");

             return sql;

}

char *updateLoginAPIUser(char* cookie,char* username)
{
             char* sql;
             sql=malloc(400);

             char* temp="UPDATE APIUSER set COOKIE = '";
             strcpy(sql,temp);
             strcat(sql,cookie);
             strcat(sql,"'  where USERNAME='");
             strcat(sql,username);
             strcat(sql,"';");
             strcat(sql," SELECT * from APIUSER");

             return sql;

}

char *updateSubscriptionDetails(char* consumerKey,char* accessToken,char* consumerSecret, char* username )
{
             char* sql;

             sql=malloc(400);

             char* temp="UPDATE USER set CONSUMERKEY = '";
             strcpy(sql,temp);
             strcat(sql,consumerKey);
             strcat(sql,"',ACCESSTOKEN ='");
             strcat(sql,accessToken);
             strcat(sql,"' ,CONSUMERSECRET= '");
             strcat(sql,consumerSecret);
             strcat(sql,"'  where USERNAME='");
             strcat(sql,username);
             strcat(sql,"';");
             //strcat(sql," SELECT * from USER");

             return sql;

}

char* getCookieValue(char* username,char* userType)
{
        char* sql;
        sql=malloc(256);

        char* temp="SELECT COOKIE from ";
        strcpy(sql,temp);
        strcat(sql,userType);
        strcat(sql,"  where USERNAME='");
        strcat(sql,username);
        strcat(sql,"';");
        return sql;
}

char *createSQLStatementDelete()
{

        char* sql;
        sql = "DELETE from USER where USERNAME='Geesara'; " \
                "SELECT * from USER";
        return sql;

}
/*
static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
   int i;
   for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

*/

int connectToDatabase(sqlite3 **db)
{
       /* Open database */
       int  rc;
       rc = sqlite3_open(DB_PATH, db);
       if( rc ){
          fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(*db));
          return 0;
       }else{
          fprintf(stdout, "Opened database successfully\n");
          return 1;
       }
}
 int callbackCookie(void *siteCookie, int argc, char **argv, char **azColName)
{

      int i;
      struct site_cookie *siteCookieVal;
      siteCookieVal=(struct site_cookie*)siteCookie;
      for(i=0; i<argc; i++){
         printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
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
        fprintf(stdout, "Failed to allocate memory.\n");
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

           fprintf(stdout, "Failed to allocate memory.\n");
           return NULL;
      }
      //struct keyValue_struct *reqData = NULL;
      int status=connectToDatabase(&db);

       if(status==0)
       {
           printf("Cant open the database \n");
           return NULL;
       }

       sql=getCookieValue(username,userType);
       status=executeSQLStatement(&db,sql,(void*)siteCookie,&errmsg,"Operation done successfully\n",callbackCookie);

       if(status==0)
       {
            return NULL;
       }

       sqlite3_close(db);

       return siteCookie->cookie;

}

