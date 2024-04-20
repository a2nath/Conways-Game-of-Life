#include <stdio.h>
#include <stdlib.h>
#include "gol.h"

/* show usage */
void usage(const char* program_name)
{
    printf("Usage:\n\
        %s <optional pattern : [RANDOM, bLiNkEr, toad, BEACON] > <optional seed : num>\n\
        Seed always comes after pattern. Need to provide pattern if providing seed. RANDOM is default\n", program_name);
}

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
enum Mode pattern_to_mode(const char* str)
{
    printf("%s\n", str);

    if (strcmp(str, "RANDOM") == 0)
    {
        return RANDOM;
    }
    else if (strcmp(str, "bLiNkEr") == 0)
    {
        return BLINKER;
    }
    else if (strcmp(str, "toad") == 0)
    {
        return TOAD;
    }
    else if (strcmp(str, "BEACON") == 0)
    {
        return BEACON;
    }
    else
    {
        fprintf(stderr, "Return a valid mode of operation. Current selection is %s which is unsupported\n", str);
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char* argv[])
{
    enum Mode mode = 0; // default RANDOM
    size_t seed = time(NULL);

    if (argc > 3) // for future implementation
    {
        usage(argv[0]);
        return EXIT_FAILURE;
    }
    else if (argc == 3)
    {
        if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)
        {
            usage(argv[0]);
            return EXIT_SUCCESS;
        }

        mode = pattern_to_mode(argv[1]);
        seed = str2unum(argv[2]);
    }
    else if (argc == 2)
    {
        if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)
        {
            usage(argv[0]);
            return EXIT_SUCCESS;
        }
        mode = pattern_to_mode(argv[1]);
    }
    else
    {
        printf("RANDOM\n");
    }

    // 1 arg means no arguments passed and use default

    GoL gol;
    game_init(&gol, seed, mode, REFRESH_RATE, SIMULATION_S);
    run(&gol);

    return EXIT_SUCCESS;
}
