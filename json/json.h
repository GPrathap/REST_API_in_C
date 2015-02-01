#pragma once

#include <stddef.h>
#include <stdbool.h>
#include "./jsmn/jsmn.h"
#include "../baseStruct/baseStruct.h"

#define BUFFER_SIZE 42768
#define JSON_TOKENS 512


/**
 * Make hashmap spliting into key-value pair using given json sting
 * @param		jsonString,js	json string
 * @param		list     where key-value pair is stored
 */
int addToListFromJSON(char* jsonString,struct keyValue_struct** list);
int addToListFromJSONGenerateKey(char* js,struct keyValue_struct** list);

/**
 * Callback function to get response body data
 * @param		buffer   respose body data
 * @param		size    size of buffer
 * @param       nmumb   how many times it is triggerd
 * @param       userp   ponter to some struct or buffer
 */
size_t fetch_data(void *buffer, size_t size, size_t nmemb, void *userp);

/**
 * break json string into jsmk tokens
 * @param		js   json string
 */
jsmntok_t * json_tokenise(char *js);

/**
 * break json string into jsmk tokens
 * @param		js   json string
 */
bool json_token_streq(char *js, jsmntok_t *t, char *s);

/**
 *convert jsmk token to normal string
 * @param		js   pointer to char*
 * @param      t    jsmn token
 */
char * json_token_tostr(char *js, jsmntok_t *t);
