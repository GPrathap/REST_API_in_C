## REST API in C

Installation process in Rasbperry pi 

Pre requestes 

1).Install Apache HTTP server 
	
		sudo apt-get install apache2

1).Install sqlite3 library

		sudo apt-get install libsqlite3-dev

3).Install curl library
    
        sudo apt-get libcurl4-openssl-dev


How to install this application

1). First get the project repository 

	  git clone https://github.com/GPrathap/REST_API_in_C.git

2). Go to the derectoty called deployment

	 sudo chmod +x configure.sh
	 ./configure.sh
	 
and follow its instructions.

Here is the sample installation proccess which might be helpful to install 

	https://gist.github.com/GPrathap/bf4e702c72d06de76ef0
	
How to test the seperate file 

    ./configure all //this will complie all c codes and create binary objects
    
    ./configure (login|signup|addApplication|....) //this will complie only given c file into binary object

    ex-> ./configure login

 	 ./configure clean //this will remove all binary objects which have been created  
