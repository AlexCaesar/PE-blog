#!/bin/sh 
make clean
make 
sudo make install
sudo apachectl restart
