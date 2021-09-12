#! /bin/zsh
cd ..

gcc -c -o utils utils.c
wait

ls
cd tests
wait

ls
gcc -g -o uTest ../utils uTest.c
wait

./uTest
exit
