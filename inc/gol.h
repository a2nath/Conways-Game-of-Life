#ifndef GOL_H
#define GOL_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/* To change the size of the grid
* In the compiler add, -DGRID_SIZE=X in [#count]
* Default: 8x8
*/
#ifndef GRID_SIZE
#define GRID_SIZE 8
#endif

/* To refesh screen at some REFRESH_RATE
* In the compiler add, -DRENDER_INPLACE and optionally -DREFRESH_RATE=X in [#fps]
* Default: 1 [#fps]
*/
#ifndef REFRESH_RATE
#define REFRESH_RATE 1
#endif

/* To set length of simulation set the [#steps] or generations
* In the compiler add, -DSTEPS=X in [#steps]
* Default: 1000 [#steps]
*/
#ifndef STEPS
#define STEPS 1000
#endif

/* Explicitly specify the simulation time in seconds
* In the compiler add, -DSIMULATION_S=X in [seconds]
* Default: 1000 [seconds] or 1000[#steps] x 1/1[#fps]
*/
#ifndef SIMULATION_S
#define SIMULATION_S STEPS * 1.0/REFRESH_RATE
#endif

enum Mode
{
    RANDOM = 0,
    BLINKER,
    TOAD,
    BEACON
};

// Definition of GoL struct
typedef struct GoL
{
    int grid[GRID_SIZE][GRID_SIZE];
    double sim_time_ms;
    double frame_time_ms;
    size_t seed;
    enum Mode mode;

    void (*cell_state_change)(struct GoL*, int, int);
    void (*rand_init)(struct GoL*);
    void (*blinker_init)(struct GoL*);
    void (*toad_init)(struct GoL*);
    void (*beacon_init)(struct GoL*);
    void (*print_row)(struct GoL*, int);
    void (*run)(struct GoL*);
    void (*game_init)(struct GoL*, size_t, enum Mode, double, double);
} GoL;

// Function prototypes
int cell_state_change(struct GoL* gol, int row, int col);
void rand_init(struct GoL* gol);
void blinker_init(struct GoL* gol);
void toad_init(struct GoL* gol);
void beacon_init(struct GoL* gol);
void print_row(struct GoL* gol, int row);
void run(struct GoL* gol);
void game_init(struct GoL* gol, size_t seed, enum Mode imode, double ifps, double isim_time);

#endif // !GOL_H