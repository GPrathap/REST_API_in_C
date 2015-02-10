/**
 * signUp
 * @param       reqbody     request body     
 * @param       url         endpoint url
 * @param       memorySize  how many bytes are to be dynamically allocated for response body
*/
char *signUp(char* reqbody,char* url,int memorySize);

/**
 * signUpRequest
 * @param       reqbody     request body     
 * @param       cookie      cookie value 
 * @param       memorySize  how many bytes are to be dynamically allocated for response body
 * @param       url         endpoint url
*/
struct response_data *signUpRequest(char* reqbody,char* cookie,int memorySize,char* url);

/**
 * signUpResponse
 * @param       reqbody     response body     
*/
char* signUpResponse(char* res);

/**
 * databaseHandlerSignUp
 * @param       reqbody     request body     
 * @param       cookie      cookie value 
*/
char* databaseHandlerSignUp(char* reqbody,char* cookie);

char *signUp(char* reqbody,char* url,int memorySize)
{

        //send a request to backend server
         struct response_data *res_data=signUpRequest(reqbody,"",memorySize,url);
         if(res_data==NULL){

            printf("<h3>Backend server not responding<h3>\n");
            return NULL;

         }
        //process response of backend server
         char* clientRes=signUpResponse(res_data->res_body);
         if(clientRes==NULL)
         {

            printf("<h3>Interanl server error<h3>\n");
            return NULL;

         }

        //user details are updated
        char* dbstatus=databaseHandlerSignUp(reqbody,res_data->res_cookie);

         if(dbstatus==NULL)
         {
            return NULL;
         }

         return "<h3>You have been successfully signed in<h3>\n";

}

char* databaseHandlerSignUp(char* reqbody,char* cookie)
{
    
}

char* signUpResponse(char* rest)
{


   
}

struct response_data *signUpRequest(char* reqbody,char* cookie,int memorySize,char* url)
{

    

}