
/* Cross platform functions */
#ifdef _WIN32
#include <windows.h>
#include <conio.h>
// Sleep is defined

#else // macOS and Linux
#define _GNU_SOURCE
#include <unistd.h>
#include <time.h>

void Sleep(double milliseconds) // usleep is depr.
{
    struct timespec ts;
    ts.tv_sec = milliseconds / 1000.0;
    ts.tv_nsec = ((size_t)milliseconds % 1000) * 1000000L;
    nanosleep(&ts, NULL);
}

#endif
#include "gol.h"

/* Clear screen and move cursor to the top-left corner */
void cls()
{
#ifdef _WIN32
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = { 0, 0 };
    DWORD count;

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hStdOut, &csbi);

    FillConsoleOutputCharacter(hStdOut, ' ', csbi.dwSize.X * csbi.dwSize.Y, coord, &count);

    SetConsoleCursorPosition(hStdOut, coord);
#else
    printf("\033[2J\033[1;1H");
#endif
}

/* Either update the graphics in-place, or print in the next line (next generations) */
void cleanup()
{
#ifndef RENDER_INPLACE
    printf("\n");
#else
    cls();
#endif
}

/*
* Decide whether to toggle the cell state (alive/dead)
*
* Input:
* GoL object
* row of the cell
* col of the cell
*
* Return:
* 1 for alive
* 0 for dead
* grid[row][col] for unchanged
*/
int cell_state_change(struct GoL* gol, int row, int col)
{
    int live_n = 0;

    // Iterate over the neighboring cells
    for (int offset_i = -1; offset_i <= 1; ++offset_i)
    {
        for (int offset_j = -1; offset_j <= 1; ++offset_j)
        {
            if (!(offset_i == 0 && offset_j == 0))
            {
                int neighbor_row = (row + offset_i) % GRID_SIZE;
                int neighbor_col = (col + offset_j) % GRID_SIZE;

                // Handle negative indices by adding GRID_SIZE if necessary
                if (neighbor_row < 0)
                {
                    neighbor_row += GRID_SIZE;
                }

                if (neighbor_col < 0)
                {
                    neighbor_col += GRID_SIZE;
                }

                live_n += gol->grid[neighbor_row][neighbor_col];
            }
        }
    }

    if (gol->grid[row][col] == 1 && (3 < live_n || live_n < 2))
    {
        return 0; // cell is dead
    }
    else if (gol->grid[row][col] == 0 && live_n == 3)
    {
        return 1; // cell is reproduced
    }

    return gol->grid[row][col]; // cell is the same
}

/* Init the RANDOM grid with random numbers */
void rand_init(struct GoL* gol)
{
    for (int row = 0; row < GRID_SIZE; ++row)
    {
        for (int col = 0; col < GRID_SIZE; ++col)
        {
            gol->grid[row][col] = rand() % 2; // either one or zero
        }
    }
}

/* Init the BLINKER grid */
void blinker_init(struct GoL* gol)
{
    int mid_row = GRID_SIZE / 2;
    int mid_col = GRID_SIZE / 2;

    if (mid_row - 1 >= 0 && mid_row + 1 < GRID_SIZE)
    {
        gol->grid[mid_row - 1][mid_col] = 1; // don't write to illegal memory address
        gol->grid[mid_row    ][mid_col] = 1;
        gol->grid[mid_row + 1][mid_col] = 1;
    }
    else
    {
        fprintf(stderr, "Grid size is too small for this operation. \
                        Size is %dx%d and blinker_init procedure needs at least 3x3", GRID_SIZE, GRID_SIZE);
        exit(EXIT_FAILURE);
    }
}

/* Init the TOAD grid */
void toad_init(struct GoL* gol)
{
    int mid_row = GRID_SIZE / 2;
    int mid_col = GRID_SIZE / 2;

    if (mid_row - 1 >= 0 && mid_row + 1 < GRID_SIZE
        && mid_col - 2 >= 0 && mid_col + 1 < GRID_SIZE)
    {
        gol->grid[mid_row - 1][mid_col - 1] = 1; // don't write to illegal memory address
        gol->grid[mid_row - 1][mid_col    ] = 1;
        gol->grid[mid_row - 1][mid_col + 1] = 1;

        gol->grid[mid_row    ][mid_col - 2] = 1;
        gol->grid[mid_row    ][mid_col - 1] = 1;
        gol->grid[mid_row    ][mid_col    ] = 1;
    }
    else
    {
        fprintf(stderr, "Grid size is too small for this operation. \
                        Size is %dx%d and toad_init procedure needs at least 4x4", GRID_SIZE, GRID_SIZE);
        exit(EXIT_FAILURE);
    }
}

/* Init the BEACON grid */
void beacon_init(struct GoL* gol)
{
    int mid_row = 1 * (GRID_SIZE / 4);
    int mid_col = 3 * (GRID_SIZE / 4); // some offset seen in requirements

    if (mid_row - 1 >= 0 && mid_row + 2 < GRID_SIZE
        && mid_col - 3 >= 0 && mid_col < GRID_SIZE)
    {
        gol->grid[mid_row - 1][mid_col - 1] = 1;
        gol->grid[mid_row - 1][mid_col    ] = 1;
        gol->grid[mid_row    ][mid_col - 1] = 1;
        gol->grid[mid_row    ][mid_col    ] = 1;

        gol->grid[mid_row + 1][mid_col - 3] = 1;
        gol->grid[mid_row + 1][mid_col - 2] = 1;
        gol->grid[mid_row + 2][mid_col - 3] = 1;
        gol->grid[mid_row + 2][mid_col - 2] = 1;
    }
    else
    {
        fprintf(stderr, "Grid size is too small for this operation. \
                        Size is %dx%d and beacon_init procedure needs at least 4x4", GRID_SIZE, GRID_SIZE);
        exit(EXIT_FAILURE);
    }
}

/* Print one row of the grid */
void print_row(struct GoL* gol, int row)
{
    for (int col = 0; col < GRID_SIZE; ++col)
    {
        printf(gol->grid[row][col] ? "X " : ". ");
    }
    printf("\n");
}

/* Runs the render loops
   Inputs:
      Game object pointer
   Return: none
*/
void run(struct GoL* gol)
{
    double curr_sim_time_ms = 0;

    cleanup(); // the console

    /* show the initial state and counts towards 1 generation */
    for (int row = 0; row < GRID_SIZE; ++row)
    {
        print_row(gol, row);
    }
    curr_sim_time_ms += gol->frame_time_ms;

    /* render loop to get rest of the generations */
    while (curr_sim_time_ms < gol->sim_time_ms)
    {
        int newgrid[GRID_SIZE][GRID_SIZE];

        Sleep(gol->frame_time_ms); // sleep based on [#fps]
        cleanup();

        /* initialize each time */
        for (int row = 0; row < GRID_SIZE; ++row)
        {
            for (int col = 0; col < GRID_SIZE; ++col)
            {
                newgrid[row][col] = 0;
            }
        }

        /* set the next state */
        for (int row = 0; row < GRID_SIZE; ++row)
        {
            for (int col = 0; col < GRID_SIZE; ++col)
            {
                newgrid[row][col] = cell_state_change(gol, row, col);
            }
        }

        /* deep copy new state into original grid */
        for (int row = 0; row < GRID_SIZE; ++row)
        {
            for (int col = 0; col < GRID_SIZE; ++col)
            {
                gol->grid[row][col] = newgrid[row][col];
            }
            print_row(gol, row);
        }

        curr_sim_time_ms += gol->frame_time_ms;
    }

    cleanup();
}

/* Calls the init functions
   Inputs:
      Game object pointer
      Mode of game {RANDOM, BLINKER, TOAD, BEACON}
      Render FPS
      Length of time to simulate [#seconds]
   Return: none
*/
void game_init(struct GoL* gol, size_t seed, enum Mode imode, double ifps, double isim_time)
{
    gol->sim_time_ms = 1000.0 * isim_time;
    gol->frame_time_ms = 1000.0 * 1.0 / ifps; // frame_time_ms based on frame rate
    gol->seed = seed;
    gol->mode = imode;

    /* initialize all to 0 (in case not RANDOM) */
    if (gol->mode != RANDOM)
    {
        for (int row = 0; row < GRID_SIZE; ++row)
        {
            for (int col = 0; col < GRID_SIZE; ++col)
            {
                gol->grid[row][col] = 0;
            }
        }
    }

    switch (gol->mode)
    {
    case BLINKER:
        blinker_init(gol);
        break;
    case TOAD:
        toad_init(gol);
        break;
    case BEACON:
        beacon_init(gol);
        break;
    default:
        srand(gol->seed);
        printf("seed %zu\n", gol->seed);
        rand_init(gol);
    }
}