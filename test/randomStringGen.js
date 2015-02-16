
var randomStringGenerator;


randomStringGenerator = function () {


    var randomGen
    randomGen=this,
    /**
     *  randomGen.generateString(len)     creating a random string for given length
     *  @param        len  length of string
     * */
    randomGen.generateString = function (len) {
        var buf = [], chars = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz', charLen = chars.length;
        for (var i = 0; i < len; ++i) {
            buf.push(chars[randomGen.getRandomInt(0, charLen - 1)]);
        }
        return buf.join('');
    },
    /**
     *  randomGen.getRandomInt(min, max)     creating a random int which is between given max and min value
     *  @param        len  length of string
     * */
    randomGen.getRandomInt = function (min, max) {
            return Math.floor(Math.random() * (max - min + 1)) + min;
    },
    randomGen.getRandomString=function(len){
        return randomGen.generateString(len);
    }

};

module.exports = randomStringGenerator;