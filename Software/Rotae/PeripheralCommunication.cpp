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


#include "PeripheralCommunication.h"
#include "Arduino.h"
#include "LiveData.h"
#include "Configuration.h"

String inputData;
PeripheralCommunication::PeripheralCommunication() {
}

//<<destructor>>
PeripheralCommunication::~PeripheralCommunication() {
  /*nothing to destruct*/
}


void PeripheralCommunication::InitPeriperalCommunication() {
  Serial1.begin(bluetoothSerialBaudrate);
}

void PeripheralCommunication::peripheralInputReader(LiveData ld) {
  while (Serial1.available() > 0) {
    inputData = Serial1.readStringUntil('\n');
    Serial.println(inputData);
    inputProcessing(inputData, ld);
    delay(50);
  }
}


void PeripheralCommunication::inputProcessing(String input, LiveData ld) {
  Serial.println(input);
  switch (input.charAt(0)) {
    case'0': //VELOCIMETER
      //velocimeter(input);
      break;
    case '1': //CASSETTE SHIFTER
      cassetteShifeter(input.charAt(2), ld);
      ld.setCassetteShifterOnLine(true);
      ld.setCassetteShifterOnLine_LAST_TIME(millis());
      break;
    case '2': //Crank
      break;
  }
}




void PeripheralCommunication::cassetteShifeter(char input, LiveData ld) {
  switch (input) {
    case '0': //gear down
      if (ld.getCurrentCassetteGear() > 1) {
        ld.setCurrentCassetteGear(ld.getCurrentCassetteGear() - 1 );
      }
      ld.setCassetteShifterOnLine_LAST_TIME(millis());
      break;
    case '1': //gear up
      if (ld.getCurrentCassetteGear() < MAX_CassetteGear) {
        Serial.print(ld.getCurrentCassetteGear());
        ld.setCurrentCassetteGear(ld.getCurrentCassetteGear() + 1);
        Serial.print(ld.getCurrentCassetteGear());

      }
      ld.setCassetteShifterOnLine_LAST_TIME(millis());
      break;
    default:
      //nothing
      break;
  }
}


/*void distancia() {
  distRecorrida = perimetroRueda * contador;
  distKM = distRecorrida / 1000;
  }*/


