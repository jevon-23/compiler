#! /bin/zsh

cd ../../utils

gcc -c -o utils utils.c
wait

ls
cd ../lexer
 gcc -c -o lex ../utils/utils lex.c
wait

cd ./test
gcc -o lexTest ../../utils/utils ../lex testLex.c
wait

./lexTest
exit
