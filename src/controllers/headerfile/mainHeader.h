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
