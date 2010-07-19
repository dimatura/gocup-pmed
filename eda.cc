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


#include <map>
#include <algorithm>
#include <numeric>
#include "eda.hh"
#include "sampleinitializer.hh"
#include "vshop.hh"
#include "utils.hh"

void EDA::solve(const Options& opt) {
    generation(true, false, opt);
    estimate(opt);
    generation(false, true, opt);
    generation(false, false, opt);
}

void EDA::roulette_sampler(Solution& soln, bool anti, const Options& opt) {
    soln.clear();
    while (soln.size() < (size_t) P) {
        double ball = 0;
        double pr = DMUtils::random();
        if (anti) {
            int c;
            for (c = 0; (size_t) c < anti_stats.size(); ++c) {
                if (soln.has_city(c)) {
                    continue;
                }
                ball += anti_stats[c];
                if (ball > pr) {
                    break;
                }
            }
            soln.insert(c);
        } else { 
            std::map<int, double>::iterator iter;
            for (iter = stats.begin();
                    iter != stats.end();
                    ++iter) {
                if (soln.has_city(iter->first)) {
                    continue;
                }
                ball += iter->second;
                if (ball > pr) {
                    break;
                }
            }
            soln.insert(iter->first);
        }
    }
}

void EDA::generation(bool first, bool anti, const Options& opt) {
    // SampleInitializer sinit(_problem);
    VSHOp rwvsh(_problem);
    if (first) {
        _best_soln.set_cost(INT_MAX);
    }
    for (int run = 1; run <= opt.runs(); ++run) {
        // sinit.initialize(_current_soln);
        if (first) {
            randomize_solution(_current_soln);
        } else {
            roulette_sampler(_current_soln, anti, opt);
        }  

        _problem->calculate_cost(_current_soln);
        rwvsh.local_search(_current_soln);
        _problem->calculate_cost(_current_soln);
        pop.push_back(_current_soln);
        if (_current_soln.cost() < _best_soln.cost()) {
            _best_soln = _current_soln;
        }
        if (opt.verbose()) {
            std::cout << "Run " << run << " of " << opt.runs() << ", ";
            std::cout << "Best of run: " << _current_soln.cost() << ", ";
            std::cout << "Overall best: " << _best_soln.cost() << std::endl;
        }
    }
}

void EDA::estimate(const Options& opt) {
    stats.clear();
    int total = 0;
    for (std::vector<Solution>::iterator soln_iter = pop.begin();
            soln_iter != pop.end();
            ++soln_iter) {
        for (std::vector<int>::iterator iter = soln_iter->begin(); 
                iter != soln_iter->end();
                ++iter) {
            stats[*iter] += 1.;
            ++total;
        }
    }

    std::fill(anti_stats.begin(), anti_stats.end(), 1.0);
    for (std::map<int, double>::iterator iter = stats.begin();
            iter != stats.end();
            ++iter) {
        iter->second /= total;
        anti_stats[iter->first] -= iter->second;
    }

    double anti_total = std::accumulate(anti_stats.begin(), anti_stats.end(), 0.);
    
    for (std::vector<double>::iterator iter = anti_stats.begin();
            iter != anti_stats.end();
            ++iter) {
        (*iter) /= anti_total;
    }

}
