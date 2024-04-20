@echo off
cl src\interview.c src\gol.c /Iinc /DREFRESH_RATE=60 /DSTEPS=4 /Fe:gol.exe
