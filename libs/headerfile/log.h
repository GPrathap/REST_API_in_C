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

#include <string.h>
#include <errno.h>

#define STR(x) #x
#define STRINGIFY(x) STR(x)
#define LINESTR STRINGIFY(__LINE__)
#define log_assert(x) if (!(x)) log_die("%s: assertion failed: " #x \
                                        " (" __FILE__ ", line " LINESTR \
                                        ")", __func__)
#define log_null(x) log_assert(x != NULL)
#define log_debug(msg, ...) log_info("%s: " msg, __func__, ##__VA_ARGS__)
#define log_syserr(msg) log_die("%s: %s: %s", __func__, msg, strerror(errno))


void log_die(char *msg, ...);
void log_info(char *msg, ...);
