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


#include "vns.hh"
#include "vshop.hh"

#define KMAX 10

void VNS::solve(const Options& opt) {
    VSHOp rwvsh(_problem);
    // initial random solution
    randomize_solution(_current_soln);
    _problem->calculate_cost(_current_soln);
    rwvsh.local_search(_current_soln);
    _problem->calculate_cost(_current_soln);
    // copy current soln
    _best_soln = _current_soln;
    for (int k = 1; k < KMAX; ++k) { 
        if (opt.verbose()) {
            std::cout << "k = " << k << ", ";
            std::cout << "best: " << _best_soln;
            std::cout << std::endl;
        }
        randomize_solution(_current_soln, k);
        rwvsh.local_search(_current_soln);
        _problem->calculate_cost(_current_soln);
        if (_current_soln.cost() < _best_soln.cost()) {
            // keep best solution so far
            _best_soln = _current_soln;
        } else {
            // keep old solution and change neighborhood
            _current_soln = _best_soln;
        }
    }
}
