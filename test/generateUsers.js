var fs =require("fs");

var User=function(userNameLen,userPasswardLen,usersList){
	this.uerNameLen=userNameLen;
	this.userPasswardLen=userPasswardLen;
	this.lenUses=usersList;
}
User.prototype.makeUserDetails=function(){

	var userDetails={
        		action:"addUser",
        		username:this.generateUserName(this.uerNameLen),
        		password:this.generateUserPassword(this.userPasswardLen),
        		cookie:"",
        		firstname:"user1",
        		lastname:"user2",
        		phonenumber:"",
        		postalcode:"",
        		country:""
		};
	return userDetails;
}
User.prototype.makeApplicationDetails=function(userName){

	var applicatioDetails={
			action:"addApplication",
    		application:this.generateUserName(),
    		tier:"Unlimited",
    		callbackUrl:"",
    		description:"",
    		username:userName
	};
	return applicatioDetails;
}
User.prototype.makeSubscriptionDetails=function(username,appDetails){

	var subscriptionDetails={
    action:"addAPISubscription",
    actionApp:"getApplications",
    name:"WikipediaAPIs",
    version:"1.0.0",
    provider:"provider1",
    tier:"Gold",
    applicationId:58,
    username:username,
		applicationName:appDetails,
    applicationKeyDetails:{
        action:"generateApplicationKey",
        application:appDetails,
        keytype:"PRODUCTION",
        callbackUrl:"",
        authorizedDomains:"ALL",
        validityTime:36000
    }
	};


	return subscriptionDetails;
}
User.prototype.makeKeyGenerationDetails=function(username,appDetails){

	var applicationKeyDetails= {
		action: "generateApplicationKey",
		application:appDetails,
		keytype: "PRODUCTION",
		callbackUrl: "",
		authorizedDomains: "ALL",
		validityTime: 36000,
		username: username

	}
	return applicationKeyDetails;
}
User.prototype.optsSingup=function(userDetails){

		var optsSingup={
    		url: "https://localhost/apimanager/user/signup",
    		method: "POST",
			ca: [fs.readFileSync('../keys/ca.crt')],
    		headers: {
        		"Content-Type": "application/x-www-form-urlencoded"
    		},
			body:"action=addUser&username="+userDetails.username+"&password="+userDetails.password+"&allFieldsValues=firstname|lastname|email"
     	};
     	return optsSingup;
}
User.prototype.optsLogin=function(userDetails){

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
		return optsLogin;
}
User.prototype.optsAddApplication=function(applicatioDetails){

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
	return optsAddApplication;
}
User.prototype.optsSubscription=function(subscriptionDetails){

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
	return optsSubscription;
}
User.prototype.optsgenerateApplicationKey=function(applicationKeyDetails){

	var optsSubscription = {
		url: "https://localhost/apimanager/user/generateApplicationKey",
		method: "POST",
		ca: [fs.readFileSync('../keys/ca.crt')],
		headers: {
			"Content-Type": "application/x-www-form-urlencoded"
		},
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
	return optsSubscription;
}
User.prototype.generateUserName=function(len){
		var buf = [], chars = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz', charlen = chars.length;
        	for (var i = 0; i < len; ++i) {
            	buf.push(chars[this.getRandomInt(0, charlen - 1)]);
        	}
        return buf.join('');
}
User.prototype.generateUserPassword=function(len){

		var buf = [], chars = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz123456789', charlen = chars.length;
        	for (var i = 0; i < len; ++i) {
            	buf.push(chars[this.getRandomInt(0, charlen - 1)]);
        	}
        return buf.join('');
        
}
User.prototype.getRandomInt=function(min,max){
		return Math.floor(Math.random() * (max - min + 1)) + min;
}
User.prototype.getUserList=function(){
		var userList=[];
		var user=[];
		for(var j=0;j<this.lenUses;j++){
			user=[];
			user=this.makeUser();
			for (var i =0;i<user.length ;i++) {
				userList.push(user[i]);
			};
			
		}
	return userList;
}
User.prototype.makeUser=function(){

	var userDetails=this.makeUserDetails();
	var optsSingup=this.optsSingup(userDetails);
	var optsLogin=this.optsLogin(userDetails);
	var applicatioDetails=this.makeApplicationDetails(userDetails.username);
	var optsAddApplication=this.optsAddApplication(applicatioDetails);
	var subscriptionDetails=this.makeSubscriptionDetails(userDetails.username,applicatioDetails.application);
	var optsSubscription=this.optsSubscription(subscriptionDetails);
	var KeyGenerationDetails=this.makeKeyGenerationDetails(userDetails.username,applicatioDetails.application);
	var optsgenerateApplicationKey=this.optsgenerateApplicationKey(KeyGenerationDetails);
	var opts=[];
	opts.push(optsSingup);
	opts.push(optsLogin);
	opts.push(optsAddApplication);
	opts.push(optsSubscription);
	opts.push(optsgenerateApplicationKey);
	return opts;
}

module.exports = User;


