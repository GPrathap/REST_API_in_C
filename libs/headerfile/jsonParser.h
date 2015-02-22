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
#pragma once

#include <stddef.h>
#include <stdbool.h>
#include "../../resources/externalLibs/headerfile/jsmn.h"
#include "./baseStruct.h"
/*
* @param  BUFFER_SIZE  json string length
*/
#define BUFFER_SIZE 40000

/*
* @param JSON_TOKENS size of jsmn array
*/
#define JSON_TOKENS 512

/**
 * Make hashmap spiting into key-value pair using given json sting
 * @param		jsonString 	json string
 * @param		list        where key-value pair is stored
 */
int addToListFromJSON(char* jsonString,struct keyValue_struct** list);

/**
 * Make hashmap spiting into key-value pair using given json sting
 * @param		jsonString 	json string
 * @param		list        where key-value pair is stored
 */
int addToListFromJSONGeneratedKeys(char* js,struct keyValue_struct** list);

/**
 * Callback function to get response body data
 * @param		buffer   response body data
 * @param		size    size of buffer
 * @param       nmumb   how many times it is triggered
 * @param       userp   pointer to some struct or buffer
 */
size_t fetch_data(void *buffer, size_t size, size_t nmemb, void *userp);

/**
 * break json string into jsmn tokens
 * @param		js   json string
 */
jsmntok_t * json_tokenise(char *js);

/**
 * break json string into jsmn tokens
 * @param		js   json string
 */
bool json_token_streq(char *js, jsmntok_t *t, char *s);

/**
 *convert jsmk token to normal string
 * @param		js   pointer to char*
 * @param      t    jsmn token
 */
char * json_token_tostr(char *js, jsmntok_t *t);
