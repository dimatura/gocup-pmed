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


#include <cmath>
#include <ctime>
#include <cstdlib>
#include <cassert>

#include "utils.hh"

void DMUtils::clock_seed() {
    srand(static_cast<unsigned int>(time(NULL)));
}

double DMUtils::random() {
    return double(rand())/(double(RAND_MAX) + 1.0);
}

double DMUtils::uniform(double a, double b) {
    return (b - a)*DMUtils::random() + a;
}

// return int in range [a,b)
int DMUtils::random_int(int a, int b) {
    double u = DMUtils::random();
    u = floor(u*(b - a) + a);
    return static_cast<int>(u);
}

bool DMUtils::flip(double p) {
    return DMUtils::random() < p;
}
