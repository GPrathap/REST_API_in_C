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

#include <stdint.h>
#include <stdbool.h>

/**
* @param		len   current length of buffer (used bytes)
 * @param       limit maximum length of buffer (allocated)
 * @param		data  insert bytes here
*/
typedef struct
{
    size_t len;
    size_t limit;
    uint8_t *data;
} buf_t;

/**
 * buf_size create buffer for given size
 * @param		buf   is the struct which includes length of buffer,limit of the buffer and char array
 * @param       len   length of  string to be saved
 */
buf_t * buf_size(buf_t *buf, size_t len);

/**
 * buf_push adding characters to buffer
 * @param		buf   is the struct which includes length of buffer,limit of the buffer and char array
 * @param       c     a character
 */
void buf_push(buf_t *buf, uint8_t c);

/**
 * buf_push adding characters to buffer
 * @param		buf   is the struct which includes length of buffer,limit of the buffer and char array
 * @param       data  character array
 */
void buf_concat(buf_t *buf, uint8_t *data, size_t len);

/**
 * buf_tostr    convert buffer struct into a string
 * @param		buf   is the struct which includes length of buffer,limit of the buffer and char array
 */
char * buf_tostr(buf_t *buf);



