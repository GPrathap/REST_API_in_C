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
    var RandomStringGenerator =require('./randomStringGen');
    var randStringGen = new RandomStringGenerator();
    //user class
    var User;
    User = function () {
        var randomStringLength=6;
        var  randomString="";
        var user
        user=this,
        user.makeUserDetails = function () {
                user.setRandomString();
                return {
                    action: "addUser",
                    username:user.getRandomString(),
                    password:user.getRandomString(),
                    tag:"normal",
                    cookie: "",
                    firstname: "user1",
                    lastname: "user2",
                    phonenumber: "",
                    postalcode: "",
                    country: ""
                }
        },
        user.setRandomString=function(){
            randomString=randStringGen.getRandomString(randomStringLength);
            return true;
        },
        user.getRandomString=function(){
            return randomString;
        },
        user.createUserDetails=function(){
            return user.makeUserDetails();
        }
    };

    module.exports = User;


