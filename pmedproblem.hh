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


#ifndef __GOCUP_PMEDPROBLEM_HH_
#define __GOCUP_PMEDPROBLEM_HH_

#include <string>
#include <vector>

#include "city.hh"
#include "distancematrix.hh"
#include "solution.hh"

#include "options.hh"

class PMedProblem {
    public:
        PMedProblem(
                int medians,
                int N,
                DistanceMatrix* distmat
            ) : 
            _P(medians),
            _N(N),
            _distance_matrix(distmat),
            _owner(true)
            { ; }
 
        PMedProblem() : 
            _P(0),
            _N(0),
            _distance_matrix(NULL),
            _owner(false)
            { ; }

        PMedProblem(const PMedProblem& pmp) :
            _P(pmp._P),
            _N(pmp._N),
            _distance_matrix(pmp._distance_matrix),
            _owner(false)
            { ; }

        ~PMedProblem() {
            if (_owner)
                delete _distance_matrix;
        }

        void calculate_cost(Solution& soln);

        int P() { return _P; }
        int N() { return _N; }

        DistanceMatrix* distance_matrix() {
            return _distance_matrix;
        }

    private:
        int _P;
        int _N;
        DistanceMatrix* _distance_matrix;
        bool _owner;

        PMedProblem& operator=(const PMedProblem& pmp);

        static bool read_line(std::istream& in, std::vector<int>& data);
        static void split(const std::string& tosplit, char delim, 
            std::vector<std::string>& v);
};



#endif
