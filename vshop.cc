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


#include <algorithm>

#include "vshop.hh"
#include "utils.hh"

void VSHOp::update_closest(Solution& solution, int swapped_in, int swapped_out_ix, int swapped_out) {
    for (Set_int::iterator city = affected.begin(); 
            city != affected.end();
            ++city) {
        int c = *city;
        int min = INT_MAX, min2 = INT_MAX;
        int argmin_ix = -1, argmin2_ix = -1;
        for (size_t m = 0; m < solution.size(); ++m) {
            int d = distance->get(c, solution.get(m));
            if (d < min) {
                min2 = min;
                argmin2_ix = argmin_ix;
                min = d;
                argmin_ix = m;
            } else if (d < min2) {
                min2 = d;
                argmin2_ix = m;
            }
        }
        closest_ix[c] = argmin_ix;
        closest2_ix[c] = argmin2_ix;
        d1[c] = min;
        d2[c] = min2;
    }
}

void VSHOp::init_closest(Solution& solution) {
    for (int c = 0; c < N; ++c) {
        int min = INT_MAX, min2 = INT_MAX;
        int argmin_ix = -1, argmin2_ix = -1;
        for (size_t m = 0; m < solution.size(); ++m) {
            int d = distance->get(c, solution.get(m));
            if (d < min) {
                min2 = min;
                argmin2_ix = argmin_ix;
                min = d;
                argmin_ix = m;
            } else if (d < min2) {
                min2 = d;
                argmin2_ix = m;
            }
        }
        closest_ix[c] = argmin_ix;
        closest2_ix[c] = argmin2_ix;
        d1[c] = min;
        d2[c] = min2;
    }
}

void VSHOp::reset_structures() {
    std::fill(loss.begin(), loss.end(), 0);
    std::fill(gain.begin(), gain.end(), 0);
    std::fill(closest_ix.begin(), closest_ix.end(), 0);
    std::fill(closest2_ix.begin(), closest2_ix.end(), 1);
    std::fill(d1.begin(), d1.end(), 0);
    std::fill(d2.begin(), d2.end(), 0);
    iterated = 0;
    extra.reset();
}

void VSHOp::update_structures(Solution& solution) {
    for (Set_int::iterator city = affected.begin(); 
            city != affected.end();
            ++city) {
        int d1tmp = d1[*city];
        int d2tmp = d2[*city];
        int swap_out_ix = closest_ix[*city];
        loss[swap_out_ix] += (d2tmp- d1tmp);
        for (int *swap_in_iter = distance->canopy(*city);
                swap_in_iter != distance->canopy(*city) + distance->size();
                ++swap_in_iter) {
            int swap_in = *swap_in_iter;

            if (swap_in ==  solution.get(closest2_ix[*city])) {
                // it's unnecesary to continue
                break;
            }

            if (solution.has_city(swap_in)) {
                continue;
            }

            int din = distance->get(*city, swap_in);

            int dout = distance->get(*city, solution.get(swap_out_ix));
           
            gain[swap_in] += std::max(0, d1tmp - din);

            int extra_val = d2tmp - std::max(din, dout);

            extra.incr(swap_in, swap_out_ix, extra_val);
        }
    }
}

void VSHOp::undo_update_structures(Solution& solution) {
    for (Set_int::iterator city = affected.begin(); 
            city != affected.end();
            ++city) {
        int d1tmp = d1[*city];
        int d2tmp = d2[*city];
        int swap_out_ix = closest_ix[*city];
        loss[swap_out_ix] -= (d2tmp - d1tmp);
        for (int *swap_in_iter = distance->canopy(*city);
                swap_in_iter != distance->canopy(*city) + distance->size();
                ++swap_in_iter) {
            int swap_in = *swap_in_iter;

            if (swap_in == solution.get(closest2_ix[*city])) {
                // it's unnecesary to continue
                break;
            }

            if (solution.has_city(swap_in)) {
                continue;
            }
            int din = distance->get(*city, swap_in);
            int dout = distance->get(*city, solution.get(swap_out_ix));
            gain[swap_in] -= std::max(0, d1[*city] - din);
            int extra_val = d2tmp - std::max(din, dout);
            extra.incr(swap_in, swap_out_ix, -extra_val); 
        }
    }
}

inline void VSHOp::find_best_neighbor(int& max_profit, 
        int& max_swap_out_ix, 
        int& max_swap_in, 
        Solution& solution) { 
    max_profit = INT_MIN;
    for (int swap_out_ix = 0; 
            swap_out_ix < (int) solution.size(); 
            ++swap_out_ix) {
        // compiler should do this optimization but just in case
        int loss_out = loss[swap_out_ix];
        for (int swap_in = 0; swap_in < N; ++swap_in) {
            int profit = gain[swap_in] - loss_out + extra.get(swap_in, swap_out_ix);
            //profit = std::max(0, profit - penalty[swap_in]);

            if (profit > max_profit) {
                max_profit = profit;
                max_swap_out_ix = swap_out_ix;
                max_swap_in = swap_in;
            }
        }
    }
}

inline void VSHOp::add_penalty(Solution& soln) {
    int max_loss = INT_MIN;
    int argmax_loss = 0;
    for (int swap_out_ix = 0; 
            swap_out_ix < (int) soln.size(); 
            ++swap_out_ix) {
        if (loss[swap_out_ix] > max_loss) {
            max_loss = swap_out_ix;
            argmax_loss = swap_out_ix;
        }
    }
    penalty[soln.get(argmax_loss)] += 20000;
}

void VSHOp::sampled_find_best_neighbor(int& max_profit, 
        int& max_swap_out_ix, 
        int& max_swap_in, 
        Solution& solution) { 

    // generate a 'small' sample of cities not in solution
    sample.clear();
    while (sample.size() < (size_t) sample_sz) {
        int s = DMUtils::random_int(0, N);
        if (!solution.has_city(s)) {
            sample.insert(s);
        }
    }

    max_profit = INT_MIN;

    for (int swap_out_ix = 0; 
            (size_t) swap_out_ix < solution.size(); 
            ++swap_out_ix) {

        // compiler should do this optimization but just in case
        int loss_out = loss[swap_out_ix];

        for (Set_int::const_iterator swap_in = sample.begin(); 
                swap_in != sample.end(); 
                ++swap_in) {
            int profit = gain[*swap_in] - loss_out + extra.get(*swap_in, swap_out_ix);
            if (profit > max_profit) {
                max_profit = profit;
                max_swap_out_ix = swap_out_ix;
                max_swap_in = *swap_in;
            }
        }
    }
}

int VSHOp::init(Solution& solution) {
    // initially all are affected.
    affected.clear();
    for (int c = 0; c < N; ++c) {
        affected.insert(c);
    }
    iterated = 0;
    reset_structures();

    init_closest(solution);
    int first_iter_profit = local_search(solution, false);
    return first_iter_profit;
}

int VSHOp::local_search(Solution& solution, bool sampled) {
    update_structures(solution);
    int max_profit = 0, max_swap_out_ix = 0, max_swap_in = 0;
    if (sampled) {
        sampled_find_best_neighbor(max_profit, max_swap_out_ix, max_swap_in, solution);
    } else {
        find_best_neighbor(max_profit, max_swap_out_ix, max_swap_in, solution);
    }
    // add_penalty(solution);
    if (max_profit > 0) {
        affected.clear();
        // find cities that'll be affected
        for (int city = 0; city < N; ++city) {
            if ((closest_ix[city] == max_swap_out_ix) || 
                (closest2_ix[city] == max_swap_out_ix) ||
                (distance->get(city, max_swap_in) < d2[city])) { 
                affected.insert(city);
            }
        }
        int swapped_out = solution.get(max_swap_out_ix);
        undo_update_structures(solution);
        solution.swap_city(max_swap_in, max_swap_out_ix);

#ifdef __GOCUP_DEBUG
        int cost = solution.cost();
        solution.set_cost(cost - max_profit); 
        printf("iter: %d, soln: ", iterated);
        solution.print_to(stdout);
        printf("\n");
#endif
        //init_closest(solution);
        update_closest(solution, max_swap_in, max_swap_out_ix, swapped_out);
        ++iterated;
    }
    return max_profit;
}

