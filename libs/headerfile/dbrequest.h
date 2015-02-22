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
#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../resources/externalLibs/headerfile/uthash.h"

/**
 * when header callback  function is called this is one is used to save http cookie value
 * @param       cookie       session cookie value
 * @param       size         string length of cookie value
*/
struct site_cookie {

    size_t size;
    char* cookie;

};

/**
 * when body_callback function is called this is one is used to save http response body
 * @param       data    request or response message
 * @param       size    string length of cookie value
*/
struct url_data {

    size_t size;
    char* data;

};

/**
 *this struct is made using url_data and  site_cookie structs
 * @param       res_body    response message
 * @param       res_cookie  session cookie value
 */
struct response_data{

    char* res_body;
    char* res_cookie;

};


/**
 * is used to connected to database
 * @param		db  pointer to database
 */
int connectToDatabase(sqlite3 **db);

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

/**update user cookie value
* @param  cookie      session cookie value
* @param  username    username of the user
*/
char *updateLoginAPIUser(char* cookie,char* username);

/**printout  all users in the database*/
char *getAllUsers();

/**create user table
 * @param userType user maybe api user or user
*/
char* createUserTable(char* userType);

/**remove table (api user or user table)
* @param  tableName name of the table
*/
char* removeTable(char* tableName);

/**create a user
* @param  username name of the user
* @param  password password of the user
* @param  cookie   cookie value
*/
char *createUser(char* username,char* password,char* cookie);

/**create api user
* @param  username name of the user
* @param  password password of the user
*/
char *createAPIUser(char* username,char* password);

/**update cookie value
* @param  username name of the user
* @param  cookie   new session cookie value
*/
char *updateCookie(char* cookie,char* username);

/**update subscription details
* @param  username        name of the user
* @param  consumerKey     consumer key
* @param  accessToken     access token
* @param  consumerSecret  consumer secret key
*/
char *updateSubscriptionDetails(char* consumerKey,char* accessToken,char* consumerSecret, char* username );

/**get cookie value from database
* @param  username     name of the user
* @param  userType     user or api user
*/
char* getCookieValue(char* username,char* userType);

/**get previous cookie value from database
* @param  username     name of the user
* @param  userType     user or api user
*/
char* getPreviousCookieValue(char* username,char* userType);

/**this callback function can be used to   callback handler for executeSQLStatement(...)
*/
int callbackSelect(void *data, int argc, char **argv, char **azColName);

/**this callback function is used to get cookie value from a  http response in curl
* @param  siteCookie     cookie value
* @param  argc           number of arguments to be returned
* @param  argv           values to be returned by http curl response function
* @param  azColName
*/
int callbackCookie(void *siteCookie, int argc, char **argv, char **azColName);

/**this callback function is used to get response body from a  http response in curl
* @param  ptr            pointer to a structure which will send data when this callback function is called
* @param  size           number of arguments to be returned
* @param  nmemb          number of argument n times string length of response
* @param  data          values to be returned by http curl response
*/
size_t body_callback(void *ptr, size_t size, size_t nmemb, struct url_data *data);

/**this callback function is used to get response header from a  http response in curl
* @param  buffer       response message when this callback function is called
* @param  size         number of arguments to be returned
* @param  nitems       number of argument times string length of response
* @param  cookiec      cookie value is to saved from http curl response
*/
size_t header_callback(char *buffer,size_t size,size_t nitems,struct site_cookie *cookiec);


