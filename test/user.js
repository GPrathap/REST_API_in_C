
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


