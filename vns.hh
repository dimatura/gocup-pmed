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


#ifndef __GOCUP_VNS_HH_
#define __GOCUP_VNS_HH_

#include <iostream>
#include "pmedproblem.hh"
#include "pmedsolver.hh"
#include "options.hh"
#include "solution.hh"

class VNS : PMedSolver {
    public:
        VNS(PMedProblem* pmp) :
            PMedSolver(pmp),
            _current_soln(),
            _best_soln()
        { ; }

        virtual ~VNS() { ; }

        virtual void solve(const Options& opt);

        virtual const Solution &best_solution() {
            return _best_soln;
        }

    private:
        Solution _current_soln;
        Solution _best_soln;
};

#endif
