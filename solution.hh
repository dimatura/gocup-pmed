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


#ifndef __GOCUP_SOLUTION_HH_
#define __GOCUP_SOLUTION_HH_

#include <cstdio>
#include <cassert>

#include <vector>
#include <algorithm>
#include "bitarray.h"

class Solution {
    public:
        Solution(size_t N);
        Solution(const Solution& soln);

        std::vector<int>::iterator begin() { return _medians.begin(); }
        std::vector<int>::iterator end() { return _medians.end(); }

        Solution& operator=(const Solution& soln);

        unsigned long has_city(int c)
        {
            return (_bitarray.test(c));
        }

        int get(size_t i)
        {
            return _medians[i];
        }

        void insert(int c)
        {
            _medians.push_back(c);
            _bitarray.set(c);
        }

        void clear()
        {
            _medians.clear();
            _bitarray.clear_all();
        }

        void swap_city(int swap_in, int swap_out_ix)
        {
            _medians[swap_out_ix] = swap_in;
            // possibly faster to use change (toggle)
            _bitarray.set(swap_in);
            _bitarray.clear(_medians[swap_out_ix]);
        }

        int cost() { return _cost; }
        void set_cost(int val) { _cost = val; }
        size_t size() const { return _medians.size(); }
        bool empty() const { return _medians.empty(); }

        void print_to(FILE* fout);

    private:
        int _cost;
        std::vector<int> _medians;
        bitarray _bitarray;
        size_t _N;
};

#endif
