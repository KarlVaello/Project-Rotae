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


#ifndef Display_H
#define Display_H

#include <Arduino.h>
#include <UTFT.h>
#include <URTouch.h>
#include <URTouchCD.h>
//#include <UTFT_Buttons.h>

#include "LiveData.h"




class Display {
  public:
    Display();
    ~Display();
    void DisplayUI(LiveData ld);
    void DisplayInit();
};

#endif

