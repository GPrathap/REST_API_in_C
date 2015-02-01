
var userDetailsAPI={

    action:"login",
    username:"provider1",
    password:"provider1"
}

var apiPublishDetalis={

    username:"provider1",
    name:"bnhm",
    version:"1.0.0",
    provider:"provider1",
    status:"PUBLISHED",
    publishToGateway:"true",
    action:"updateStatus"
}

var apiDetalis={

        action:"addAPI",
        name:"bnhm",
        username:"provider1",
        visibility:"public",
        version:"1.0.0",
        description:"If tabases",
        endpointType:"nonsecured",
        http_checked:"http",
        https_checked:"https",
        wsdl:"",
        tags:"wikipedia,mediawiki",
        tier:"Silver",
        thumbUrl:"https://upload.wikimedia.org/wikipedia/en/b/bc/Wiki.png",
        context:"/hjyumkl",
        tiersCollection:"Gold",
        resourceCount:"0",
        resourceMethod:"GET",
        resourceMethodAuthType:"Application",
        resourceMethodThrottlingTier:"Unlimited",
        endpoint_config:{
                production_endpoints:{
                        url:"http://en.wikipedia.org/w/api.php",
                        config:null
                                        },
                endpoint_type:"http"
                        },
        uriTemplate:"/*"
}

var userDetails={

        action:"addUser",
        username:"user37",
        password:"test123",
        cookie:"",
        firstname:"user1",
        lastname:"user2",
        phonenumber:"",
        postalcode:"",
        country:""
}

var applicatioDetails={

    action:"addApplication",
    application:"default42",
    tier:"Unlimited",
    callbackUrl:"",
    description:"",
    username:"user37"
}






var subscriptionDetails={

    action:"addAPISubscription",
    actionApp:"getApplications",
    name:"WikipediaAPIs",
    version:"1.0.0",
    provider:"provider1",
    tier:"Gold",
    username:"user37",
    applicationName:"default42"

};

var applicationKeyDetails={

    action:"generateApplicationKey",
    application:"default42",
    keytype:"PRODUCTION",
    callbackUrl:"",
    authorizedDomains:"ALL",
    validityTime:36000,
    username:"user37"


};

var fs = require('fs');
var request = require('request');




var optsSingup = {
    url: "https://localhost/apimanager/user/signup",
    method: "POST",
    ca: [fs.readFileSync('../keys/ca.crt')],
    headers: {
        "Content-Type": "application/x-www-form-urlencoded"
    },
    body:"action=addUser&username=user38&password=test123&allFieldsValues=firstname|lastname|email"

};
var optsLogin = {
    url: "https://localhost/apimanager/user/login",
    method: "POST",
    ca: [fs.readFileSync('../keys/ca.crt')],
    headers: {
        "Content-Type": "application/x-www-form-urlencoded"
    },
    form:{
        action:"login",
        username:userDetails.username,
        password:userDetails.password
    }

};
var optsAddApplication = {
    url: "https://localhost/apimanager/user/addApplications",
    method: "POST",
    ca: [fs.readFileSync('../keys/ca.crt')],
    headers: {
        "Content-Type": "application/x-www-form-urlencoded"
    },
    form:{
        action:applicatioDetails.action,
        application:applicatioDetails.application,
        tier:applicatioDetails.tier,
        callbackUrl:applicatioDetails.callbackUrl,
        description:applicatioDetails.description,
        username:applicatioDetails.username
    }

};
var optsSubscription = {
    url: "https://localhost/apimanager/user/addSubscription",
    method: "POST",
    ca: [fs.readFileSync('../keys/ca.crt')],
    headers: {
        "Content-Type": "application/x-www-form-urlencoded"
    },
    form:{
        action:subscriptionDetails.action,
        name:subscriptionDetails.name,
        version:subscriptionDetails.version,
        provider:subscriptionDetails.provider,
        tier:subscriptionDetails.tier,
        applicationName:subscriptionDetails.applicationName,
        username:subscriptionDetails.username

    }

};
var optsGetAppDetails = {
    url: "https://localhost/apimanager/user/getAppDetails",
    method: "POST",
    ca: [fs.readFileSync('../keys/ca.crt')],
    headers: {
        "Content-Type": "application/x-www-form-urlencoded"
    },
    form:{
        action:"getApplications",
        username:userDetails.username
    }

};

var optsgenerateApplicationKey = {
    headers: {
        'content-type' : 'application/x-www-form-urlencoded'
        //'Cookie':
    },
    method:"POST",
    ca: [fs.readFileSync('../keys/ca.crt')],
    url: 'https://localhost/apimanager/user/generateApplicationKey',
    form:{
        action:applicationKeyDetails.action,
        application:applicationKeyDetails.application,
        keytype:applicationKeyDetails.keytype,
        callbackUrl:applicationKeyDetails.callbackUrl,
        authorizedDomains:applicationKeyDetails.authorizedDomains,
        validityTime:applicationKeyDetails.validityTime,
        retryAfterFailure:applicationKeyDetails.retryAfterFailure,
        username:applicationKeyDetails.username
    }
};

var optsLoginAPI = {
    url: "https://localhost/apimanager/apiuser/apilogin",
    method: "POST",
    ca: [fs.readFileSync('../keys/ca.crt')],
    headers: {
        "Content-Type": "application/x-www-form-urlencoded"
    },
    form:{
        action:"login",
        username:userDetailsAPI.username,
        password:userDetailsAPI.password
    }

};


var optsaddAPI = {
    url: "https://localhost/apimanager/apiuser/addapi",
    method: "POST",
    ca: [fs.readFileSync('../keys/ca.crt')],
    headers: {
        "Content-Type": "application/x-www-form-urlencoded"
    },
    body:'action=' +apiDetalis.action+
    '&name=' +apiDetalis.name+
        '&username='+apiDetalis.username+
    '&visibility=' +apiDetalis.visibility+
    '&version=' +apiDetalis.version+
    '&description=' +apiDetalis.description+
    '&endpointType=' +apiDetalis.endpointType+
    '&http_checked=' +apiDetalis.http_checked+
    '&https_checked=' +apiDetalis.https_checked+
    '&wsdl=' +apiDetalis.wsdl+
    '&tags=' +apiDetalis.tags+
    '&tier=' +apiDetalis.tier+
    '&thumbUrl=' +apiDetalis.thumbUrl+
    '&context=' +apiDetalis.context+
    '&tiersCollection=' +apiDetalis.tiersCollection+
    '&resourceCount=' +apiDetalis.resourceCount+
    '&resourceMethod-0=' +apiDetalis.resourceMethod+
    '&resourceMethodAuthType-0=' +apiDetalis.resourceMethodAuthType+
    '&resourceMethodThrottlingTier-0=' +apiDetalis.resourceMethodThrottlingTier+
    '&endpoint_config={"production_endpoints":{"url":"' +apiDetalis.endpoint_config.production_endpoints.url+
    '","config":' +apiDetalis.endpoint_config.production_endpoints.config+
    '},"endpoint_type":"' +apiDetalis.endpoint_config.endpoint_type+
    '"}&' +
    'uriTemplate-0=' +apiDetalis.uriTemplate+
    ''

};
var optsPublishAPI = {
    url: "https://localhost/apimanager/apiuser/apipublish",
    method: "POST",
    ca: [fs.readFileSync('../keys/ca.crt')],
    headers: {
        "Content-Type": "application/x-www-form-urlencoded"
    },
    form:{
        username:apiPublishDetalis.username,
        name:apiPublishDetalis.name,
        version:apiPublishDetalis.version,
        provider:apiPublishDetalis.provider,
        status:apiPublishDetalis.status,
        publishToGateway:apiPublishDetalis.publishToGateway,
        action:apiPublishDetalis.action
    }

};

//optsSingup
//optsLogin
//optsAddApplication
//optsSubscription
//optsLoginAPI
//optsaddAPI
//optsPublishAPI
//optsGetAppDetails
//optsgenerateApplicationKey

request(optsSingup,function (err, res, body) {

    console.log('error', err);
    // console.log('status', res.statusCode);clear

    //var s=JSON.parse(body);
    console.log('body', body);

});

/*
 var fs=require("fs");
 var request = require('request');
 var userDetails={

    action:"addUser",
    username:"GPhap13",
    password:"geesara1234A",
    cookie:"",
    firstname:"user1",
    lastname:"user2",
    phonenumber:"",
    postalcode:"",
    country:""
};
 */