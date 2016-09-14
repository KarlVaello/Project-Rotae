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

int currentSpeed = 0;

// TIME VARIABLES
int m, mu = 0, md = 0;                     //Declaramos las variables que vamos a usar
int s, su = 0, sd = 0;
int l, lu = 0, ld = 0, lc = 0;
long int tiempo, inicio;


//<<constructor>> setup the LED, make pin 13 an OUTPUT
LiveData::LiveData() {
}

//<<destructor>>
LiveData::~LiveData() {
  /*nothing to destruct*/
}

void int getCurrentSpeed() {
  return  currentSpeed;
}
void setCurrentSpeed(int currentSpeed) {
  this.currentSpeed = currentSpeed;
}

void int getLu() {
  return  lu;
}
void setLu(int lu) {
  this.lu = lu;
}


