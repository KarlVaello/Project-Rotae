/*
   Project Rotae  Copyright (C) 2016  Carlos Vaello

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
/**
   @file Chrono.h
   @brief Contains everithing related to Chrono
   @author Carlos Vaello
*/
#ifndef CHRONO_H
#define CHRONO_H

#include "Arduino.h"

class Chrono {
  public:
    Chrono(long int chronoInitTime );
    ~Chrono();
    void ChronoSplit() ;
    int getM();
    int getMu();
    int getMd();

    int getS();
    int getSu();
    int getSd();

    int getL();
    int getLu();
    int getLd();
    int getLc();


};

#endif
