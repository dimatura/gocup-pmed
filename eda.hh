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


#ifndef __GOCUP_EDA_HH_
#define __GOCUP_EDA_HH_

#include <vector>
#include <map>
#include "pmedproblem.hh"
#include "pmedsolver.hh"
#include "options.hh"
#include "solution.hh"

class EDA : PMedSolver {
    public:
        EDA(PMedProblem* pmp) :
            PMedSolver(pmp),
            _best_soln(pmp->N()),
            _current_soln(pmp->N()),
            pop(),
            stats(),
            P(pmp->P())
        { ; }

        virtual ~EDA() { ; }

        virtual void solve(const Options& opt);

        virtual const Solution &best_solution() {
            return _best_soln;
        }

    private:
        Solution _best_soln;
        Solution _current_soln;
        std::vector<Solution> pop;
        std::map<int, double> stats;
        int P;

        void generation(bool first, const Options& opt);
        void estimate(const Options& opt);
        void roulette_sampler(Solution& soln, const Options& opt);
};

#endif
