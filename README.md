# Conway's Game of Life #

## Tested on 
- WSL Ubuntu 22.04.2 LTS, g++ 11.4.0
- CMake 3.22.1
- Make 4.3
  
## Requirements
- C++17
- argparse library
- cmake and make

## Invoke Usage

How to use the program

```python
./gol --help #./gol -?
Usage: gol  [options...]

Options:
        -s,--seed : Seed value of the random number generator
-r,--refresh_rate,--fps : Refresh rate of theg ame  [default: 1]
          --steps : Steps in the simulation of generations to render [default: 10]
  -t,--time,--sim : Simulation time of the game [default: none]
        -d,--dims : Dimension of the grid [default: unknown]
        -m,--mode : Mode of initial state, default is Random [default: RANDOM]
     -i,--inplace : Render the output like in a game, no scoll [implicit: "true", default: false]
          --stats : Shows stats like FPS [implicit: "true", default: false]
        -?,--help : print help [implicit: "true", default: false]
```

## Demo

### FPS counter
```python
./gol -d 20 20 -r 25 -i -t 70 --stats
```
Output

https://github.com/a2nath/Conways-Game-of-Life/assets/32167617/a26dddea-ff8c-472d-9906-4fe303d99db6

### Show various generations

```python
./gol -d 20 20 -r 5
--------- Parameters ----------

            -s,--seed : 1713754852
-r,--refresh_rate,--fps : 5
      -t,--time,--sim : 1000
              --steps : 1000
            -d,--dims : 20,20
         -i,--inplace : false
            -?,--help : false
-------------------------------

seed 1713754852

. . . X X . . X . X X X . . . X . X . .
. X X . X . . X X X . X X . . . . . X .
. X X . X X X X X X X X X . X . X . X .
X X . . X . . X X X X X . . X . . . X X
. X . X X . X . . . X X . X X X X X X .
. . X X X . X X X . . X X . . X . X X .
X . X X X . X X X . X . . X X X X . . .
. . X . X X X X . . . . X X X . . . X X
. X X X . . . X . X . X X X X . X . . X
. . X X X X . X X X X . . . X . X X . X
. . . . X X . . X . . . . X X . . X X .
X . . X X X . . . . X X . . X X X X . X
. . X . X . . . . . . X . . . X X . X X
. X . . X X . . X . X X . . X X X . X X
. X . . X . . . X X . X . . . X . . . X
. X . . . X X X X X . X . . . . . . . X
X . X . X X X X X X . X X . X X X . . X
X . . . . . . . . . . . X X . . . X X X
X X . . X X X . X X X X X . X X . X X X
X X X . . X . . . X X X . X X X . . . .

X X . X X . . . . . . . . . . . . . X .
X X . . . . . . . . . . . X . X X . X .
. . . . X . . . . . . . . . . X . . X .
. . . . . . . . . . . . . . . . . . . .
. X . . . . X . . . . . . X . . . . . .
. . . . . . . . X . . . . . . . . . X X
X . . . . . . . . X . . . . . . X . . .
X . . . . . . . . X X . . . . . X X X X
. X . . . . . . . X . X . . . . X . . X
. X . . . X . X . . X X . . . . X . . X
. . X . . . . X X . . X . X . . . . . .
X . . . . . . . . . X X X X . . . . . .
. X X . . . . . . X . . X . . . . . . .
. X X . X X . . X . . X X . X . . . . .
. X X . X . . . . . . X X . X X X . . X
. X X X . . . . . . . X . . X . X . X X
X . . . X . . . . X . X . . X X X X . .
. . . X . . . . . . . . . . . . . . . .
. . X . X X X . X . . . . . . X . X . .
. . X . . . . X . . . . . X . . . X . .

. . . X X . . . . . . . . . X . X . X .
. X X X X . . . . . . . . . X X X . X .
. . . . . . . . . . . . . . X X X X . X
. . . . . . . . . . . . . . . . . . . .
. . . . . . . . . . . . . . . . . . . .
. . . . . . . . . . . . . . . . . . . X
. . . . . . . . X X X . . . . . X . . .
X X . . . . . . X X . . . . . X X . X .
X X . . . . . . X X . X . . . X X . . .
. X X . . . X X . X . X . . . . . . . .
. X . . . . X X X X . . . X . . . . . .
. . X . . . . . X X X . . X . . . . . .
X . X X . . . . . X . . . . . . . . . .
. . . . X X . . . . X . . . X . . . . .
. . . . X X . . . . X . . . X . X X X X
. . . . X . . . . . . X . . . . . . X X
X X . . X . . . . . X . . . X . X X X X
X . . X . . . . . . . . . . X . . X . .
. . X . X X X X . . . . . . . . X . . .
X . X . . . X X . . . . . . . . X X X .
```
