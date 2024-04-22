#include "gol.hpp"

using namespace Games;

inline void GoL::init_zeros(std::vector<std::vector<int>>& grid)
{
	for (size_t row = 0; row < size.rows; ++row)
	{
		for (size_t col = 0; col < size.cols; ++col)
		{
			grid[row][col] = 0;
		}
	}
}

inline void GoL::init_rand(std::vector<std::vector<int>>& grid)
{
	for (size_t row = 0; row < size.rows; ++row)
	{
		for (size_t col = 0; col < size.cols; ++col)
		{
			grid[row][col] = rand() % 2; // either one or zero
		}
	}
}

/* Print one row of the grid */
inline void GoL::print_row(const std::vector<std::vector<int>>& grid, int row) const
{
	for (size_t col = 0; col < size.cols; ++col)
	{
		printf(grid[row][col] ? "X " : ". ");
	}
	printf("\n");
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
inline int GoL::cell_state_change(int row, int col)
{
	int live_n = 0;

	// Iterate over the neighboring cells
	for (int offset_i = -1; offset_i <= 1; ++offset_i)
	{
		for (int offset_j = -1; offset_j <= 1; ++offset_j)
		{
			if (!(offset_i == 0 && offset_j == 0))
			{
				int neighbor_row = (row + offset_i) % size.rows;
				int neighbor_col = (col + offset_j) % size.cols;

				// Handle negative indices by adding GRID_SIZE if necessary
				if (neighbor_row < 0)
				{
					neighbor_row += size.rows;
				}

				if (neighbor_col < 0)
				{
					neighbor_col += size.cols;
				}

				live_n += game_grid[neighbor_row][neighbor_col];
			}
		}
	}

	if (game_grid[row][col] == 1 && (3 < live_n || live_n < 2))
	{
		return 0; // cell is dead
	}
	else if (game_grid[row][col] == 0 && live_n == 3)
	{
		return 1; // cell is reproduced
	}

	return game_grid[row][col]; // cell is the same
}


/* Runs the render loops
*	Inputs:
*	Game object pointer
*	Return: none
*/
void GoL::run()
{
	double curr_sim_time_ms = 0;

	cleanup(is_scroll); // the console

	/* show the initial state and counts towards 1 generation */
	for (size_t row = 0; row < size.rows; ++row)
	{
		print_row(game_grid, row);
	}
	curr_sim_time_ms += frame_time_ms;

	/* render loop to get rest of the generations */
	while (curr_sim_time_ms < sim_time_ms)
	{
		std::vector<std::vector<int>> newgrid(size.rows, std::vector<int>(size.cols, 0));

		usleep(frame_time_ms); // sleep based on [#fps]
		cleanup(is_scroll);

		/* initialize each time */
		init_zeros(newgrid);

		/* set the next state */
		for (size_t row = 0; row < size.rows; ++row)
		{
			for (size_t col = 0; col < size.cols; ++col)
			{
				newgrid[row][col] = cell_state_change(row, col);
			}
		}

		/* deep copy new state into original grid */
		for (size_t row = 0; row < size.rows; ++row)
		{
			for (size_t col = 0; col < size.cols; ++col)
			{
				game_grid[row][col] = newgrid[row][col];
			}
			print_row(game_grid, row);
		}

		curr_sim_time_ms += frame_time_ms;
	}

	cleanup(is_scroll);
}

GoL::GoL(size_t iseed, size_t grid_rows, size_t grid_col, double ifps, double isim_time, bool iscroll) :
	seed(iseed),
	game_grid(grid_rows, std::vector<int>(grid_col, 0)),
	size(grid_rows, grid_col),
	sim_time_ms(1000.0 * isim_time),
	frame_time_ms(1000.0 * 1.0 / ifps),
	is_scroll(iscroll)
{
	srand(seed);
	std::cout << "seed " << seed << std::endl;

	init_rand(game_grid);
}