#include "argparse.hpp"
#include "gol.hpp"

using namespace std;

#define DEFAULT_FPS        1
#define DEFAULT_STEPS      10
#define DEFAULT_GRID_ROWS  8
#define DEFAULT_GRID_COLS  8

struct ArgsParser : public argparse::Args
{
    string& seed                   = kwarg("s,seed", "Seed value of the random number generator").set_default(str(time(NULL)));
    double& refresh_rate           = kwarg("r,refresh_rate,fps", "Refresh rate of theg ame ").set_default(DEFAULT_FPS);
    double& steps                  = kwarg("steps", "Steps in the simulation of generations to render").set_default(DEFAULT_STEPS);
    optional<double>& simulation_s = kwarg("t,time,sim", "Simulation time of the game");
    vector<unsigned>& dims         = kwarg("d,dims", "Dimension of the grid").multi_argument().set_default(vector<unsigned>{DEFAULT_GRID_ROWS, DEFAULT_GRID_COLS});
    string& mode                   = kwarg("m,mode", "Mode of initial state, default is Random").set_default("RANDOM");
    bool& render_inplace           = flag("i,inplace", "Render the output like in a game, no scoll").set_default(false);
    bool& show_stats               = flag("stats", "Shows stats like FPS").set_default(false);
};


/* Get str and return size_t unsigned */
size_t str2unum(const char* str) {
    char* endptr;
    size_t number = strtoul(str, &endptr, 10);

    if (*endptr != '\0' || endptr == str) {
        fprintf(stderr, "Error: Invalid number format for seed %s\n", str);
        exit(EXIT_FAILURE);
    }
    return number; // All characters are valid
}

/* map requested mode in str to enum */
enum Games::Mode pattern_to_mode(const string& str)
{
    cout << "mode: " << str << endl;
    if (str.compare("RANDOM") == 0)
    {
        return Games::Mode::RANDOM;
    }
    else if (str.compare("blinker") == 0)
    {
        return Games::Mode::BLINKER;
    }
    else if (str.compare("toad") == 0)
    {
        return Games::Mode::TOAD;
    }
    else if (str.compare("beacon") == 0)
    {
        return Games::Mode::BEACON;
    }
    else
    {
        fprintf(stderr, "Return a valid mode of operation. Current selection is %s which is unsupported\n", str.c_str());
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char** argv, char** envp)
{
    auto args = argparse::parse<ArgsParser>(argc, argv);
    cout << "--------- Parameters ----------\n" << endl;

    double simtime = args.steps * (1.0 / args.refresh_rate);
    if (args.simulation_s.has_value())
    {
        simtime = args.simulation_s.value();
    }
    else
    {
        args.simulation_s = simtime;
        cout << "Corrected sim-time (seconds): " << simtime << endl;
    }

    if (args.dims.size() > 2 || args.dims[0] < 3 || args.dims[1] < 3)
    {
        fprintf(stderr, "Grid size parameter is correct. One or 2 parameters, non-zero {rows, cols}");
        exit(EXIT_FAILURE);
    }
    else if (args.dims.size() == 1)
    {
        args.dims = vector<unsigned>{ args.dims[0], args.dims[0] };
    }

    args.print();
    cout << "-------------------------------\n" << endl;

    Games::GoL gol(
        str2unum(args.seed.c_str()),
        args.dims[0],
        args.dims[1],
        args.refresh_rate,
        simtime,
        pattern_to_mode(args.mode),
        !args.render_inplace,
        args.show_stats);
    gol.run();

    if (args.render_inplace)
    {
        cout << "Done, press any key to exit " << argv[0] << endl;
        string dummy;
        std::getline(std::cin, dummy);
    }

    return EXIT_SUCCESS;
}