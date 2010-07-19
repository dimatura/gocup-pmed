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



#ifndef __GOCUP_DATALOADER_HH_
#define __GOCUP_DATALOADER_HH_

#include <vector>
#include <utility>

#include "distancematrix.hh"

typedef std::vector<int> DemandVector;
typedef std::pair<int, int> Point;
typedef std::vector<Point> CoordVector;

class DataLoader {
    public:
        DataLoader() { ; }
        ~DataLoader() { ; }
        DistanceMatrix* load_internal_gocup(int probnum);
        DistanceMatrix* load_external_gocup(const char* demandfile, const char* coordfile);

    private:
        void load_gocup_demands(const char* demandfile, DemandVector& demands);
        void load_gocup_coords(const char* coordfile, CoordVector& coords);
        DataLoader(const DataLoader&);
        DataLoader& operator=(const DataLoader&);
        
};

#endif
