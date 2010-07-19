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

#ifndef __GOCUP_EXTRA_MATRIX
#define __GOCUP_EXTRA_MATRIX

#include <cassert>
#include <algorithm>

class ExtraMatrix {
    public: 
        ExtraMatrix(const ExtraMatrix& dm) :
            _rows(dm._rows),
            _cols(dm._cols),
            _size(dm._size),
            _data(dm._data),
            _owner(false) 
        { ; }

        ExtraMatrix(int N, int P) : 
            _rows(N),
            _cols(P),
            _size(N*P), 
            _data(0),
            _owner(true)
        {
            _data = new int[_size*_size];
            std::fill(_data, _data + _size, 0);
        }

        size_t size() const { return _size; }
        size_t rows() const { return _rows; }
        size_t cols() const { return _cols; }

        int get(size_t i, size_t j) {
            assert (i < _rows && j < _cols);
            return _data[i*_cols + j];
        }

        void incr(size_t i, size_t j, int val) {
            assert (i < _rows && j < _cols);
            _data[i*_cols + j] += val;
        }

        void reset() {
            std::fill(_data, _data + _size, 0);
        }

        ~ExtraMatrix() {
            if (_owner) {
                delete[] _data;
            }
        }

    private:
        ExtraMatrix& operator=(ExtraMatrix& dm);
        ExtraMatrix& operator=(const ExtraMatrix& dm);
        size_t _rows, _cols;
        size_t _size;
        int *_data;
        bool _owner;
};

#endif
