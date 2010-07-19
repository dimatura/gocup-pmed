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


#ifndef __GOCUP_HILLCLIMBER_HH_
#define __GOCUP_HILLCLIMBER_HH_

#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <numeric>

#include "pmedproblem.hh"
#include "pmedsolver.hh"
#include "options.hh"
#include "solution.hh"

#define BLOOM_SZ 4096

class SolutionBloomFilter {
    public:
        SolutionBloomFilter() {
            clear();
        }

        void insert(Solution &soln) {
            int key = std::accumulate(soln.begin(), soln.end(), 0);
            _bloom[hash1(key) % BLOOM_SZ] = true;
            _bloom[hash2(key) % BLOOM_SZ] = true;
            _bloom[hash3(key) % BLOOM_SZ] = true;
            _bloom[hash4(key) % BLOOM_SZ] = true;
        }

        bool test(Solution &soln) {
            int key = std::accumulate(soln.begin(), soln.end(), 0);
            return (_bloom[hash1(key) % BLOOM_SZ] &&
                    _bloom[hash2(key) % BLOOM_SZ] &&
                    _bloom[hash3(key) % BLOOM_SZ] &&
                    _bloom[hash4(key) % BLOOM_SZ]);
        }

        void clear() {
            std::fill(_bloom, _bloom + BLOOM_SZ, false);
        }
        

    private:
        size_t hash1(int key) 
        {
            return ((key*5381) + (key << 5)); 
        }

        size_t hash2(int key) 
        {
            return 131*key;
        }

        size_t hash4(int key) 
        {
            char* key2 = (char*) (&key);
            unsigned int hash = 5381;
            for (char *c = key2; c != key2+sizeof(key); ++c) {
                hash = ((hash << 5) + hash) + *c;
            }
            return hash;
        }

        size_t hash3(int key) 
        {
            return ((key << 5) ^ (key >> 27)); 
        }

        bool _bloom[BLOOM_SZ];
};

class BloomClimber : PMedSolver {
    typedef std::vector<int> Vector_int;
    typedef std::set<int> Set_int;
    typedef std::map<int, double> Map_int_dbl;

    public:
        BloomClimber(PMedProblem* pmp) :
            PMedSolver(pmp),
            _best_soln(pmp->N()),
            _current_soln(pmp->N()),
            N(pmp->N())
        { ; }

        virtual ~BloomClimber() { ; }

        virtual void solve(const Options& opt);

        virtual const Solution &best_solution() {
            return _best_soln;
        }

    private:
        SolutionBloomFilter _soln_bloom_filter;
        Solution _best_soln;
        Solution _current_soln;
        int N;
};

#endif
