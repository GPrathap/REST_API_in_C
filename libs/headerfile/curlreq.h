#include <curl/curl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "../../resources/externalLibs/headerfile/uthash.h"
#include "./dbrequest.h"
#include "./jsonParser.h"
#include "./makeBuffer.h"
#include "../../resources/externalLibs/headerfile/jsmn.h"

/**
 * make curl request
 * @param		reqbody        request body coming from client side
 * @param       cookie         previous session cookie
 * @param       memorySize     how many bytes are to be dynamically allocated for response body
 * @param		url            destination url
 */
struct response_data *makeCURLRequest(char* reqbody,char* cookie,int memorySize,char* url );


