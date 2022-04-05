#!/bin/sh

if [ $# -eq 1 ]; then
    ./ifcc $1 > .main.s && as -o .main.o .main.s && gcc .main.o -o .main && ./.main
    echo $?
    rm .main.s .main.o 2> /dev/null
else
    echo "Usage: ./runner.sh your_input_file.c"
fi
