#ifndef __GOCUP_OPTIONS_HH_
#define __GOCUP_OPTIONS_HH_

#include <cstdio>
#include <cstdlib>

#define DEFAULT_RUNS 82
#define DEFAULT_MEDIANS 10

class Options {
    public:
        Options() :
            _runs(DEFAULT_RUNS),
            _medians(DEFAULT_MEDIANS),
            _demands_file(0),
            _coordinates_file(0),
            _gocup_problem(0),
            _quiet(false)
            { ; }

        void parse_args(int argc, char** argv);

        int parse_numeric_option(int c, int argc, char** argv);

        void print_usage();

        int runs() const { return _runs; }
        int medians() const { return _medians; }
        bool quiet() const { return _quiet; }
        int gocup_problem() const { return _gocup_problem; }
        const char *demands_file() const { return _demands_file; }
        const char *coordinates_file() const { return _coordinates_file; }

    private:
        int _runs;
        int _medians;
        const char* _demands_file;
        const char* _coordinates_file;
        int _gocup_problem;
        bool _quiet;
};

#endif
