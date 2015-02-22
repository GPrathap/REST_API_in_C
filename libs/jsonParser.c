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
#include <curl/curl.h>
#include <stdlib.h>

#include "./headerfile/jsonParser.h"
#include "./headerfile/makeBuffer.h"
#include "../resources/externalLibs/headerfile/uthash.h"
#include "./headerfile/log.h"

/*
get the json object as string and break it into parts according to jsmn format
json object
'{ "name" : "Jack", "age" : 27 }'

jsmn will split it into the following tokens:

    Object: { "name" : "Jack", "age" : 27} (the whole object)
    Strings: "name", "Jack", "age" (keys and some values)
    Number: 27

The key moment is that jsmn tokens do not hold any data, but just point to the token boundaries in
JSON string instead. In the example above jsmn creates tokens like:

    Object [0..31]
    String [3..7], String [12..16], String [20..23]
    Number [27..29].
*/
jsmntok_t * json_tokenise(char *js)
{
    jsmn_parser parser;
    jsmn_init(&parser);
    unsigned int n = JSON_TOKENS;
    jsmntok_t *tokens = malloc(sizeof(jsmntok_t) * n);
    log_null(tokens);
    int ret = jsmn_parse(&parser, js, tokens, n);
    while (ret == JSMN_ERROR_NOMEM)
    {
        n = n * 2 + 1;
        tokens = realloc(tokens, sizeof(jsmntok_t) * n);
        log_null(tokens);
        ret = jsmn_parse(&parser, js, tokens, n);
    }
    if (ret == JSMN_ERROR_INVAL)
        log_die("jsmn_parse: invalid JSON string");
    if (ret == JSMN_ERROR_PART)
        log_die("jsmn_parse: truncated JSON string");
    return tokens;
}

/*Compares up to (t-end-t->start) characters of the string s with  string js.*/
bool json_token_streq(char *js, jsmntok_t *t, char *s)
{
    return (strncmp(js + t->start, s, t->end - t->start) == 0
            && strlen(s) == (size_t) (t->end - t->start));
}

/*break the whole jsmn string from t->end and return t->start It means it just return a normal string*/
char * json_token_tostr(char *js, jsmntok_t *t)
{
    js[t->end] = '\0';
    return js + t->start;
}

  /*Simpley extrcat the key-value pair if json string is in this format
     *
     *
     *   { "a":value,"b":value,...
     *   }
     *
     *
     * @param		jsonString just char* (character string which is in json format as above)
     * @param		list		where key-value pair is added
     */
int addToListFromJSON(char* jsonString,struct keyValue_struct** list)
{
    //keys which are looking for
    char *KEYS[] = { "message", "error" };
    //create jsmn tokens
    jsmntok_t *tokens = json_tokenise(jsonString);
    int finalCount;
    finalCount=0;
    typedef enum { START, KEY, PRINT, SKIP, STOP } parse_state;
    parse_state state = START;
    // Counters to keep track of how far through parsing we are
    size_t object_tokens = 0;
    int count;
    count=0;
    for(size_t i = 0, j = 1; j > 0; i++, j--)
    {
        jsmntok_t *t = &tokens[i];
        // Should never reach uninitialized tokens
        log_assert(t->start != -1 && t->end != -1);
        if (t->type == JSMN_ARRAY || t->type == JSMN_OBJECT)
            j += t->size;
        switch (state)
        {
            case START:
                if (t->type != JSMN_OBJECT)
                    printf("{error:\"true\",message:\"Invalid response: root element must be an object\"}\n");
                state = KEY;
                object_tokens = t->size;
                if (object_tokens == 0)
                    state = STOP;
                break;
            case KEY:
                object_tokens--;
                if (t->type != JSMN_STRING)
                    printf("{error:\"true\",message:\"Invalid response: object keys must be strings\"}\n");
                state = SKIP;
                for (size_t i = 0; i < sizeof(KEYS)/sizeof(char *); i++)
                {
                    if (json_token_streq(jsonString, t, KEYS[i]))
                    {
                        count=i;
                        finalCount++;
                        state = PRINT;
                        break;
                    }
                }
                break;
            case SKIP:
                if (t->type != JSMN_STRING && t->type != JSMN_PRIMITIVE)
                    printf("{error:\"true\",message:\"Invalid response: object values must be strings or primitives.\"}\n");
                object_tokens--;
                state = KEY;
                if (object_tokens == 0)
                    state = STOP;
                break;
            case PRINT:
                if (t->type != JSMN_STRING && t->type != JSMN_PRIMITIVE)
                    printf("{error:\"true\",message:\"Invalid response: object values must be strings or primitives.\"}\n");
                char *str = json_token_tostr(jsonString, t);
                puts(KEYS[count]);
                puts(str);
                add_item(KEYS[count],str,list);
                object_tokens--;
                state = KEY;
                if (object_tokens == 0)
                    state = STOP;
                break;
            case STOP:
                // Just consume the tokens
                break;
            default:
                printf("{error:\"true\",message:\"Invalid response\"}\n");
                   }
    }
    return finalCount;
}

/*this is the callback function is used to get response body data*/
 size_t fetch_data(void *buffer, size_t size, size_t nmemb, void *userp)
{
    buf_t *buf = (buf_t *) userp;
    size_t total = size * nmemb;
    if (buf->limit - buf->len < total)
    {
        buf = buf_size(buf, buf->limit + total);
        log_null(buf);
    }
    buf_concat(buf, buffer, total);
    return total;
}

/* The generate key response is in this format:
     *
     *
     *   {
     *      ...,
     *      "data":
     *          {
     *             "key":
     *                  {
     *                    ....
     *                  }
     *          }
     *   }
     * @param		js      just char* (character string which is in json format as above)
     * @param		list    where key-value pair is added
     */
int addToListFromJSONGeneratedKeys(char* js,struct keyValue_struct** list){
    char *KEYS[] = { "error", "message","consumerKey","accessToken","consumerSecret"};
    jsmntok_t *tokens = json_tokenise(js);
    int count,isvalied;
    count=0,isvalied=0;
    typedef enum {
        START,
        KEY,
        SKIP,
        PRINT,
        STOP
    } parse_state;
    // state is the current state of the parser
    parse_state state = START;
    // Counters to keep track of how far through parsing we are
    size_t object_tokens = 0;
    for (size_t i = 0, j = 1; j > 0; i++, j--)
    {
        jsmntok_t *t = &tokens[i];
        // Should never reach uninitialized tokens
        log_assert(t->start != -1 && t->end != -1);
        if (t->type == JSMN_ARRAY || t->type == JSMN_OBJECT)
            j += t->size;
        switch (state)
        {
            case START:
                if (t->type != JSMN_OBJECT){
                     printf("{error:\"true\",message:\"Invalid response: root element must be an object.\"}\n");
                     state=STOP;
                     break;
                }
                state = KEY;
                object_tokens = t->size;
                if (object_tokens == 0)
                          state = STOP;
                break;
            case KEY:
                 object_tokens--;
                 if(t->type == JSMN_OBJECT){
                      state = START;
                      object_tokens = t->size;
                      break;
                 }
                 else if (t->type != JSMN_STRING){
                      printf("{error:\"true\",message:\"Invalid response: object keys must be strings.\"}\n");
                      state=STOP;
                      break;
                 }
                  state=SKIP;
                 for (size_t i = 0; i < sizeof(KEYS)/sizeof(char *); i++)
                 {
                      if (json_token_streq(js, t, KEYS[i]))
                      {
                          count=i;
                          isvalied=1;
                          state = PRINT;
                          break;
                      }else{
                          state = PRINT;
                          isvalied=0;
                      }
                 }
                 break;
            case SKIP:
                            if (t->type != JSMN_STRING && t->type != JSMN_PRIMITIVE){
                                printf("{error:\"true\",message:\"Invalid response: object keys must be strings.\"}\n");
                                state = STOP;
                                break;
                            }
                            object_tokens--;
                            state = KEY;
                            if (object_tokens == 0)
                                state = STOP;
                            break;
            case PRINT:
                 if(t->type == JSMN_OBJECT){
                      state = KEY;
                      object_tokens = t->size;
                      break;
                 }
                 if (t->type != JSMN_STRING && t->type != JSMN_PRIMITIVE)
                         log_die("Invalid response: object values must be strings or primitives.");
                 char *str = json_token_tostr(js, t);
                 if(isvalied==1 ){
                    add_item(KEYS[count],str,list);
                 }
                 object_tokens--;
                 state = KEY;
                 if (object_tokens == 0)
                      state = STOP;
                 break;
            case STOP:
                 break;
            default:
                log_die("Invalid state %u", state);
        }
    }
    return 0;
}