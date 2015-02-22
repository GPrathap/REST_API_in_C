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
var fs = require('fs');
var Rand =require('./randomStringGen');
var serviceRequest;
serviceRequest = function () {
    //initialize service request api
    var api
    api = this,
    api.randomStringLength = 0,
    api.publicKey="",

    api.setPublicKey=function(){

        api.publicKey=fs.readFileSync('../resources/keystore/ca.crt');
        return true;
    },
    api.setRandomStringLength = function (len) {

        api.randomStringLength = len;
        return true;
    },
    api.getRandomStringLength = function () {

        return api.randomStringLength;
    },
    api.getPublicKey=function(){

        return api.publicKey;
    },
    api.makeApplicationDetails = function (userName) {

        var stringLength = api.getRandomStringLength();
        return {
            action: "addApplication",
            application: api.generateString(stringLength),
            tier: "Unlimited",
            callbackUrl: "",
            description: "",
            username: userName
        }

    },
    api.makeSubscriptionDetails = function (username, appDetails) {

        return {
            action: "addAPISubscription",
            actionApp: "getApplications",
            name: "WikipediaAPIs",
            version: "1.0.0",
            provider: "provider1",
            tier: "Gold",
            applicationId: 58,
            username: username,
            applicationName: appDetails,
            applicationKeyDetails: {
                action: "generateApplicationKey",
                application: appDetails,
                keytype: "PRODUCTION",
                callbackUrl: "",
                authorizedDomains: "ALL",
                validityTime: 36000
            }
        }
    },
    api.makeKeyGenerationDetails = function (username, appDetails) {

        return {
            action: "generateApplicationKey",
            application: appDetails,
            keytype: "PRODUCTION",
            callbackUrl: "",
            authorizedDomains: "ALL",
            validityTime: 36000,
            username: username

        }

    },
    /**
     * make REST request ex:signUp,login,...
     **/
    api.optsSingUp = function (userDetails,url) {

        return {
            url: url,
            method: "POST",
            ca: [api.getPublicKey()],
            headers: {
                "Content-Type": "application/x-www-form-urlencoded"
            },
            body: "action=addUser&username=" + userDetails.username + "&password=" + userDetails.password + "&allFieldsValues=firstname|lastname|email"
        }

    },
    api.optsLogin = function (userDetails,url) {

        return {
            url: url,
            method: "POST",
            ca: [api.getPublicKey()],
            headers: {
                "Content-Type": "application/x-www-form-urlencoded"
            },
            form: {
                action: "login",
                username: userDetails.username,
                password: userDetails.password,
                tag:userDetails.tag
            }

        }
    },
    api.optsAddApplication = function (applicationDetails,url) {

        return {
            url: url,
            method: "POST",
            ca: [api.getPublicKey()],
            headers: {
                "Content-Type": "application/x-www-form-urlencoded"
            },
            form: {
                action: applicationDetails.action,
                application: applicationDetails.application,
                tier: applicationDetails.tier,
                callbackUrl: applicationDetails.callbackUrl,
                description: applicationDetails.description,
                username: applicationDetails.username
            }

        }

    },
    api.optsSubscription = function (subscriptionDetails,url) {

        return {
            url: url,
            method: "POST",
            ca: [api.getPublicKey()],
            headers: {
                "Content-Type": "application/x-www-form-urlencoded"
            },
            form: {
                action: subscriptionDetails.action,
                name: subscriptionDetails.name,
                version: subscriptionDetails.version,
                provider: subscriptionDetails.provider,
                tier: subscriptionDetails.tier,
                applicationName: subscriptionDetails.applicationName,
                username: subscriptionDetails.username

            }

        }

    },
    api.optsGenerateApplicationKey = function (applicationKeyDetails,url) {

        return {
            url: url,
            method: "POST",
            ca: [api.getPublicKey()],
            headers: {
                "Content-Type": "application/x-www-form-urlencoded"
            },
            form: {
                action: applicationKeyDetails.action,
                application: applicationKeyDetails.application,
                keytype: applicationKeyDetails.keytype,
                callbackUrl: applicationKeyDetails.callbackUrl,
                authorizedDomains: applicationKeyDetails.authorizedDomains,
                validityTime: applicationKeyDetails.validityTime,
                retryAfterFailure: applicationKeyDetails.retryAfterFailure,
                username: applicationKeyDetails.username
            }

        }

    },

    api.generateString = function (len) {
       return new Rand().getRandomString(len);
    }
};

module.exports = serviceRequest;