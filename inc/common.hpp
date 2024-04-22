#pragma once
#include <filesystem>
#include <string>
#include <sstream>

template<class T> std::string str(const T& input) { return std::to_string(input); }

template<class T>
inline T rand(T min, T max)
{
	return min + rand() % (max - min + 1);
}

inline std::string getcwd()
{
	return std::filesystem::current_path().string();
}

template<class T>
T to_num(const std::string& s)
{
	T answer;
	std::istringstream ss(s);
	ss >> answer;
	return answer;
}

// Function to sleep for the specified number of microseconds
inline void usleep(const size_t& milliseconds)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

/* Clear console screen */
void cls()
{
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

/* Either update the graphics in-place, or print in the next line (next generations) */
void cleanup(bool scroll)
{
	if (scroll)
	{
		printf("\n");
	}
	else
	{
		cls();
	}
}

template<class T>
struct Size
{
	T rows, cols;
	Size(T irows, T icols) : rows(irows), cols(icols) {}
};
