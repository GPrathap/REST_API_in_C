#!/bin/sh

 # Copyright (c) 2015, WSO2 Inc. (http://www.wso2.org) All Rights Reserved.
 #
 #  WSO2 Inc. licenses this file to you under the Apache License,
 #  Version 2.0 (the "License"); you may not use this file except
 #  in compliance with the License.
 #  You may obtain a copy of the License at
 #
 #  http://www.apache.org/licenses/LICENSE-2.0
 #
 #  Unless required by applicable law or agreed to in writing,
 #  software distributed under the License is distributed on an
 #  "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 #  KIND, either express or implied. See the License for the
 #  specific language governing permissions and limitations
 #  under the License.


DB_PATH_FILE="../libs/headerfile/dbrequest.h"
CGI_BIN=""
APACHE2=""
ConfigFile="../conf/endpointConfig.txt"

while read line
do
    KEY=`echo ${line} | cut -d \= -f 1`
    VALUE=`echo ${line} | cut -d \= -f 2`
    if [ "$KEY" = "CGI-BIN" ]; then
       CGI_BIN=`echo ${VALUE} | sed -e "s/,//g"`
    elif [ "$KEY" = "APACHE2" ]; then
    	APACHE2=`echo ${VALUE} | sed -e "s/,//g"`
    fi;

done <${ConfigFile}

DB_PATH="\"$CGI_BIN/database/test.db\""
printf '#define DB_PATH %s\n' ${DB_PATH} >> ${DB_PATH_FILE}

if [ -d "$CGI_BIN" ]; then
  		echo "Now CGI scripts  are going to store in $CGI_BIN/ \n\rplease wait ..."
  		if [ -d "$CGI_BIN/database" ]; then
  			rm  "$CGI_BIN/database/test.db"
			touch "$CGI_BIN/database/test.db"
            chown www-data:www-data "$CGI_BIN/database"
            chown www-data:www-data "$CGI_BIN/database/test.db"
            echo "fun"
  		else
  			 mkdir "$CGI_BIN/database"
			 touch "$CGI_BIN/database/test.db"
			 chown www-data:www-data "$CGI_BIN/database"
             chown www-data:www-data "$CGI_BIN/database/test.db"
             echo "fun"
  		fi
fi

echo "\n\r================================== Compilation is started =========================="

set -e
make routing_index -f Makefile || exit
echo "===================================  Compilation is done ==========================\n"

if [ -z "$1" ]; then

	if [ -d "$CGI_BIN" ]; then
  		echo "Now CGI scripts  are going to store in $CGI_BIN/ \n\rplease wait ..."
  		if [ -d "$CGI_BIN" ]; then
  			 cp routing_index ${ConfigFile} "$CGI_BIN"

		fi

        if [ -d "$APACHE2" ]; then
          	echo "Now default configuration file is going to override\n"
          	if [ -d "$APACHE2/sites-available" ]; then
          			if [ -d "$APACHE2/keys" ]; then
  			 			cp  ../resources/keystore/ca.key ../resources/keystore/ca.crt  "$APACHE2/keys/"
  					else
  			 			mkdir "$APACHE2/keys"
  			 			cp  ../resources/keystore/ca.key ../resources/keystore/ca.crt  "$APACHE2/keys/"
  					fi
         			read -p "Are you alright? (y/n) " RESP
        		  	if [ "$RESP" = "y" ]; then
          					 cp ../conf/default.conf "$APACHE2/sites-available"
          					 #a2ensite 000-default.conf

          			else
          					echo "Do the changes manually as you wish\n"
          			fi
          			a2enmod proxy
					a2enmod proxy_http
					a2enmod proxy_ajp
					a2enmod rewrite
					a2enmod deflate
					a2enmod headers
					a2enmod proxy_balancer
					a2enmod proxy_connect
					a2enmod proxy_html
					service apache2 restart

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

make initConfig -f Makefile
./initConfig
