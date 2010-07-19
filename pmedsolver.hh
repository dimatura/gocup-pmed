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


#ifndef __GOCUP_PMEDSOLVER_HH_
#define __GOCUP_PMEDSOLVER_HH_

#include "pmedproblem.hh"
#include "options.hh"
#include "solution.hh"

class PMedSolver {
    public:
        PMedSolver(PMedProblem* pmp) :
            _problem(pmp)
            { ; }
        virtual ~PMedSolver() { ; }

        virtual void solve(const Options& opt) = 0;
        virtual const Solution& best_solution() = 0;

    protected:
        PMedSolver(const PMedSolver&);
        PMedSolver& operator=(const PMedSolver&);
        PMedProblem *_problem;
};

#endif
