
var User = require('./user');
var RESTfulRequest = require('./RESTfulRequest');
var generateUsers;

/**
 * generateUsers(urlConfiguration,numberOfUsers) class is used to generate users
 * @param        urlConfig                       endpoint urls
 * @param        numberOfUsers                   number of random users are to be generated
 */

generateUsers = function (urlConfig,numberOfUsers) {

    var api;
    //create a instance of restful request class
    var restRequests =new RESTfulRequest();
    restRequests.setPublicKey();
    restRequests.setRandomStringLength(8);
    api = this,
    //initialize User class
    api.user = new User(),
    api.numberOfUser=numberOfUsers,

    /**
     * make a requests list which includes all REST requests which have been created from api.createUserRequests()
     * */
     api.getUserRequestsList = function () {
        var usersRequestsList = [];
        var userRequests = [];
        for (var j = 0; j < api.numberOfUser; j++) {
            userRequests = [];
            userRequests =api.createUserRequests();
            for (var i = 0; i < userRequests.length; i++) {
                usersRequestsList.push(userRequests[i]);
            }
        }
        return usersRequestsList;
    },

    /**
    *  making REST Requests
     * */
    api.createUserRequests = function () {

            var userDetails=api.user.createUserDetails();
            var optsSingUp=restRequests.optsSingUp(userDetails,urlConfig.signUp);
            var optsLogin=restRequests.optsLogin(userDetails,urlConfig.login);
            var applicationDetails=restRequests.makeApplicationDetails(userDetails.username);
            var optsAddApplication=restRequests.optsAddApplication(applicationDetails,urlConfig.addApplication);
            var subscriptionDetails=restRequests.makeSubscriptionDetails(userDetails.username,applicationDetails.application);
            var optsSubscription=restRequests.optsSubscription(subscriptionDetails,urlConfig.addSubscription);
            var KeyGenerationDetails=restRequests.makeKeyGenerationDetails(userDetails.username,applicationDetails.application);
            var optsGenerateApplicationKey=restRequests.optsGenerateApplicationKey(KeyGenerationDetails,urlConfig.generateApplicationKey);
            var opts=[];
            opts.push(optsSingUp);
            opts.push(optsLogin);
            opts.push(optsAddApplication);
            opts.push(optsSubscription);
            opts.push(optsGenerateApplicationKey);
            return opts;
    }

};

module.exports = generateUsers;

