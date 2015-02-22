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
    var benchrest;
    benchrest = require('bench-rest');
    var fs = require('fs');
    var generateUsers = require('./generateUsers');
    var Test;
    Test = function () {
        var api;
        api = this,
            api.randomUserLength=0,
            api.endpoints="",
            api.runOption = {
                limit: 1,     // concurrent connections
                iterations: 1 , // number of iterations to aperfor
                progress:10
            },
            api.setGeneratedUsers=function(len){
                api.randomUserLength=len;
                return true;
            },
            /**
            * endpoint urls of REST API
            **/
            api.setAPIEndpointList=function(fileName){

                try{
                    api.endpoints=JSON.parse(fs.readFileSync(fileName, 'utf8'));
                }catch(error){
                    console.log(error);
                }
                return true;
            },
            api.getEndpointsList=function(){
                return api.endpoints;
            },
            api.getGeneratedUsers=function(){
                var genUsers= new generateUsers(api.getEndpointsList(),api.randomUserLength);
                return genUsers.getUserRequestsList();
            },
            api.flow = function() {
                return {main: api.getGeneratedUsers()}

            },
            api.runTest=function(){
                    benchrest(api.flow(), api.runOption)
                   .on('progress', function (stats, percent, concurrent, ips) {
                       //console.log('Progress: %s   %s  %s  %s complete',percent);
                   })
                    .on('error', function (err, ctxName) {
                        console.error('Failed in %s with err: ', ctxName, err);
                    })
                    .on('end', function (stats, errorCount) {
                        console.log('error count: ', errorCount);
                        console.log('stats', stats);
                    });
            }
    };
    module.exports = Test;
    //create a instance of Test class
    testAPI = new Test();
    //set number of random users to be generated
    testAPI.setGeneratedUsers(1);
    //set REST API endpoints
    testAPI.setAPIEndpointList('../conf/serverConfig.json');
   // console.log(testAPI.getGeneratedUsers());
    //start test
    testAPI.runTest();
