#! /bin/zsh

cd ../../../utils

gcc -c -o utils utils.c
wait

cd ../lexer/keyToken
gcc -c -o key_token key_token.c

cd ../tokens
ls

gcc -c -o token ../../utils/utils ../keyToken/key_token tokenList token.c
wait

gcc -c -o tokenList token tokenList.c
wait

cd ./test
ls
gcc -g -o tokTest ../../keyToken/key_token ../../../utils/utils ../token ../tokenList testTokens.c
wait

./tokTest
exit
