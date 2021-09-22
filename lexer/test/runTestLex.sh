#! /bin/zsh

cd ../../utils
#
gcc -c -o utils utils.c
wait
#
cd ../lexer/keyToken
gcc -c -o key_token key_token.c
#
cd ../tokens
# ls
#
gcc -c -o tokenList token tokenList.c
wait
#
gcc -c -o token ../../utils/utils ../keyToken/key_token tokenList token.c
wait

# ls
cd ..
# ls
gcc -c -o lex ../utils/utils keyToken/key_token tokens/token tokens/tokenList lex.c
wait
# #
cd ./test
ls
gcc -g -o lexTest ../../utils/utils ../keyToken/key_token ../tokens/token ../tokens/tokenList ../lex testLex.c
wait
#
./lexTest
exit
