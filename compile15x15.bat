@echo off
cl src\main.c src\gol.c /Iinc /DREFRESH_RATE=60 /DSTEPS=4 /Fe:gol.exe /DGRID_SIZE=15
