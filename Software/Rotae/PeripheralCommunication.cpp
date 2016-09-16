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
    //Serial.println(inputData);
    inputProcessing(inputData, ld);
    delay(50);
  }
}


void PeripheralCommunication::inputProcessing(String input, LiveData ld) {
  //Serial.println(input);
  switch (input.charAt(0)) {
    case'0': //VELOCIMETER
      //velocimeter(input);
      speedodometer(input, ld);
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
        ld.setCurrentCassetteGear(ld.getCurrentCassetteGear() + 1);
      }
      ld.setCassetteShifterOnLine_LAST_TIME(millis());
      break;
    default:
      //nothing
      break;
  }
}
String spliteded;
void PeripheralCommunication::speedodometer(String input, LiveData ld) {
  Serial.println(input);
  switch (input.charAt(0)) {
    case'0': //VELOCIMETER
      //spliteded = (getValue(input, ';', 1));
      ld.setCurrentSpeed((splitStringAtIndexSeparator(input, ';', 1)).toInt());
      Serial.println((splitStringAtIndexSeparator(input, ';', 1)));
      break;

  }
}

String PeripheralCommunication::splitStringAtIndexSeparator(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {
    0, -1
  };
  int maxIndex = data.length() - 1;
  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
/*void distancia() {
  distRecorrida = perimetroRueda * contador;
  distKM = distRecorrida / 1000;
  }*/

void PeripheralCommunication::onlineStatusPerifericalCheck(LiveData ld) {
  if (millis() > ld.getCassetteShifterOnLine_LAST_TIME() + cassetteShifterOnLine_MAX_TIME) {
    ld.setCassetteShifterOnLine(false);
  }
}

