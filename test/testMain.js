var benchrest = require('bench-rest');
  //var flow = 'https://localhost:3000/';  // can use as simple single GET
var fs = require('fs');
var User = require('./generateUsers');
  // OR more powerfully define an array of REST operations with substitution
  // This does a unique PUT and then a GET for each iteration
var user =new User(6,7,1);


var userList=user.getUserList();

//console.log(userList);

  var flow = {
    main: userList
  };


  // if the above flow will be used with the command line runner or
  // programmatically from a separate file then export it.
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

