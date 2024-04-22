#pragma once
#include <vector>
#include <iostream>
#include <thread>
#include <chrono>
#include <iostream>
#include <time.h>
#include "common.hpp"

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

namespace Games
{
	/* Conway's Game of Life */
	class GoL
	{
		size_t seed;
		std::vector<std::vector<int>> game_grid;
		Size<size_t> size;
		double sim_time_ms;
		double frame_time_ms;
		bool is_scroll;

		inline void init_zeros(std::vector<std::vector<int>>& grid);
		inline void init_rand(std::vector<std::vector<int>>& grid);
		inline void print_row(const std::vector<std::vector<int>>& grid, int row) const;
		inline int cell_state_change(int row, int col);
	public:
		void run();
		GoL(size_t iseed, size_t grid_rows, size_t grid_col, double ifps, double isim_time, bool iscroll);
	};
}