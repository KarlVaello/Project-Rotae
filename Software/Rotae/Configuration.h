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
  Este fichechor header contiene las variables que manejara la clase principal.
  Debe almacenar todas las varaibles que puedan ser configurables por el usuario.

*/


#ifndef Configuration
#define Configuration

#include <Arduino.h>


#define mainSerialBaudrate 9600
#define gpsSerialBaudrate 9600
#define bluetoothSerialBaudrate 9600


#define  MAX_CranksetGear 2
#define  MAX_CassetteGear 11


#define cassetteShifterOnLine_MAX_TIME 8000

#endif

