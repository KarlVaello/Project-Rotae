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
#include "LiveData.h"
#include <UTFT.h>
#include <URTouch.h>
#include <URTouchCD.h>

//#include <UTFT_Buttons.h>
LiveData ld;

UTFT lcd(ILI9481, 38, 39, 40, 41);
URTouch tactil(6, 5, 4, 3, 2);
//UTFT_Buttons myButtons(&lcd, &tactil);

// Declare which fonts we will be using
extern uint8_t BigFont[];
extern uint8_t SmallFont[];
extern uint8_t arial_bold[];
extern uint8_t various_symbols[];
extern uint8_t CalibriBold32x48[];
extern uint8_t SevenSeg_XXXL_Num[];
extern uint8_t SevenSegNumFontPlus[];
extern uint8_t ArialNumFontPlus[];
extern uint8_t OCR_A_Extended_M[];

class Display {
  public:
    Display();
    ~Display();
    void DisplayUI();
    void DisplayInit();
};

#endif
