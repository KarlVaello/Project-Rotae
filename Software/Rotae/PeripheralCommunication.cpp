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
   @file PeripheralCommunication.cpp
   @brief Peripheral bluethoot serial communication. Read,write and proces input comands
   @author Carlos Vaello
*/

#include "PeripheralCommunication.h"
#include "Arduino.h"
#include "LiveData.h"
#include "Configuration.h"

String inputData;

//<<constructor>>
PeripheralCommunication::PeripheralCommunication() {
}

//<<destructor>>
PeripheralCommunication::~PeripheralCommunication() {
  /*nothing to destruct*/
}

/*
  @brief Seting up serial baudrate. Used at start.
*/
void PeripheralCommunication::InitPeriperalCommunication() {
  Serial1.begin(BLUETOOTH_SERIAL_BAUDRATE);
}

/*
  @brief Main input data function that read from serial1(bluetooth) until '\n'.
  The input string is sended to inputProcessing cutom function.
  @param ld is the current LiveData running.
*/
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

/*
  @brief proces the inputData and process each comand.
  The input string is sended to inputProcessing cutom function.

  @param input input data comand (string) to process
  @param ld is the current LiveData running.
*/

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

/*
  @brief proces cassetteShifeter comands

  @param input input data comand (char) to process
  @param ld is the current LiveData running.
*/
void PeripheralCommunication::cassetteShifeter(char input, LiveData ld) {
  switch (input) {
    case '0': //gear down
      if (ld.getCurrentCassetteGear() > 1) {
        ld.setCurrentCassetteGear(ld.getCurrentCassetteGear() - 1 );
      }
      ld.setCassetteShifterOnLine_LAST_TIME(millis());
      break;
    case '1': //gear up
      <<< <<< < HEAD
      if (ld.getCurrentCassetteGear() < MAX_CASSETTE_GEAR) {
        == == == =
        if (ld.getCurrentCassetteGear() < MAX_CassetteGear) {
          >>> >>> > origin / master
          ld.setCurrentCassetteGear(ld.getCurrentCassetteGear() + 1);
        }
        ld.setCassetteShifterOnLine_LAST_TIME(millis());
        break;
      default:
        //nothing
        break;
      }
  }
}

/*
  @brief proces speedodometer comands

  @param input input data comand (String) to process
  @param ld is the current LiveData running.
*/
String spliteded;
void PeripheralCommunication::speedodometer(String input, LiveData ld) {
  Serial.println(input);
  switch (input.charAt(0)) {
    case'0': //VELOCIMETER
      //spliteded = (getValue(input, ';', 1));
      ld.setCurrentSpeed((splitStringAtIndexSeparator(input, ';', 1)).toInt());
      Serial.println((splitStringAtIndexSeparator(input, ';', 1)));
      break;
      <<< <<< < HEAD
  }
}

/*
  @brief Custom function thats allow to split a String by a separator and a idex.
  Example:
  String a = "0;45"
  splitStringAtIndexSeparator(a,';',1);
  will retun -> "45" (String)

  This function stops when index is found and just retunr a String!!.

  @param data string to split
  @param separator some like ';','&','%'...
  @param index whicdivided string are you interested.
  @return the splited String by separatr and index.
*/
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

void PeripheralCommunication::onlineStatusPerifericalCheck(LiveData ld) {
  if (millis() > ld.getCassetteShifterOnLine_LAST_TIME() + cassetteShifterOnLine_MAX_TIME) {
    >>> >>> > origin / master
    ld.setCassetteShifterOnLine(false);
  }
}

