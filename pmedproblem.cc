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



#include <vector>
#include <cstdlib>

#include "pmedproblem.hh"

/**
 * Calculate cost of a solution from scratch.
 */
void PMedProblem::calculate_cost(Solution& soln) {
    int cost = 0;
    for (size_t i = 0; i < _distance_matrix->size(); ++i) {
        int min = INT_MAX;
        for (std::vector<int>::iterator med_iter = soln.begin(); 
                med_iter != soln.end();
                ++med_iter) {
            int d = _distance_matrix->get(i, *med_iter); 
            min = (d < min)? d : min;
        }
        cost += min;
    }
    soln.set_cost(cost);
}

