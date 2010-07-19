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


#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <cassert>

#include "options.hh"
#include "utils.hh"
#include "pmedproblem.hh"
#include "dataloader.hh"

#include "glhillclimber.hh"
//#include "bloomclimber.hh"

int main(int argc, char** argv) {

    // parse options
    Options opt;
    opt.parse_args(argc, argv);

    // load data
    DataLoader dataloader;
    DistanceMatrix *distancematrix = 0;

    if (opt.gocup_problem() >= 1 && opt.gocup_problem() <= 4) {
        distancematrix = dataloader.load_internal_gocup(opt.gocup_problem());
    } else {
        distancematrix = dataloader.load_external_gocup(opt.demands_file(), opt.coordinates_file());
    }

    // load problem
    PMedProblem *pmp = new PMedProblem(opt.medians(), distancematrix->size(), distancematrix);

    DMUtils::clock_seed();

    // start timing
    time_t start_t = time(NULL);

    GLHillClimber pmsolver(pmp);
    //BloomClimber pmsolver(pmp);

    pmsolver.solve(opt);

    // end timing
    time_t end_t = time(NULL);

    // print output
    Solution best_solution(pmsolver.best_solution());
    printf("Best solution: ");
    best_solution.print_to(stdout);
    printf("\n");
    printf("Wall clock time taken: %lu\n",(end_t - start_t));
    printf("\n");
    delete pmp;

    return 0;
}
