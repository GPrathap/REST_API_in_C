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
 * send a request to backend server
 * @param       reqbody     request body
 * @param       cookie      cookie value
 * @param       memorySize  how many bytes are to be dynamically allocated for response body
 * @param       url         endpoint url
*/
struct response_data *signUpRequest(char* reqbody,char* cookie,int memorySize,char* url);
/**
 *  send a request to backend server
 * @param       reqbody     request body
 * @param       cookie      cookie value
 * @param       memorySize  how many bytes are to be dynamically allocated for response body
 * @param       url         endpoint url
*/
struct response_data *loginRequest(char* reqbody,char* cookie,int memorySize,char* url);
/**
 *  send a request to backend server
 * @param       reqbody     request body
 * @param       cookie      cookie value
 * @param       memorySize  how many bytes are to be dynamically allocated for response body
 * @param       url         endpoint url
*/
struct response_data *apiLoginRequest(char* reqbody,char* cookie,int memorySize,char* url);
/**
 *  send a request to backend server
 * @param       reqbody     request body
 * @param       cookie      cookie value
 * @param       memorySize  how many bytes are to be dynamically allocated for response body
 * @param       url         endpoint url
*/
struct response_data *addApplicationRequest(char* reqbody,char* cookie,int memorySize,char* url);
/**
 *  send a request to backend server
 * @param       reqbody     request body
 * @param       cookie      cookie value
 * @param       memorySize  how many bytes are to be dynamically allocated for response body
 * @param       url         endpoint url
*/
struct response_data *addSubscriptionRequest(char* reqbody,char* cookie,int memorySize,char* url);
/**
 *  send a request to backend server
 * @param       reqbody     request body
 * @param       cookie      cookie value
 * @param       memorySize  how many bytes are to be dynamically allocated for response body
 * @param       url         endpoint url
*/
struct response_data *generateApplicationKeyRequest(char* reqbody,char* cookie,int memorySize,char* url);
/**
 *  send a request to backend server
 * @param       reqbody     request body
 * @param       cookie      cookie value
 * @param       memorySize  how many bytes are to be dynamically allocated for response body
 * @param       url         endpoint url
*/
struct response_data *addAPIRequest(char* reqbody,char* cookie,int memorySize,char* url);
/**
 *  send a request to backend server
 * @param       reqbody     request body
 * @param       cookie      cookie value
 * @param       memorySize  how many bytes are to be dynamically allocated for response body
 * @param       url         endpoint url
*/
struct response_data *publishAPIRequest(char* reqbody,char* cookie,int memorySize,char* url);

/**
 *  process response of backend server
 * @param       res     response body of backend server
*/
char* signUpResponse(char* res);
/**
 *  process response of backend server
 * @param       res     response body of backend server
*/
char* loginResponse(char* res);
/**
 *  process response of backend server
 * @param       res     response body of backend server
*/
char* addApplicationResponse(char* res);
/**
 *  process response of backend server
 * @param       res     response body of backend server
*/
char* addSubscriptionResponse(char* res);
/**
 *  process response of backend server
 * @param       res     response body of backend server
 * @param       cookie  new session cookie value
 * @param       list    hashmap which includes response of backend server as key-value pair
*/
char* generateApplicationKeyResponse(char* res,char* cookie,struct keyValue_struct** list);
/**
 *  process response of backend server
 * @param       res     response body of backend server
*/
char* apiLoginResponse(char* res);
/**
 *  process response of backend server
 * @param       res     response body of backend server
*/
char* addAPIResponse(char* res);
/**
 *  process response of backend server
 * @param       res     response body of backend server
*/
char* publishAPIResponse(char* res);


/**
 *  update the session cookie value
 * @param       reqbody     request body
 * @param       cookie      new session cookie value
*/
char* databaseHandlerSignUp(char* reqbody,char* cookie);
/**
 *  update the session cookie value
 * @param       reqbody     request body
 * @param       cookie      new session cookie value
*/
char* databaseHandlerAPI(char* reqbody,char* cookie);
/**
 *  update the session cookie value
 * @param       cookie      new session cookie value
 * @param       username    username of the client who may be a api user or normal user
*/
char* databaseHandlerApplicaation(char* username,char* cookie);
/**
 *  update the session cookie value
 * @param       reqbody     request body
 * @param       cookie      new session cookie value
*/
char* databaseHandlerSubscription(char* reqbody,char* cookie);
/**
 *  update user access token
 * @param       list        response body
 * @param       username    username of the client who may be a api user or normal user
*/
char* databaseHandlerGenerateApplication(struct keyValue_struct** list,char* username);
/**
 *  update the session cookie value
 * @param       reqbody     request body
 * @param       cookie      new session cookie value
*/
char* databaseHandler(char* reqbody,char* cookie);
/**
 *  update the session cookie value
 * @param       cookie      new session cookie value
 * @param       username    username of the client who may be a api user or normal user
*/
char* databaseHandlerAPIadd(char* username,char* cookie);
/**
 *  update the session cookie value
 * @param       cookie      new session cookie value
 * @param       username    username of the client who may be a api user or normal user
*/
char* databaseHandlerAPIPublish(char* username,char* cookie);
