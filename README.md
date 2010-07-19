
gocup-pmed
===========

author: Daniel Maturana (dimatura@puc.cl)

A fast implementation of the vertex substitution heuristic for the p-median
problem.  Various of the optimizations suggested by  M. Resende y R. Wernicke
('On the implementation of a swap based local search procedure for the p-median
problem', Proceedings of the fifth workshop on Algorithm Engineering, 2003)
were used.

This implemenentation won the [GOCUP](http://www.gocup.cl) 2008 contest.

Compilation and usage
----------------------

The program was developed in C++ using GNU g++ in Ubuntu Linux Hardy Heron. It was
also verified to compile and run under Windows XP using the GNU MingW toolchain. 
It has no external library dependencies. To compile, simply run make.
The program is named pmedian and accepts various arguments. The simplest
usage is "pmedian <number>" where number is the problem to solve. It
includes various more options which can are documented in the help message
which is displayed with "pmedian -h".

Credits
--------

The project includes Joerg Arndt's bitarray implementation, which is part of the 
[FXT library](http://www.jjj.de/fxt). The library is under GPLv3 as well.

TODO
-----

While the algorithm is implemented for the general case, the data loading code
is specialized for the contest format, which is 2-D. During development I
tested on the classical ORLIB instances, after applying the Floyd-Warshall
algorithm.  I'll eventually reincorporate the code to read the ORLIB format.


