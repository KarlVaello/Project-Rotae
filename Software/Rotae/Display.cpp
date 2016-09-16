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
/*
   @file Display.cpp
   @brief Contains everithing related to display
   @author Carlos Vaello
*/

#include "Display.h" //include the declaration for this class
#include "Configuration.h"
#include "Chrono.h"

UTFT lcd(ILI9481, 38, 39, 40, 41);
URTouch tactil(6, 5, 4, 3, 2);

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



//<<constructor>> setup the LED, make pin 13 an OUTPUT


Display::Display() {
}

//<<destructor>>
Display::~Display() {
  /*nothing to destruct*/
}


/*
  Control init isplay at star on setup arduino function.
  This set up somo importand display config
*/
void Display::DisplayInit() {
  lcd.InitLCD(PORTRAIT);
  lcd.clrScr();
  tactil.InitTouch(PORTRAIT);
  tactil.setPrecision(PORTRAIT);
  lcd.fillScr(210, 215, 211);
  lcd.setColor(103, 129, 159);
  lcd.fillRect(0, 0, 480, 20);
  tactil.setPrecision(PREC_MEDIUM);
}

/*
  Control canvas display

  @param ld is the current LiveData running.
  @param ch is the current Chrono object running.
  @return the numerical value of the color code.
*/
void Display::DisplayUI(LiveData ld, Chrono ch) {
  //##### SPEED PRINT #########
  lcd.setFont(SevenSeg_XXXL_Num);
  lcd.setBackColor(210, 215, 211);
  lcd.setColor(32, 73, 120);
  lcd.print(String(ld.getCurrentSpeed()), CENTER, 40);
  lcd.setFont(arial_bold);
  lcd.setBackColor(210, 215, 211);
  lcd.print("km/h", CENTER, 150);
  lcd.drawLine(10, 175, 310, 175);

  //##### CRANKSET GEARS PRINT #########
  lcd.setFont(OCR_A_Extended_M);
  lcd.setBackColor(210, 215, 211);
  lcd.setColor(32, 73, 120);
  if (ld.getCurrentCranksetGear() + 1 <= MAX_CRANKSET_GEAR) {
    lcd.print(String(ld.getCurrentCranksetGear() + 1 ), 36, 45);
  } else {
    lcd.print(" ", 36, 45);
  }

  lcd.drawLine(35, 70, 55, 70);

  lcd.setFont(SevenSegNumFontPlus);
  lcd.setBackColor(210, 215, 211);
  lcd.setColor(32, 73, 120);
  lcd.print(String(ld.getCurrentCranksetGear()), 30, 75);

  lcd.drawLine(35, 130, 55, 130);

  lcd.setFont(OCR_A_Extended_M);
  lcd.setBackColor(210, 215, 211);
  lcd.setColor(32, 73, 120);
  if (ld.getCurrentCranksetGear() - 1 >= 1) {
    lcd.print(String(ld.getCurrentCranksetGear() - 1  ), 36, 135);
  } else {
    lcd.print(" ", 36, 135);
  }


  //##### CASSETTE GEARS PRINT #########
  if (ld.getCassetteShifterOnLine()) {
    lcd.setColor(0, 200, 0);

  } else {
    lcd.setColor(200, 0, 0);
  }
  lcd.fillCircle(268, 35, 5);

  lcd.setFont(OCR_A_Extended_M);
  lcd.setBackColor(210, 215, 211);
  lcd.setColor(32, 73, 120);
  if (ld.getCurrentCassetteGear() + 1 <= MAX_CASSETTE_GEAR) {
    lcd.print(String(ld.getCurrentCassetteGear() + 1 ), 261, 45);
  } else {
    lcd.print(" ", 261, 45);
  }

  lcd.drawLine(260, 70, 280, 70);

  lcd.setFont(SevenSegNumFontPlus);
  lcd.setBackColor(210, 215, 211);
  lcd.setColor(32, 73, 120);
  lcd.print(String(ld.getCurrentCassetteGear()), 255, 75);

  lcd.drawLine(260, 130, 280, 130);

  lcd.setFont(OCR_A_Extended_M);
  lcd.setBackColor(210, 215, 211);
  lcd.setColor(32, 73, 120);
  if (ld.getCurrentCassetteGear() - 1 >= 1) {
    lcd.print(String(ld.getCurrentCassetteGear() - 1  ), 261, 135);
  } else {
    lcd.print(" ", 261, 135);
  }

  //GPS
  lcd.setFont(OCR_A_Extended_M);
  lcd.setBackColor(210, 215, 211);
  lcd.setColor(32, 73, 120);
  lcd.print(String(ld.getLtd()), 70, 200);

  lcd.setFont(OCR_A_Extended_M);
  lcd.setBackColor(210, 215, 211);
  lcd.setColor(32, 73, 120);
  lcd.print(String(ld.getLon()), 70, 240);

  lcd.setFont(OCR_A_Extended_M);
  lcd.setBackColor(210, 215, 211);
  lcd.setColor(32, 73, 120);
  lcd.print(String(ld.getLon()), 70, 240);

  lcd.setFont(OCR_A_Extended_M);
  lcd.setBackColor(210, 215, 211);
  lcd.setColor(32, 73, 120);

  lcd.print(String(ld.getAlt()), 200, 200);

  //DISTANCE

  lcd.drawLine(10, 310, 310, 310);
  lcd.setFont(CalibriBold32x48);
  lcd.print(String(ld.getDistanceTraveled_KM_digits()), 70, 320);
  lcd.fillRect(142, 356, 148, 362);
  lcd.print(String(ld.getDistanceTraveled_M_digits()), 160, 320);
  lcd.setFont(arial_bold);
  lcd.setBackColor(210, 215, 211);
  lcd.print("km", CENTER, 375);
  lcd.drawLine(10, 175, 310, 175);
  lcd.drawLine(10, 400, 310, 400);


  lcd.setFont(CalibriBold32x48);
  lcd.print(String(ch.getMd()), 18, 410);
  lcd.print(String(ch.getMu()), 50, 410);
  lcd.setFont(ArialNumFontPlus);
  lcd.print(":", 82, 410);
  lcd.setFont(CalibriBold32x48);
  lcd.print(String(ch.getSd()), 114, 410);
  lcd.print(String(ch.getSu()), 146, 410);
  lcd.setFont(ArialNumFontPlus);
  lcd.print(":", 178, 410);
  lcd.setFont(CalibriBold32x48);
  lcd.print(String(ch.getLc()), 210, 410);
  lcd.print(String(ch.getLd()), 242, 410);
  lcd.print(String(ch.getLu()), 274, 410);
}


//int optionButton, pressed_button;

// myButtons.setTextFont(BigFont);

//optionButton = myButtons.addButton( 220,  340, 80,  60, "C");
//myButtons.drawButtons();

/*while (1)
  {
  if (tactil.dataAvailable() == true)
  {
    pressed_button = myButtons.checkButtons();

    if (pressed_button == optionButton) {
      lcd.print("Cat     ", 10, 220);

    }
  }
  }*/
