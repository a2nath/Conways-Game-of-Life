@echo off
cl src\main.c src\gol.c /Iinc /DREFRESH_RATE=1 /DSTEPS=10 /Fe:gol.exe /DRENDER_INPLACE
