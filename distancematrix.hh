#ifndef __GOCUP_DISTANCE_MATRIX
#define __GOCUP_DISTANCE_MATRIX

#include <cstdio> 
#include <vector>
#include "city.hh"

class DistanceMatrix {
    public: 
        DistanceMatrix(size_t sz) :
            _size(sz), 
            _data(0), 
            _canopies(0) 
        {
            _data = new int[_size*_size];
            _canopies = new int[_size*_size];
        }

        void swap(int *l, int *r) {
            int tmp = *l;
            *l = *r;
            *r = tmp;
        }

        int* canopy(int i) { return _canopies + (_size*i); }

        void build_canopies();

        size_t size() const { return  _size; }

        int get(int i, int j) const {
            return _data[i*_size + j];
        }

        void set(int i, int j, int val) {
            _data[i*_size + j] = val;
        }


        ~DistanceMatrix() {
            delete[] _data;
            delete[] _canopies;
        }

        void print_to(FILE* fout) const 
        {
            for (size_t i = 0; i < _size; ++i) {
                for (size_t j = 0; j < _size - 1; ++j) {
                    fprintf(fout, "%d, ", _data[i*_size + j]);
                }
                fprintf(fout, "%d\n", _data[i*_size + (_size - 1)]);
            }
        }

        void floyd_warshallize(); 

    private:
        DistanceMatrix(const DistanceMatrix& dm); 
        DistanceMatrix& operator=(DistanceMatrix& dm);
        DistanceMatrix& operator=(const DistanceMatrix& dm);
        void arg_quicksort(int *dist, int *left, int *right);
        int* arg_partition(int *dist, int *left, int *right);
        size_t _size;
        int *_data;
        int *_canopies;
};

#endif
