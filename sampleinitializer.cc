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



#include <numeric>
#include <iterator>
#include <algorithm>
#include "sampleinitializer.hh"
#include "utils.hh"

#define BIGNUM 1000000

void SampleInitializer::greedy_init(Solution& soln) {
    // make sure soln is clean
    soln.clear();
    // fill closest dist with 'infinite' value since there's
    // no cities to go
    std::fill(closest_dist.begin(), closest_dist.end(), BIGNUM);
    while (soln.size() < (size_t) P) {
        int best = find_best_city(soln);
        soln.insert(best);
        update_closest(best);
    }
}

void SampleInitializer::ADE_init(Solution& soln) {
    static int calls = 0;
    soln.clear();
    while (soln.size() < (size_t) P) {
        int c = (calls + 100)%N;
        soln.insert(c);
    }
    ++calls;
}

void SampleInitializer::renormalize(Map_int_dbl& probs) 
{
    double sum = 0.;
    for (Map_int_dbl::iterator iter = probs.begin();
            iter != probs.end();
            ++iter) {
        sum += iter->second;
    }
    for (Map_int_dbl::iterator iter = probs.begin();
            iter != probs.end();
            ++iter) {
        iter->second /= sum;
    }
}

void SampleInitializer::weighted_random_init(Solution& soln, Map_int_dbl& probs) 
{
    soln.clear();
    Map_int_dbl probs_cpy(probs);

    while (soln.size() < (size_t) P) {
        double ball = 0.;
        double spin = DMUtils::random();
        Map_int_dbl::iterator iter;
        for (iter = probs_cpy.begin();
            iter != probs_cpy.end();
                ++iter) {
            ball += iter->second;
            if (ball > spin) {
                break;
            }
        }
        soln.insert(iter->first);
        probs_cpy.erase(iter);
        renormalize(probs_cpy);
    }
}

void SampleInitializer::random_init(Solution& soln) {
    soln.clear();
    while (soln.size() < (size_t) P) {
        int c = DMUtils::random_int(0, N);
        if (!soln.has_city(c))
            soln.insert(c);
    }
}

void SampleInitializer::perturbation_init(Solution& soln) {
    if (soln.empty()) {
        random_init(soln);
        //greedy_init(soln);
    } else { 
        int perturbations = DMUtils::random_int(2, soln.size());
#ifdef __GOCUP_DEBUG
        printf("perturbations: %d\n", perturbations);
#endif
        for (int p = 0; p < perturbations; ++p) {
            int out_ix = DMUtils::random_int(0, soln.size());
            int in = DMUtils::random_int(0, N);
            while (soln.has_city(in)) {
                in = DMUtils::random_int(0, N);
            }
            soln.swap_city(in, out_ix);
        }
    }
}


void SampleInitializer::update_closest(int inserted) {
    // we only need to look at the city we just inserted to see if it's closer
    // note that in first iteration closest_dist is BIGNUM
    // so distance to inserted will always be better
    for (int city = 0; city < N; ++city) {
        closest_dist[city] = std::min(distance->get(city, inserted), closest_dist[city]);
    }
}

int SampleInitializer::find_best_city(Solution& soln) {
    // generate a 'small' sample of cities not in solution
    sample.clear();
    while (sample.size() < (size_t) sample_sz) {
        int s = DMUtils::random_int(0, N);
        if (!soln.has_city(s)) {
            sample.insert(s);
        }
    }

    // among the sample, find the best one to insert
    int argmax_gain = 0;
    int max_gain = -1;
    for (Set_int::iterator iter = sample.begin();
            iter != sample.end();
            ++iter) {
        int gain = 0;
        for (int city = 0; city < N; ++city) {
            int din = distance->get(city, *iter);
            int d1 = closest_dist[city];
            gain += std::max((d1 - din), 0); 
        }
        if (gain > max_gain) {
            max_gain = gain;
            argmax_gain = *iter;
        }
    }
    return argmax_gain;
}

