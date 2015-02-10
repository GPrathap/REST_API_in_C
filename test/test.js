

    var benchrest = require('bench-rest');
    var fs = require('fs');
    var generateUsers = require('./generateUsers');

    /**
    * endpoint urls of each methods
    **/
    var urlConfiguration={

        "signup":"https://localhost/apimanager/user/signup",
        "login":"https://localhost/apimanager/user/login",
        "addApplication":"https://localhost/apimanager/user/addApplications",
        "addSubscription":"https://localhost/apimanager/user/addSubscription",
        "generateApplicationKey":"https://localhost/apimanager/user/generateApplicationKey"

    };

    /**
    * generateUsers(urlConfiguration,numberOfUsers) function is used to generate users
    * @param		urlConfiguration  endpoint urls
    * @param		numberOfUsers     number of random users are to be generated
    */
    var generatedUsers= new generateUsers(urlConfiguration,10);
    var userList =generatedUsers.getUserList();

    var flow = {
        main: userList
    };

    module.exports = flow;

    var runOptions = {
        limit: 1,     // concurrent connections
        iterations: 1  // number of iterations to perform
    };
    benchrest(flow, runOptions)
        .on('error', function (err, ctxName) { console.error('Failed in %s with err: ', ctxName, err); })
        .on('end', function (stats, errorCount) {
            console.log('error count: ', errorCount);
            console.log('stats', stats);
    });