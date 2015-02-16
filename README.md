## REST API in C

#####REST API docs 
    
         index.html 

#####REST API installation process

###Prerequisites

1).Install Apache HTTP server 
	
		sudo apt-get install apache2

1).Install sqlite3 library

		sudo apt-get install libsqlite3-dev

3).Install curl library
    
        	sudo apt-get libcurl4-openssl-dev
        	
4).Install fcgi library
      		
      		sudo apt-get install libfcgi-dev

###How to install this application

1). First get the project repository 

	  git clone https://github.com/GPrathap/REST_API_in_C.git

2). Change these properties in endpointConfig.txt in conf directory 

    CGI_BIN 
 	Change this to your Apache HTTP server CGI_BIN location
		
		Example -: /usr/local/apache2/cgi-bin/

    DB_PATH
	Provide any location where you would like to store your database 

    ENDPOINT URLS
	Here you have to change the domain name of server where WSO2 API Manager is currently running.  


3).Add REST API endpoint urls in serverConfig.json in conf directory 

4). Go to the directory called bin
	
	 sudo chmod +x configure.sh
	 sudo ./configure.sh
	 
and follow its instructions.

Here is the sample installation process which might be helpful to install

	https://gist.github.com/GPrathap/bf4e702c72d06de76ef0
	
