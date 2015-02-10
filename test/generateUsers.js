
var User = require('./user');

var generateUsers=function(urlConfiguration,numberOfUsers){


    //Initialize User class
    this.user=new User(urlConfiguration);

    //Generate random users
    this.getUserList=function(numberOfUsers){
        var userList=[];
        var userRequests=[];
        for(var j=0;j<numberOfUsers;j++){
            userRequests=[];
            userRequests=userRequests.makeUser();
            for (var i =0;i<userRequests.length ;i++) {
                userList.push(userRequests[i]);
            };

        }
        return userList;
    }

}

