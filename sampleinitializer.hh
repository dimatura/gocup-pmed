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



#ifndef __GOCUP_SAMPLEINITIALIZER_HH_
#define __GOCUP_SAMPLEINITIALIZER_HH_

#include <vector>
#include <set>
#include <map>
#include "pmedproblem.hh"
#include "solution.hh"
#include "distancematrix.hh"

#define FRACTION 0.05 

class SampleInitializer
{
    typedef std::vector<int> Vector_int;
    typedef std::set<int> Set_int;
    typedef std::map<int, double> Map_int_dbl;
    public:
        SampleInitializer (PMedProblem* pmp) :
            N(pmp->N()),
            P(pmp->P()),
            distance(pmp->distance_matrix()),
            closest_dist(N, 0),
            sample(),
            sample_sz((int)(N*FRACTION))
            { 
            }

        void greedy_init(Solution& soln);
        void ADE_init(Solution& soln);
        void random_init(Solution& soln);
        void weighted_random_init(Solution& soln, Map_int_dbl& probs);
        void perturbation_init(Solution& soln);

    private:
        SampleInitializer(const SampleInitializer&);
        SampleInitializer& operator=(const SampleInitializer&);

        void renormalize(Map_int_dbl& probs);

        int N, P;
        DistanceMatrix* distance;
        // gain by swapping in city. size N
        Vector_int closest_dist;
        Set_int sample;
        int sample_sz;

        void update_closest(int inserted);
        int find_best_city(Solution& soln);
};

#endif
