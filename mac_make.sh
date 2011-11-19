#!/bin/sh 
phpize --clean
phpize
./configure 
make clean
make 
sudo make install
