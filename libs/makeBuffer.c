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
#include <stdlib.h>
#include <string.h>
#include "./headerfile/makeBuffer.h"


buf_t * buf_size(buf_t *buf, size_t len)
{
    if (buf == NULL)
    {
        buf = malloc(sizeof(buf_t));
        buf->data = NULL;
        buf->len = 0;
    }
    buf->data = realloc(buf->data, len);
    if (buf->len > len)
        buf->len = len;
    buf->limit = len;
    return buf;
}

void buf_push(buf_t *buf, uint8_t c)
{
    buf->data[buf->len++] = c;
}

void buf_concat(buf_t *dst, uint8_t *src, size_t len)
{
    for (size_t i = 0; i < len; i++)
        dst->data[dst->len++] = src[i];
}

char * buf_tostr(buf_t *buf)
{
    char *str = malloc(buf->len + 1);
    memcpy(str, buf->data, buf->len);
    str[buf->len] = '\0';
    return str;
}
