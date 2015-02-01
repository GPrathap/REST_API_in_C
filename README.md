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
	  
2). Go to the dbrequest directory and in dbrequest.h change the path to the database 

          ex: #define DB_PATH /home/pi/project/database/test.db	  

3). Go to the directory called deployment

	 sudo chmod +x configure.sh
	 ./configure.sh
	 
and follow its instructions.

Here is the sample installation process which might be helpful to install

	https://gist.github.com/GPrathap/bf4e702c72d06de76ef0
	
How to test a separate file

       ./configure all //this will compile all c codes and create binary objects
    
       ./configure (login|signup|addApplication|....) //this will compile only given c file into binary object           ex-> ./configure login
    
       ./configure clean //this will remove all binary objects which have been created  
