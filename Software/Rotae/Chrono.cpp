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
   @file Chrono.cpp
   @brief Contains everithing related to Chrono
   @author Carlos Vaello
*/

#include "Chrono.h"
#include "Arduino.h"

// TIME VARIABLES
int m, mu = 0, md = 0;                     //Declaramos las variables que vamos a usar
int s, su = 0, sd = 0;
int l, lu = 0, ld = 0, lc = 0;
long int tiempo, inicio;

//<<constructor>> 
Chrono::Chrono(long int chronoInitTime) {
  inicio = chronoInitTime;

}
//<<destructor>>
Chrono::~Chrono() {
  /*nothing to destruct*/
}

/*
  @brief Split tiempo (millis) on minuts(m), seconds(s) and milliseconds(l)
  m:s:l
  And split it on theys digits to help to print it on the screen
*/
void Chrono::ChronoSplit() {
  tiempo = millis() - inicio;      //Calculamos el tiempo que paso desde que se activo el sensor start/stop

  m = (tiempo / 1000) / 60;           //Calculamos los minutos
  mu = m % 10;                        //Descomponemos los minutos y sacamos el valor de las unidades
  md = (m - mu) / 10;                 //Descomponemos los minutos y sacamos el valor de las decenas

  s = (tiempo / 1000) % 60;           //Calculamos los segundos
  su = s % 10;                        //Descomponemos los segundos y sacamos el valor de las unidades
  sd = (s - su) / 10;                 //Descomponemos los segundos y sacamos el valor de las decenas

  l = (tiempo % 1000);               //Calculamos las milesimas de segundo
  lu = l % 10;                        //Descomponemos las milesimas y sacamos el valor de las unidades
  ld = ((l - lu) / 10) % 10;          //Descomponemos las milesimas y sacamos el valor de las decenas
  lc = (l - (ld * 10) - lu) / 100;    //Descomponemos las milesimas y sacamos el valor de las centenas*/
  //Serial.println(String(m) + ":" + String(s) + ":" + String(l));

}


int Chrono::getM() {
  return m;
}
int Chrono::getMu() {
  return mu;
}
int Chrono::getMd() {
  return md;
}

int Chrono::getS() {
  return s;
}
int Chrono::getSu() {
  return su;
}
int Chrono::getSd() {
  return sd;
}

int Chrono::getL() {
  return l;
}
int Chrono::getLu() {
  return lu;
}
int Chrono::getLd() {
  return ld;
}
int Chrono::getLc() {
  return lc;
}
