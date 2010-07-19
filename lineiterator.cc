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


#include "lineiterator.hh"

LineIterator::LineIterator(const char* filename) : 
    _valid(false),
    _fp(NULL)
{
    _fp = fopen(filename, "r");
    if (_fp == NULL) {
        perror("LineIterator");
        return;
    }
    _valid = true;
}

bool LineIterator::has_next() const 
{
    return (_valid && !feof(_fp));
}

char *LineIterator::next() 
{
    char* ret = fgets(_current_line, MAXLINELENGTH, _fp);
    if (ret == NULL) {
        // shouldn't happen; has_next should return false
        // make a dummy empty line
        _current_line[0] = '\0';
        _valid = false;
    }
    return &_current_line[0];
}

LineIterator::~LineIterator()
{
    if (_fp != NULL) {
        fclose(_fp);
    }
}
