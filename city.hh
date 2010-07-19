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


#ifndef __GOCUP_CITY_HH_
#define __GOCUP_CITY_HH_

#include <cmath>
#include <iostream>

class City {
    public:
        City() :
            id(0),
            x(0),
            y(0),
            weight(0)
        { ; }

        City(const City& c) : 
            id(c.id),
            x(c.x), 
            y(c.y), 
            weight(c.weight) 
        { ; }

        City(int id_, 
            int x_, 
            int y_, 
            int weight_) :
            id(id_),
            x(x_), 
            y(y_), 
            weight(weight_)
        { ; }

        int real_id() const { return id + 1; }

        int weighted_distance(const City& c) const {
            double dx = x - c.x; 
            double dy = y - c.y;
            int dist = static_cast<int>(floor(hypot(dx, dy)));
            return dist*weight;
        }

        bool operator==(const City& rhs) {
            return id == rhs.id; 
        }

        City& operator=(const City& rhs) {
            if (&rhs == this) {
                return *this;
            }
            id = rhs.id;
            x = rhs.x;
            y = rhs.y;
            weight = rhs.weight;
            return *this;
        }

        void clear() {
            x = y = 0;
            weight = 0;
        }

        friend std::ostream& operator<<(std::ostream& os, const City& c) {
            os << "city_" << c.id << " = (" << c.x << ", " << c.y;
            os << ", " << c.weight << ")";
            return os;
        }

        int id;
        int x, y;
        int weight;
};

#endif
