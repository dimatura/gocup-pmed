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


#include <cassert>
#include <cmath>
#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <vector>

#include "lineiterator.hh"
#include "dataloader.hh"
#include "gocup_data.hh"

void DataLoader::load_gocup_demands(const char* demandfile, DemandVector& demands)
{
    demands.clear();
    LineIterator lineiter(demandfile);
    int linectr = 1;
    while (lineiter.has_next()) {
        char* line = lineiter.next();
        int id, weight;
        int ret = sscanf(line, "%d\t%d", &id, &weight); 
        // printf("demand = %d\n", weight);
        if (ret == EOF) {
            break;
        } else if (ret != 2) {
            fprintf(stderr, "Error parsing file %s, line %d\n", demandfile, linectr);
            exit(1);
        }
        demands.push_back(weight);
        ++linectr;
    }
}

void DataLoader::load_gocup_coords(const char* coordfile, CoordVector& coords)
{
    coords.clear();
    LineIterator lineiter(coordfile);
    int linectr = 1;
    while (lineiter.has_next()) {
        char *line = lineiter.next();
        int id, x, y;
        int ret = sscanf(line, "%d\t%d\t%d", &id, &x, &y); 
        // printf("x = %d, y = %d\n", x, y);
        if (ret == EOF) {
            break;
        } else if (ret != 3) {
            fprintf(stderr, "Error parsing file %s, line %d\n", coordfile, linectr);
            exit(1);
        }
        coords.push_back(Point(x, y));
        ++linectr;
    }
}

DistanceMatrix* DataLoader::load_internal_gocup(int probnum) 
{
    DistanceMatrix* distmatrix = new DistanceMatrix(1000);
    const int *demand_ptr = 0;
    const int (*coord_ptr)[2] = 0;
    switch (probnum) {
        case 1: demand_ptr = demandas1; 
                coord_ptr = coordenadas1;
                break; 
        case 2: demand_ptr = demandas2; 
                coord_ptr = coordenadas2;
                break; 
        case 3: demand_ptr = demandas3; 
                coord_ptr = coordenadas3;
                break; 
        case 4: demand_ptr = demandas4; 
                coord_ptr = coordenadas4;
                break; 
        default: assert(0);
    }
    for (int i = 0; i < 1000; ++i) {
        distmatrix->set(i, i, 0);
        for (int j = 0; j < i; ++j) {
            double dx = coord_ptr[i][0] - coord_ptr[j][0]; 
            double dy = coord_ptr[i][1] - coord_ptr[j][1]; 
            int dist = static_cast<int>(floor(hypot(dx, dy)));
            distmatrix->set(i, j, dist * demand_ptr[i]);
            distmatrix->set(j, i, dist * demand_ptr[j]);
        }
    }
    distmatrix->build_canopies();
    return distmatrix;
}

DistanceMatrix* DataLoader::load_external_gocup(const char* demandfile, const char* coordfile) 
{
    DemandVector demands;
    CoordVector coords;
    load_gocup_demands(demandfile, demands);
    load_gocup_coords(coordfile, coords);
    printf("demands size= %u, coords size = %u\n", demands.size(), coords.size());
    if (demands.size() != coords.size()) {
        fprintf(stderr, "Fatal error: files have different number of lines\n"); 
        exit(1);
    }
    int sz = (int) demands.size();
    DistanceMatrix* distmatrix = new DistanceMatrix(sz);
    for (int i = 0; i < sz; ++i) {
        // distmatrix->set(i, i, 0);
        for (int j = 0; j < sz; ++j) {
            double dx = coords[i].first -  coords[j].first; 
            double dy = coords[i].second - coords[j].second; 
            int dist = static_cast<int>(floor(hypot(dx, dy)));
            distmatrix->set(i, j, dist * demands[i]);
            distmatrix->set(j, i, dist * demands[j]);
        }
    }
    distmatrix->build_canopies();
    return distmatrix;
}
