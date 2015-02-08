#!/bin/sh
echo "\n\r================================== Compilation is started =========================="

set -e
make $1 -f Makefile || exit

echo "===================================  Compilation is done ==========================\n"

PARENTDIR=""

if [ -z "$1" ]; then 
    # Variable is empty
	read -p "Please enter path to directory where cgi-bin is located  (ex -> Ubuntu:/usr/local/apache2/cgi-bin/ ex ->Raspberry pi:/usr/lib/cgi-bin/ ) :" PARENTDIR
	if [ -d "$PARENTDIR" ]; then
  		echo "Now CGI scripts  are going to store in $PARENTDIR/apiuser \n\rplease wait ..."
  		if [ -d "$PARENTDIR/apiuser" ]; then

  			 cp addapi apipublish apilogin "$PARENTDIR/apiuser"

  		else
  			 mkdir "$PARENTDIR/apiuser"
  			 cp addapi apipublish apilogin "$PARENTDIR/apiuser"
  		fi
  		if [ -d "$PARENTDIR/user" ]; then
  			 cp login signup  addSubscription addApplications generateApplicationKey getAppDetails "$PARENTDIR/user"
  		else
  			 mkdir "$PARENTDIR/user"
  			 cp login signup  addSubscription addApplications generateApplicationKey getAppDetails "$PARENTDIR/user"
  		fi

  		read -p "Please enter path to directory where apache.conf or httpd.conf is located  (ex -> ubuntu|Raspberry pi:/etc/apache2/ ) :" PARENTDIR
        if [ -d "$PARENTDIR" ]; then
          	echo "Now default configuration file is going to override\n"
          	if [ -d "$PARENTDIR/sites-available" ]; then
          			if [ -d "$PARENTDIR/keys" ]; then
  			 			cp  ../keys/ca.key ../keys/ca.crt  "$PARENTDIR/keys/"
  					else
  			 			mkdir "$PARENTDIR/keys"
  			 			cp  ../keys/ca.key ../keys/ca.crt  "$PARENTDIR/keys/"
  					fi
         			read -p "Are you alright? (y/n) " RESP
        		  	if [ "$RESP" = "y" ]; then
          					 cp 000-default.conf "$PARENTDIR/sites-available"
          					 a2ensite 000-default.conf

          			else
          					echo "Do the changes manually as you wish\n"
          			fi
          			#a2enmod proxy
					#a2enmod proxy_http
					#a2enmod proxy_ajp
					#a2enmod rewrite
					#a2enmod deflate
					#a2enmod headers
					#a2enmod proxy_balancer
					#a2enmod proxy_connect
					#a2enmod proxy_html
					service apache2 restart
                    gcc -Wall -o initconfig initConfig.c ../baseStruct/baseStruct.c ../dbrequest/dbrequest.c -l sqlite3
                    ./initconfig
                    echo "Configuration is successfully done\n"
          	fi
          	echo "Enabling modules in apache "
          	
        else
          	echo "Provided path is not correct...\n"
        fi
	else
  		echo "Provided path is not correct...\n"
	fi
fi


