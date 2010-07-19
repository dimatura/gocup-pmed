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

#include "hillclimber.hh"
#include "sampleinitializer.hh"
#include "vshop.hh"

void HillClimber::solve(const Options& opt) {
    SampleInitializer sinit(_problem);
    VSHOp rwvsh(_problem);
    _best_soln.set_cost(INT_MAX);
    for (int run = 1; run <= opt.runs(); ++run) {
        //sinit.random_init(_current_soln);
        sinit.ADE_init(_current_soln);
        _problem->calculate_cost(_current_soln);
        int max_profit = rwvsh.init(_current_soln);
        while (max_profit > 0) {
            max_profit = rwvsh.local_search(_current_soln, false);
        }
        _problem->calculate_cost(_current_soln);
        if (_current_soln.cost() < _best_soln.cost()) {
            _best_soln = _current_soln;
        }
        if (!opt.quiet()) {
            printf("Run %d of %d; best of run: %d; overall best: %d\n",
                    run, opt.runs(), _current_soln.cost(), _best_soln.cost());
        }
    }
}
