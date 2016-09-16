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
   @file LiveData.h
   @brief Contains everithing related to LiveData
   @author Carlos Vaello
*/

#ifndef LiveData_H
#define LiveData_H


class LiveData {
  public:
    LiveData();
    ~LiveData();

    int getCurrentSpeed();
    void setCurrentSpeed(int currentSpeed);

    int getLu();
    void setLu(int lu);

    int getCurrentCranksetGear();
    void setCurrentCranksetGear(int gear);

    int getCurrentCassetteGear();
    void setCurrentCassetteGear(int gear);

    bool getCassetteShifterOnLine();
    void setCassetteShifterOnLine(bool OnLine);

    int getCassetteShifterOnLine_LAST_TIME();
    void setCassetteShifterOnLine_LAST_TIME(int LAST_TIME);

    float getLtd();
    void setLtd(float latitude);

    float getLon();
    void setLon(float longitude);

    double getAlt();
    void setAlt(double altitu);

    int getDistanceTraveled_KM_digits();
    void setDistanceTraveled_KM_digits(int distanceTraveled_KM_digits_IN  );

    int getDistanceTraveled_M_digits();
    void setDistanceTraveled_M_digits (int distanceTraveled_M_digits_IN );



};


#endif
