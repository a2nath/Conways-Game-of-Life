#include "argparse.hpp"
#include "gol.hpp"
#include "common.h"

using namespace std;

struct ArgsParser : public argparse::Args
{
    string& seed             = kwarg("s,seed", "Seed value of the random number generator").set_default(str(time(NULL)));
    double& refresh_rate     = kwarg("r,refresh_rate,fps", "Refresh rate of theg ame ").set_default(REFRESH_RATE);
    double& simulation_s     = kwarg("t,time,sim", "Simulation time of the game").set_default(SIMULATION_S);
    double& steps            = kwarg("steps", "Steps in the simulation of generations to render").set_default(STEPS);
    vector<unsigned>& dims   = kwarg("d,dims", "Dimension of the grid").multi_argument().set_default(vector<unsigned>{GRID_SIZE, GRID_SIZE});
    bool& render_inplace     = flag("i,inplace", "Render the output like in a game, no scoll").set_default(false);
};

int main(int argc, char** argv, char** envp)
{
    auto args = argparse::parse<ArgsParser>(argc, argv);
    cout << "--------- Parameters ----------\n" << endl;
    args.print();
    cout << "-------------------------------\n" << endl;

    Games::GoL gol(
        to_num<size_t>(args.seed),
        args.dims[0],
        args.dims[1],
        args.refresh_rate,
        args.simulation_s,
        !args.render_inplace);
    gol.run();

    if (args.render_inplace)
    {
        cout << "Done, press any key to exit " << argv[0] << endl;
        string dummy;
        std::getline(std::cin, dummy);
    }

    return EXIT_SUCCESS;
}