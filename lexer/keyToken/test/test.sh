#! /bin/zsh

cd ../

gcc -c -o key_token key_token.c

cd test
gcc -o testKey_token ../key_token testKey_token.c

./testKey_token

exit
