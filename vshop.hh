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


#ifndef __GOCUP_RWVSHOPERATOR_HH_
#define __GOCUP_RWVSHOPERATOR_HH_

#include <vector>
#include <set>
#include <iostream>
#include "city.hh"
#include "distancematrix.hh"
#include "solution.hh"
#include "extramatrix.hh"
#include "pmedproblem.hh"

typedef std::vector<int> Vector_int;
typedef std::set<int> Set_int;

#define BESTNEIGHBOR_FRACTION 0.05

class VSHOp {
    public:
        VSHOp(PMedProblem* pmedproblem) : 
            N(pmedproblem->N()),
            P(pmedproblem->P()),
            distance(pmedproblem->distance_matrix()),
            gain(pmedproblem->N(), 0),
            loss(pmedproblem->P(), 0),
            extra(pmedproblem->N(), pmedproblem->P()),
            closest_ix(pmedproblem->N()),
            closest2_ix(pmedproblem->N()),
            d1(pmedproblem->N()),
            d2(pmedproblem->N()),
            affected(),
            sample(),
            sample_sz((int)(N*BESTNEIGHBOR_FRACTION)),
            iterated(0),
            penalty(pmedproblem->N())
        { ; }

        int init(Solution& solution);
        int local_search(Solution& solution, bool sampled);

    private:
        VSHOp(const VSHOp& vo);
        VSHOp& operator=(const VSHOp& vo);
        
        void reset_structures();
        void update_structures(Solution& solution);
        void undo_update_structures(Solution& solution);
        void init_closest(Solution& solution);
        void update_closest(Solution& solution, int swapped_in, int swapped_out_ix, int swapped_out);
        void find_best_neighbor(int& profit, int& swap_out_ix, int& swap_in, Solution& solution);
        void sampled_find_best_neighbor(int& profit, int& swap_out_ix, int& swap_in, Solution& solution);
        void add_penalty(Solution& soln);


        int N, P;
        DistanceMatrix* distance;

        // gain by swapping in city. size N
        Vector_int gain;
        // loss by swapping out city, size P
        Vector_int loss;
        // extra adjustment term
        ExtraMatrix extra;
        // index of city in solution solution closest to user city, sz P
        Vector_int closest_ix;
        // idem for second closest
        Vector_int closest2_ix;
        Vector_int d1, d2;
        // affected cities
        Set_int affected;

        Set_int sample;
        int sample_sz;
        int iterated;
        //penal
        Vector_int penalty;

};

#endif
