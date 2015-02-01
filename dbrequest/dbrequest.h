#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include "../hedder/uthash.h"
#define DB_PATH "/home/geesara/try4/apache2_modules/project/test.db"



/*when headder callback  function is called this is one is used to save http cookie value*/
struct site_cookie {

    size_t size;
    char* cookie;

};

/*when body_callback function is called this is one is used to save http response body data*/
struct url_data {

    size_t size;
    char* data;

};

/*this struct is made using above two struct */
struct response_data{

    char* res_body;
    char* res_cookie;

};


/**
 * is used to connected to databse
 * @param		db  pointer to database
 */
int connectToDatabase(sqlite3 **db);


/**
 * String replace
 * @param		str  string is to be modified
 * @param		old  string is to be replaced
 * @param		new string is to be added
 */
//char *createSQLStatement();

/**
 * execute given sql statement
 * @param		db          pointer too database
 * @param		sql         sql query string
 * @param		data        void pointer to the function
 * @param       errmsg      error message
 * @param       successCon  some statement for show if execution is completed
 * @param       callback function callback function and argument which is required
 */
int executeSQLStatement(sqlite3 **db,const char* sql,void *data, char **errmsg,char *successCon,int (*callback)(void *, int,  char **, char **));


char *updateLoginAPIUser(char* cookie,char* username);
//char *createSQLStatementDelete();

//printout  all uses in databse
char *getAllUsers();
//create table for normal uses
char *createUserTable();
//create table for api uses
char *createAPIUserTable();
//remove table (api user or user table)
char* removeTable(char* TableName);
//create normal user table
char *createUser(char* username,char* password,char* cookie);
//create api user
char *createAPIUser(char* username,char* password);
//update cookie value
char *updateLogin(char* cookie,char* username);
//update subscription details
char *updateSubscriptionDetails(char* consumerKey,char* accessToken,char* consumerSecret, char* username );
//get cookie value
char* getCookieValue(char* username,char* userType);
char* getPreviousCookieValue(char* username,char* userType);
//this callback function can be used to   callback handler for executeSQLStatement(...)
int callbackSelect(void *data, int argc, char **argv, char **azColName);
//this callback function is used to get cookie value from a  http response in curl
int callbackCookie(void *siteCookie, int argc, char **argv, char **azColName);
//this callback function is used to get response body data  from a  http response in curl
size_t body_callback(void *ptr, size_t size, size_t nmemb, struct url_data *data);
//this callback function is used to get response hedder data  from a  http response in curl
size_t header_callback(char *buffer,size_t size,size_t nitems,struct site_cookie *cookiec);

