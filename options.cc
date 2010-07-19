
#include <cstring>
#include "options.hh"

void Options::parse_args(int argc, char** argv) {
    if (argc < 2) {
        fprintf(stderr, "Not enough arguments\n");
        print_usage();
        exit(1);
    }

    _demands_file = _coordinates_file = 0;
    _gocup_problem = 0;

    int arg = 1;
    while (arg < argc - 1) {
        if (strcmp(argv[arg], "-h") == 0) {
            print_usage();
            exit(0);
        } else if (strcmp(argv[arg], "-r") == 0) {
            _runs = parse_numeric_option(arg, argc, argv);
            if (_runs <= 0) {
                fprintf(stderr, "Bad argument for %s\n", argv[arg]);
                exit(1);
            }
            arg += 2; // advance for option + parameter
        } else if (strcmp(argv[arg], "-d") == 0) {
            _demands_file = argv[arg + 1];
            arg += 2; // advance for option + parameter
        } else if (strcmp(argv[arg], "-c") == 0) {
            _coordinates_file = argv[arg + 1];
            arg += 2; // advance for option + parameter
        } else if (strcmp(argv[arg], "-m") == 0) {
            _medians = parse_numeric_option(arg, argc, argv);
            if (_medians <= 0) {
                fprintf(stderr, "Bad argument for %s\n", argv[arg]);
                exit(1);
            }
            arg += 2; // advance for option + parameter
        } else if (strcmp(argv[arg], "-q") == 0) {
            _quiet = true;
            arg += 1; // advance 1 for option
        } else {
            // assume it may be gocup prob argument
            if (arg == (argc - 1)) {
                _gocup_problem = strtol(argv[argc - 1], NULL, 10);
                if (_gocup_problem == 0) {
                    fprintf(stderr, "Error: %s is invalid problem number\n", argv[argc - 1]);
                    print_usage();
                    exit(1);
                }
            } else {
                fprintf(stderr, "Error: %s is an invalid argument\n", argv[arg]);
                print_usage();
                exit(1);
            }
        }
    }

    // post verification
    // it's both or none
    if (_demands_file || _coordinates_file) {
        if (!(_demands_file && _coordinates_file)) {
            fprintf(stderr, 
                    "Error: either both demands _and_ coordinate files must be specified, or none.\n");
            print_usage();
            exit(1);
        }
    } else {  
        _gocup_problem = strtol(argv[argc - 1], NULL, 10);
        if (_gocup_problem == 0) {
            fprintf(stderr, "Error: %s is invalid problem number\n", argv[argc - 1]);
            print_usage();
            exit(1);
        }
    }
    if (!(_gocup_problem || _demands_file || _coordinates_file)) {
        fprintf(stderr, "Error parsing arguments.\n");
        print_usage();
        exit(1);
    }

}

int Options::parse_numeric_option(int c, int argc, char** argv) {
    if (argc <= (c + 1)) {
        fprintf(stderr, "Error: no argument for %s\n", argv[c]);
        exit(1);
    }
    // limitation of strtol: can't tell legit 0 from error
    int num = strtol(argv[c + 1], NULL, 10);
    return num;
}

void Options::print_usage() {
    //      ---------                    80 chars approx                      ------------
    printf("PMEDIAN - Daniel Maturana, 2009\n");
    printf("Usage: pmedian [options] <problem_number>\n");
    printf("problem_number must be 1, 2, 3 o 4 to solve. This will load and solve the\n");
    printf("respective pmedian problem.\n");
    printf("For example, to solve problem 2:\n");
    printf("  pmedian 2\n");
    printf("\n");
    printf("To solve an arbitrary problem use the options -d <demands> and -c <coords>:\n");
    printf("  'demands' is a text file with the demands (weights) for each city (node).\n");
    printf("  'coords' is a text file with the coordinates for each city (node).\n");
    printf("For example:\n");
    printf("  pmedian -d demandas1.txt -c coordenadas1.txt\n");
    printf("See demandas[1..4].txt and coordenadas[1..4].txt for the format.\n");
    printf("\n");
    printf("Options: \n");
    printf("  -h            this message\n");
    printf("  -r <runs>     Number of multi start runs. Default is %d.\n", DEFAULT_RUNS);
    printf("  -m <medians>  Number of medians (P). Default is %d.\n", DEFAULT_MEDIANS);
    printf("  -q            Less verbose output. Default is false.\n");
}
