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
   @file Rotae.ino
   @brief Main skecht. Runs everithing.
   @author Carlos Vaello
*/


#include "Configuration.h"
#include "Display.h"
#include "LiveData.h"
#include "PeripheralCommunication.h"
#include "TinyGPS++.h"
#include "Chrono.h"

TinyGPSPlus gps;

Display dp;
LiveData ldata;
PeripheralCommunication peripherals;


long x, y;
int pantalla;

String inputDataP;

Chrono ch(millis());
void setup()
{
  Serial.begin(MAIN_SERIAL_BAUDRATE);      // open the serial port at 9600 bps:

  peripherals.InitPeriperalCommunication();

  Serial3.begin(GPS_SERIAL_BAUDRATE);

  //Serial1.begin(9600);

  dp.DisplayInit();

}


void loop()
{
  ch.ChronoSplit();

  peripherals.peripheralInputReader(ldata);


  /*if (gps.location.isUpdated())
    {
    ldata.setLtd(gps.location.lat());
    ldata.setAlt(gps.location.lng());
    if (gps.altitude.isValid()) {
      ldata.setAlt(gps.altitude.meters());
    }
    }*/



  dp.DisplayUI(ldata);

  smartDelay(1000);

  peripherals.onlineStatusPerifericalCheck(ldata);

}

// This custom version of delay() ensures that the gps object
// is being "fed".
static void smartDelay(unsigned long ms)
{
  /*unsigned long start = millis();
    do
    {*/
  while (Serial3.available()) {
    gps.encode(Serial3.read());
  }
  //} while (millis() - start < ms);
}

