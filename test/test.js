
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
