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
#include "LiveData.h"

int currentSpeed = 0;

// TIME VARIABLES
int m, mu = 0, md = 0;                     //Declaramos las variables que vamos a usar
int s, su = 0, sd = 0;
int l, lu = 0, ld = 0, lc = 0;
long int tiempo, inicio;

int currentCranksetGear = 1;
int currentCassetteGear = 1;

bool cassetteShifterOnLine = false;
int cassetteShifterOnLine_LAST_TIME = 0;


float distanceTraveled_M_Complete = 1.45f; //distance traveled metros
int distanceTraveled_KM = 0; //distance traveled metros
int distanceTraveled_M = 0 ; //distance traveled metros


//GPS
float ltd, lon;
double alt;

//<<constructor>> setup the LED, make pin 13 an OUTPUT
LiveData::LiveData() {
}

//<<destructor>>
LiveData::~LiveData() {
  /*nothing to destruct*/
}

int LiveData::getCurrentSpeed() {
  return  currentSpeed;
}
void LiveData::setCurrentSpeed(int currentSpeed_IN) {
  currentSpeed = currentSpeed_IN;
}

int LiveData::getLu() {
  return  lu;
}

void LiveData::setLu(int lu_IN) {
  lu = lu_IN;
}

int LiveData::getCurrentCranksetGear() {
  return currentCranksetGear;
}
void LiveData::setCurrentCranksetGear(int gear) {
  currentCranksetGear = gear;
}

int LiveData::getCurrentCassetteGear() {
  return currentCassetteGear;
}
void LiveData::setCurrentCassetteGear(int gear) {
  currentCassetteGear = gear;
}


bool LiveData::getCassetteShifterOnLine() {
  return cassetteShifterOnLine;
}
void LiveData::setCassetteShifterOnLine(bool onLine) {
  cassetteShifterOnLine = onLine;
}

int LiveData::getCassetteShifterOnLine_LAST_TIME() {
  return cassetteShifterOnLine_LAST_TIME;
}

void LiveData::setCassetteShifterOnLine_LAST_TIME(int LAST_TIME) {
  cassetteShifterOnLine_LAST_TIME = LAST_TIME;
}

float LiveData::getLtd() {
  return ltd;
}
void LiveData::setLtd(float latitude) {
  ltd = latitude;
}

float LiveData::getLon() {
  return lon;
}
void LiveData::setLon(float longitude) {
  lon = longitude;
}

double LiveData::getAlt() {
  return alt;
}
void LiveData::setAlt(double altitu) {
  alt = altitu;
}




