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


#ifndef __GOCUP_LINE_ITERATOR_HH
#define __GOCUP_LINE_ITERATOR_HH
#include <cstdio>

#define MAXLINELENGTH 256

class LineIterator {
    public:
        LineIterator(const char* filename);
        ~LineIterator();

        bool valid() const { return _valid; }
        bool has_next() const;
        char *next();

    private:
        LineIterator(const LineIterator&);
        LineIterator& operator=(const LineIterator&);

        bool _valid;
        FILE *_fp;
        char _current_line[MAXLINELENGTH];
        
};

#endif
