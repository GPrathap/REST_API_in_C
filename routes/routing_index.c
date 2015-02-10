

int main(){

    /*
    initialize database connection(make a persistent connection to database) , structs
    which are to used. Initialization section, which is executed only once.
    */
    initialize();
    /*
    The FCGI_Accept blocks until a client request comes in, and then returns 0.
    If there is a system failure, or the system administrator terminates the process,
    Accept will return -1.
    */
    while (FCGI_Accept() >= 0) {

        //set the content type as text/html
        printf("Content-type: text/html\n\n");
        int i=atoi(getenv("CONTENT_LENGTH"));
        char *requestBody;
        //allocate memory for request body
        requestBody=malloc(i+2);
        //read from stdin(request body) something of i bytes to requestBody
        int lenOfRead=fread(requestBody,i,1,stdin);
        if(lenOfRead==0){

                printf("<h3>%s request is empty</h3>\n",getenv("REQUEST_METHOD"));
                return 0;

        }
        //handle request according to the request action
        handler(request);

    }
    return -1;

}


char* initialize(){
    /* Initialization. */
}

int handler(char* request){
    //split request into key-value pair
    requestBody=add_toList(request);

    //get action
    char* action=getValue("action");

    switch(action){

        case "addUser" :
            signUp(requestBody,url);
            break;

        case "login" :
            login(requestBody,url);
            break

        case "addApplication":
            addApplication(requestBody,url);
            break;

        case "addSubscription":
            addSubscription(requestBody,url);
            break;

        case "generateApplicationKey":
            generateApplicationKey(requestBody,url);
            break;

        case "addAPI":
            addAPI(requestBody,url);
            break;

        default :
            defaultHandler();

    }
    return 0;

}