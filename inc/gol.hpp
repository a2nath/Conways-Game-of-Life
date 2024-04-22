#pragma once
#include <vector>
#include <iostream>
#include <thread>
#include <chrono>
#include <iostream>
#include <time.h>
#include "common.hpp"

namespace Games
{
	enum class Mode
	{
		RANDOM = 0,
		BLINKER,
		TOAD,
		BEACON
	};

	/* Conway's Game of Life */
	class GoL
	{
		size_t seed;
		std::vector<std::vector<int>> game_grid;
		Size<size_t> size;
		double sim_time_ms;
		double frame_time_ms;
		bool is_scroll, stats;

		inline void init_zeros(std::vector<std::vector<int>>& grid);
		inline bool cell_state_change(int row, int col);
		inline void print() const;
		inline void random_init();
		inline void blinker_init();
		inline void toad_init();
		inline void beacon_init();
	public:
		void run();
		GoL(
			size_t iseed,
			size_t grid_rows,
			size_t grid_col,
			double ifps,
			double isim_time,
			Mode imode,
			bool iscroll,
			bool istats);
	};
}