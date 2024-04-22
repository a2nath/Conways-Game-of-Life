# Conway's Game of Life #

## Table of Contents
-   [Tested On](#tested-on)
-   [Modes of Operation](#modes-of-operation)
-   [Usage](#usage)
-   [Invoke Usage](#invoke-usage)
-   [Demo](#demo)

## Tested on 
- Visual Studio 2019 developer console, v16.11.34
- WSL Ubuntu 22.04.2 LTS, gcc 11.4.0

## Modes of Operation

### Console scroll output
This mode simply scrolls the console with print out of each generation in the grid. Bigger the grid, more scroll. Compile as follows:
```python
# bare minimum parameters to compile in POSIX
gcc src/interview.c src/gol.c -Iinc -o gol

# bare minimum parameters to compile in WINDOWS
cl src\interview.c src\gol.c /Iinc /Fe:gol.exe
```

### Console constant refresh
This mode refreshes the console so that the output of each generation within its grid stays in the same place. Compile as follows:
```python
# render the output inplace in POSIX
gcc src/interview.c src/gol.c -Iinc -o gol -DREFRESH_RATE=5 -DSTEPS=1000 -DRENDER_INPLACE

# render the output inplace in WINDOWS
cl src\interview.c src\gol.c /Iinc /Fe:gol.exe /DREFRESH_RATE=5 /DSTEPS=1000 /DRENDER_INPLACE
```

## Usage
Supports 4 modes of output, 3 of which are stable outputs for testing purpose. And seed value for random number generator `12345` only affects the `RANDOM` mode. 
```python
# various options to start the game in POSIX
./gol        # default is RANDOM, default seed is time(NULL)
./gol RANDOM #./gol RANDOM 12345
./gol bLiNkEr
./gol toad
./gol BEACON

```
You can also use the `-DSIMULATION_S` or SIMULATION_S parameter when compiling to set the amount of time to simulate the game. It overrides `-DSTEPS` or STEPS preprocessor switch (macro). This was supposed to be a simple project so I kept the macro switches as such, rather than making them part of the command-line arguments.

## Invoke Usage
```python
./gol -h #./gol --help
Usage:
        ./gol <optional pattern : [RANDOM, bLiNkEr, toad, BEACON] > <optional seed : num>
        Seed always comes after pattern. Need to provide pattern if providing seed. RANDOM is default
```

## Demo

```python
# This is also the contents of the run_random_stable.sh script
./gol RANDOM 1713646168
```
  
Check the output for a toroidal grid behaviour:
<details>
<summary>Output</summary>

```
RANDOM
seed 1713646168
. . X . X . . X
X . X . X X X .
. . . X X . . .
X X X . X X X X
X . X . . X . X
X X X . X . X X
. X . . . X . X
. X X X . . X .

X . . . X . . X
. X X . . . X X
. . . . . . . .
. . X . . . . .
. . . . . . . .
. . X X X . . .
. . . . X X . .
. X . X X X X X

. . . . X . . .
. X . . . . X X
. X X . . . . .
. . . . . . . .
. . X . . . . .
. . . X X X . .
. . . . . . . .
. . . X . . . X

X . . . . . X X
X X X . . . . .
X X X . . . . .
. X X . . . . .
. . . X X . . .
. . . X X . . .
. . . X . . . .
. . . . . . . .

X . . . . . . X
. . X . . . . .
. . . X . . . .
X . . . . . . .
. . . . X . . .
. . X . . . . .
. . . X X . . .
. . . . . . . X

X . . . . . . X
. . . . . . . .
. . . . . . . .
. . . . . . . .
. . . . . . . .
. . . . X . . .
. . . X . . . .
X . . . . . . X

X . . . . . . X
. . . . . . . .
. . . . . . . .
. . . . . . . .
. . . . . . . .
. . . . . . . .
. . . . . . . .
X . . . . . . X

X . . . . . . X
. . . . . . . .
. . . . . . . .
. . . . . . . .
. . . . . . . .
. . . . . . . .
. . . . . . . .
X . . . . . . X

X . . . . . . X
. . . . . . . .
. . . . . . . .
. . . . . . . .
. . . . . . . .
. . . . . . . .
. . . . . . . .
X . . . . . . X
```
</details>

## C++ Implementation
If you want a C++17 implementation, switch to the `cpp` branch and launch with the cmake system 

```python
mkdir build && cd build
cmake ..
make
./gol
```
