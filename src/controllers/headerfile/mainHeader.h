/**
 * all functions are listed below are used to process the desired task
 * @param       reqbody     request body
 * @param       url         endpoint url
 * @param       memorySize  how many bytes are to be dynamically allocated for response body
*/
char *signUp(char* reqbody,char* url,int memorySize);
char *login(char* reqbody,char* url,int memorySize);
char *addApplication(char* reqbody,char* url,int memorySize);
char *addSubscription(char* reqbody,char* url,int memorySize);
char *generateApplicationKey(char* reqbody,char* url,int memorySize);
char *apiLogin(char* reqbody,char* url,int memorySize);
char *addAPI(char* reqbody,char* url,int memorySize);
char *publishAPI(char* reqbody,char* url,int memorySize);

/**
 * all functions are listed below are used to send a request to backend server
 * @param       reqbody     request body
 * @param       cookie      cookie value
 * @param       memorySize  how many bytes are to be dynamically allocated for response body
 * @param       url         endpoint url
*/
struct response_data *signUpRequest(char* reqbody,char* cookie,int memorySize,char* url);
struct response_data *loginRequest(char* reqbody,char* cookie,int memorySize,char* url);
struct response_data *apiLoginRequest(char* reqbody,char* cookie,int memorySize,char* url);
struct response_data *addApplicationRequest(char* reqbody,char* cookie,int memorySize,char* url);
struct response_data *addSubscriptionRequest(char* reqbody,char* cookie,int memorySize,char* url);
struct response_data *generateApplicationKeyRequest(char* reqbody,char* cookie,int memorySize,char* url);
struct response_data *addAPIRequest(char* reqbody,char* cookie,int memorySize,char* url);
struct response_data *publishAPIRequest(char* reqbody,char* cookie,int memorySize,char* url);

/**
 * all functions are listed below are used to process response of backend server
 * @param       res     response body of backend server
 * @param       cookie  new session cookie value
 * @param       list    hashmap which includes response of backend server as key-value pair
*/
char* signUpResponse(char* res);
char* loginResponse(char* res);
char* addApplicationResponse(char* res);
char* addSubscriptionResponse(char* res);
char* generateApplicationKeyResponse(char* res,char* cookie,struct keyValue_struct** list);
char* apiLoginResponse(char* res);
char* addAPIResponse(char* res);
char* publishAPIResponse(char* res);

/**
 * all functions are listed below are used to handle the database
 * @param       reqbody     request body
 * @param       cookie      new session cookie value
 * @param       username    username of the client who may be api user or normal user
*/
char* databaseHandlerSignUp(char* reqbody,char* cookie);
char* databaseHandlerAPI(char* reqbody,char* cookie);
char* databaseHandlerApplicaation(char* username,char* cookie);
char* databaseHandlerSubscription(char* reqbody,char* cookie);
char* databaseHandlerGenerateApplication(struct keyValue_struct** list,char* username);
char* databaseHandler(char* reqbody,char* cookie);
char* databaseHandlerAPIadd(char* username,char* cookie);
char* databaseHandlerAPIPublish(char* username,char* cookie);

