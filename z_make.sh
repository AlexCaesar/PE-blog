#!/bin/sh 
/server/php/bin/phpize --clean
/server/php/bin/phpize
./configure --with-php-config=/server/php/bin/php-config
make clean
make 
sudo make install
