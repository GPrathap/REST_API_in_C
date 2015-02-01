#include <curl/curl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "../hedder/uthash.h"
#include "../dbrequest/dbrequest.h"
#include "../json/json.h"
#include "../json/buf/buf.h"
#include "../json/jsmn/jsmn.h"

struct response_data *makeCURLRequest(char* reqbody,char* cookie,int memorySize,char* url);


