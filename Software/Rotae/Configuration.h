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
   @file Configuration.h
   @brief Contains global configurable variables.
   @author Carlos Vaello
*/


#ifndef Configuration
#define Configuration

#include <Arduino.h>


#define MAIN_SERIAL_BAUDRATE 9600
#define GPS_SERIAL_BAUDRATE 9600
#define BLUETOOTH_SERIAL_BAUDRATE 9600


#define  MAX_CRANKSET_GEAR 2
#define  MAX_CASSETTE_GEAR 11


#define CASSETTE_SHIFTER_ONLINE_MAX_TIME 8000

#endif
