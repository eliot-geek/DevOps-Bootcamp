#!/bin/bash
gcc hello.c -lfcgi -o mini_server
service nginx start
spawn-fcgi -p 8080 ./mini_server
/bin/bash

#gcc -o mini_server hello.c -I/Users/atruskat/.brew/Cellar/fcgi/2.4.2/include -L/Users/atruskat/.brew/Cellar/fcgi/2.4.2/lib -lfcgi
#spawn-fcgi -p 8080 -n mini_server  