
#include <cstdio>

#include "glhillclimber.hh"
#include "sampleinitializer.hh"
#include "vshop.hh"

#define MAX_RUNS_NO_IMPROVEMENT 100

void GLHillClimber::update_probs(Solution& soln) {
    for (Vector_int::iterator iter = soln.begin(); 
            iter != soln.end();
            ++iter) {
        _probs[*iter] += 1.;
    }
}

void GLHillClimber::solve(const Options& opt) {
    SampleInitializer sinit(_problem);
    _best_soln.set_cost(INT_MAX);
    int runs_without_improvement = 0;
    for (int run = 1; run <= opt.runs(); ++run) {
        VSHOp rwvsh(_problem);
        sinit.random_init(_current_soln);
        //sinit.perturbation_init(_current_soln);
        int max_profit = rwvsh.init(_current_soln);
        _problem->calculate_cost(_current_soln);
        while (max_profit > 0) {
            max_profit = rwvsh.local_search(_current_soln, false);
        }
        //update_probs(_current_soln);
        _problem->calculate_cost(_current_soln);
        if (_current_soln.cost() < _best_soln.cost()) {
            _best_soln = _current_soln;
            runs_without_improvement = 0;
        } else {
            ++runs_without_improvement;
            if (runs_without_improvement > MAX_RUNS_NO_IMPROVEMENT) {
                printf("%d consecutive runs without improvement, stopping.\n", 
                        MAX_RUNS_NO_IMPROVEMENT);
                break;
            }
        }
        if (!opt.quiet()) {
            printf("Run %d of %d; best of run: %d; overall best: %d\n",
                run, opt.runs(), _current_soln.cost(), _best_soln.cost());
        }
    }
}
