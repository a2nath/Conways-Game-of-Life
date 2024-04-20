#!/bin/sh
gcc -Wall -Wextra -pedantic -std=c99 -g src/interview.c src/gol.c -Iinc -o gol -DREFRESH_RATE=4 -DSTEPS=25
./gol RANDOM 1713646168