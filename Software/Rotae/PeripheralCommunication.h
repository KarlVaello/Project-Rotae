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
   @file PeripheralCommunication.h
   @brief Peripheral bluethoot serial communication. Read,write and proces input comands 
   @author Carlos Vaello
*/

#ifndef PeripheralCommunication_H
#define PeripheralCommunication_H

#include "LiveData.h"
#include "Arduino.h"

class PeripheralCommunication {
  public:
    PeripheralCommunication();
    ~PeripheralCommunication();

    void InitPeriperalCommunication();
    void peripheralInputReader(LiveData ld);
    void inputProcessing(String input, LiveData ld);
    void cassetteShifeter(char input, LiveData ld);

    void onlineStatusPerifericalCheck(LiveData ld);
    void speedodometer(String input, LiveData ld);

    String getValue(String data, char separator, int index);
    String splitStringAtIndexSeparator(String data, char separator, int index);

};

#endif
