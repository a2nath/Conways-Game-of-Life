#include "gol.hpp"

using namespace Games;
using namespace std;

inline void GoL::init_zeros(vector<vector<int>>& grid)
{
	for (size_t row = 0; row < size.rows; ++row)
	{
		for (size_t col = 0; col < size.cols; ++col)
		{
			grid[row][col] = 0;
		}
	}
}

/* Print the entire grid */
inline void GoL::print() const
{
	for (auto& row : game_grid)
	{
		for (auto& cell : row)
		{
			printf((cell & 0x1) ? "X " : ". ");
		}
		printf("\n");
	}
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
* True for changed (alive or dead)
* False for unchanged (keep as is)
*/
inline bool GoL::cell_state_change(int row, int col)
{
	int live_n = 0;

	// Iterate over the neighboring cells
	for (int offset_i = -1; offset_i <= 1; ++offset_i)
	{
		for (int offset_j = -1; offset_j <= 1; ++offset_j)
		{
			if (!(offset_i == 0 && offset_j == 0))
			{
				int neighbor_row = (row + offset_i + size.rows) % size.rows;
				int neighbor_col = (col + offset_j + size.cols) % size.cols;

				live_n += game_grid[neighbor_row][neighbor_col];
			}
		}
	}

	if (game_grid[row][col] == 1 && (3 < live_n || live_n < 2))
	{
		return true; // cell is dead, so flip this
	}
	else if (game_grid[row][col] == 0 && live_n == 3)
	{
		return true; // cell is reproduced, so flip this
	}

	return false; // cell is the same
}


/* Runs the render loops
*	Inputs:
*	Game object pointer
*	Return: none
*/
void GoL::run()
{
	double curr_sim_time_ms = 0;
	vector<size_t> changes_rows, changes_cols;

	changes_rows.reserve(size.rows * size.cols);
	changes_cols.reserve(size.rows * size.cols);

	cleanup(is_scroll); // the console

	auto start = std::chrono::steady_clock::now();
	size_t overhead_ms = 0;

	/* render loop to get rest of the generations */
	while (curr_sim_time_ms < sim_time_ms)
	{
		/* show the current state and counts towards 1 generation */
		print();
		auto end = std::chrono::steady_clock::now();
		overhead_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1e3;

		size_t sleep_time = max((long long)0, (long long)(frame_time_ms - overhead_ms));

		usleep(sleep_time); // sleep based on [#fps]

		start = std::chrono::steady_clock::now();
		cleanup(is_scroll);

		/* set the next state */
		for (size_t row = 0; row < size.rows; ++row)
		{
			for (size_t col = 0; col < size.cols; ++col)
			{
				if (cell_state_change(row, col))
				{
					changes_rows.emplace_back(row);
					changes_cols.emplace_back(col);
				}
			}
		}

		/* flip bits that needs changing */
		for (size_t index = 0; index < changes_rows.size(); ++index)
		{
			game_grid[changes_rows[index]][changes_cols[index]] ^= 0x1;
		}

		changes_rows.clear();
		changes_cols.clear();

		curr_sim_time_ms += overhead_ms + sleep_time;

		if (stats)
			printf("FPS: %.0f\n", 1000.0 / max(overhead_ms, (size_t)frame_time_ms));
	}

	cleanup(is_scroll);
}

inline void GoL::random_init()
{
	for (size_t row = 0; row < size.rows; ++row)
	{
		for (size_t col = 0; col < size.cols; ++col)
		{
			game_grid[row][col] = rand() % 2; // either one or zero
		}
	}
}

/* Init the BLINKER grid */
inline void GoL::blinker_init()
{
	size_t mid_row = size.rows / 2;
	size_t mid_col = size.cols / 2;

	if (mid_row - 1 >= 0 && mid_row + 1 < size.rows)
	{
		game_grid[mid_row - 1][mid_col] = 1; // don't write to illegal memory address
		game_grid[mid_row][mid_col] = 1;
		game_grid[mid_row + 1][mid_col] = 1;
	}
	else
	{
		fprintf(stderr, "Grid size is too small for this operation. \
						Size is %zux%zu and blinker_init procedure needs at least 3x3", size.rows, size.cols);
		exit(EXIT_FAILURE);
	}
}

/* Init the TOAD grid */
inline void GoL::toad_init()
{
	size_t mid_row = size.rows / 2;
	size_t mid_col = size.cols / 2;

	if (mid_row - 1 >= 0 && mid_row + 1 < size.rows
		&& mid_col - 2 >= 0 && mid_col + 1 < size.cols)
	{
		game_grid[mid_row - 1][mid_col - 1] = 1; // don't write to illegal memory address
		game_grid[mid_row - 1][mid_col] = 1;
		game_grid[mid_row - 1][mid_col + 1] = 1;

		game_grid[mid_row][mid_col - 2] = 1;
		game_grid[mid_row][mid_col - 1] = 1;
		game_grid[mid_row][mid_col] = 1;
	}
	else
	{
		fprintf(stderr, "Grid size is too small for this operation. \
						Size is %zux%zu and toad_init procedure needs at least 4x4", size.rows, size.cols);
		exit(EXIT_FAILURE);
	}
}

/* Init the BEACON grid */
inline void GoL::beacon_init()
{
	size_t mid_row = 1 * (size.rows / 4);
	size_t mid_col = 3 * (size.cols / 4); // some offset seen in requirements

	if (mid_row - 1 >= 0 && mid_row + 2 < size.rows
		&& mid_col - 3 >= 0 && mid_col < size.cols)
	{
		game_grid[mid_row - 1][mid_col - 1] = 1;
		game_grid[mid_row - 1][mid_col] = 1;
		game_grid[mid_row][mid_col - 1] = 1;
		game_grid[mid_row][mid_col] = 1;

		game_grid[mid_row + 1][mid_col - 3] = 1;
		game_grid[mid_row + 1][mid_col - 2] = 1;
		game_grid[mid_row + 2][mid_col - 3] = 1;
		game_grid[mid_row + 2][mid_col - 2] = 1;
	}
	else
	{
		fprintf(stderr, "Grid size is too small for this operation. \
						Size is %zux%zu and beacon_init procedure needs at least 4x4", size.rows, size.cols);
		exit(EXIT_FAILURE);
	}
}

GoL::GoL(size_t iseed, size_t grid_rows, size_t grid_col, double ifps, double isim_time, Mode imode, bool iscroll, bool istats) :
	seed(iseed),
	game_grid(grid_rows, vector<int>(grid_col, 0)),
	size(grid_rows, grid_col),
	sim_time_ms(1000.0 * isim_time),
	frame_time_ms(1000.0 * 1.0 / ifps),
	is_scroll(iscroll),
	stats(istats)
{
	switch (imode)
	{
	case Mode::BLINKER:
		blinker_init();
		break;
	case Mode::TOAD:
		toad_init();
		break;
	case Mode::BEACON:
		beacon_init();
		break;
	default:
		srand(seed);
		cout << "seed: " << seed << endl;
		random_init();
	}
}
