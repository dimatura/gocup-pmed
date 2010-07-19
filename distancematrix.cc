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

#include "distancematrix.hh"

void DistanceMatrix::build_canopies() {
    // insert ranges
    int *dist_row = _data;
    int *canopy_row = _canopies;
    for (size_t i = 0; i < _size; ++i) {
        for (size_t j = 0; j < _size; ++j) {
            canopy_row[j] = j;
        }
        // now do an 'argsort'
        arg_quicksort(dist_row, canopy_row, canopy_row + _size);
        dist_row += _size;
        canopy_row += _size;
    }
}

int* DistanceMatrix::arg_partition(int* dist, int* left, int* right) {
    //TODO smarter pivot. for now pivot is last item
    int* i = left - 1;
    int* j = right - 1;
    int* p = right - 1;
    while (true) {
        do { 
            ++i;
        } while (dist[*i] < dist[*p]);
        do {
            --j;
        } while ((dist[*p] < dist[*j]) && (j != left)); 
        if (i >= j)
            break;
        swap(i, j);
    }
    swap(i, p);
    return i;
}

void DistanceMatrix::arg_quicksort(int *dist, int* left, int* right) {
    size_t len = right - left;
    if (len <= 1) { 
        // do nothing
    }
    else if (len == 2) {
        if (*left > *(left + 1)) {
            swap(left, left + 1);
        }
    } else {
        int* p = arg_partition(dist, left, right);
        arg_quicksort(dist, left, p);
        arg_quicksort(dist, p + 1, right);
    }
}

void DistanceMatrix::floyd_warshallize() { 
    int newval, oldval;
    for (size_t k = 0; k < _size; ++k) {
        for (size_t i = 0; i < _size; ++i) {
            for (size_t j = 0; j < _size; ++j) {
                oldval = _data[i*_size + j];
                newval = _data[i*_size + k] + _data[k*_size + j];
                _data[i*_size + j] = oldval < newval? oldval : newval;
            }
        }
    }
}


