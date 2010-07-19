/**
 * Copyright (C) 2008 Daniel Maturana
 * This file is part of gocup-pmed.
 * 
 * gocup-pmed is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * gocup-pmed is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with gocup-pmed. If not, see <http://www.gnu.org/licenses/>.
 */

#include <cstdio>

#include "bloomclimber.hh"
#include "sampleinitializer.hh"
#include "vshop.hh"

#define MAX_RUNS_NO_IMPROVEMENT 100

void BloomClimber::solve(const Options& opt) {
    SampleInitializer sinit(_problem);
    _best_soln.set_cost(INT_MAX);
    int runs_without_improvement = 0;
    for (int run = 1; run <= opt.runs(); ++run) {
        VSHOp rwvsh(_problem);
        sinit.random_init(_current_soln);
        //sinit.perturbation_init(_current_soln);
        _soln_bloom_filter.insert(_current_soln);
        int max_profit = rwvsh.init(_current_soln);
        _problem->calculate_cost(_current_soln);
        while (max_profit > 0) {
            max_profit = rwvsh.local_search(_current_soln, false);
            if (_soln_bloom_filter.test(_current_soln)) {
                printf("Already seen solution\n");
                break;
            }
            _soln_bloom_filter.insert(_current_soln);
        }
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
