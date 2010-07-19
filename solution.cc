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


#include "solution.hh"

Solution::Solution(size_t N) :
    _cost(0),
    _medians(),
    _bitarray(N),
    _N(N)
{
}

Solution::Solution(const Solution& soln) :
    _cost(soln._cost),
    _medians(soln._medians),
    _bitarray(soln._N),
    _N(soln._N)
{
    std::copy(soln._bitarray.f_, soln._bitarray.f_ + soln._bitarray.nfw_, _bitarray.f_);
}

Solution& Solution::operator=(const Solution& soln)
{
    if (&soln == this) {
        return *this;
    }
    _medians.clear();
    _medians = soln._medians;
    _cost = soln._cost;
    std::copy(soln._bitarray.f_, soln._bitarray.f_ + soln._bitarray.nfw_, _bitarray.f_);
    return *this;
}

void Solution::print_to(FILE* fout)
{
    fprintf(fout, "[");
    std::vector<int> _medians_copy(_medians);
    std::sort(_medians_copy.begin(), _medians_copy.end());
    for (int m = 0; (size_t) m < _medians_copy.size(); ++m) {
        fprintf(fout, "%d ", _medians_copy[m] + 1);
    }
    fprintf(fout, "], cost: %d", _cost);
}
