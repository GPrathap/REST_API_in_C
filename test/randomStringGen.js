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
var randomStringGenerator;
randomStringGenerator = function () {
    var randomGen
    randomGen=this,
    /**
     *  randomGen.generateString(len)     creating a random string for given length
     *  @param        len  length of string
     * */
    randomGen.generateString = function (len) {
        var buf = [], chars = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz', charLen = chars.length;
        for (var i = 0; i < len; ++i) {
            buf.push(chars[randomGen.getRandomInt(0, charLen - 1)]);
        }
        return buf.join('');
    },
    /**
     *  randomGen.getRandomInt(min, max)     creating a random int which is between given max and min value
     *  @param        len  length of string
     * */
    randomGen.getRandomInt = function (min, max) {
            return Math.floor(Math.random() * (max - min + 1)) + min;
    },
    randomGen.getRandomString=function(len){
        return randomGen.generateString(len);
    }

};

module.exports = randomStringGenerator;