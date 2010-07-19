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


#ifndef __GOCUP_UTILS_H_
#define __GOCUP_UTILS_H_

#define SHOW(x) std::cout << "Value of " #x << " = " << x << std::endl;

#ifdef DMDEBUG
#define DMDBG(arg) arg
#define DMDBGLN(arg) arg; cout << endl;
#else
#define DMDBG(arg)
#define DMDBGLN(arg)
#endif

namespace DMUtils {

void clock_seed();
double random();
double uniform(double a, double b);
// return int in range [a,b)
int random_int(int a, int b);
bool flip(double p = 0.5);

}//namespace

#endif
