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



#include "Configuration.h"
#include "Display.h"
#include "LiveData.h"

#include "TinyGPS++.h"

TinyGPSPlus gps;

Display dp;
LiveData ldata;


float ltd, lon;
double alt;
// SCREEN VARIABLES

long x, y;
int pantalla;

int state = 0;
char dato = ' ';
// DISTANCE VARIABLES

float distanceTraveled_M_Complete = 1.45f; //distance traveled metros
int distanceTraveled_KM = 0; //distance traveled metros
int distanceTraveled_M = 0 ; //distance traveled metros


String inputDataString;


void setup()
{
  Serial.begin(mainSerialBaudrate);      // open the serial port at 9600 bps:
  Serial1.begin(bluetoothSerialBaudrate);
  Serial3.begin(gpsSerialBaudrate);

  dp.DisplayInit();

}


void loop()
{

  while (Serial1.available() > 0) {
    inputDataString = Serial1.readStringUntil('\n');
    //currentCassetteGear = int(Serial1.read());
    Serial.println(inputDataString);
    inputProcessing(inputDataString);
    delay(50);
  }
  if (gps.location.isUpdated())
  {
    ltd = gps.location.lat();
    lon = gps.location.lng();
    if (gps.altitude.isValid()) {
      alt = gps.altitude.meters();
    }
  }



  /*tiempo = millis() - inicio;        //Calculamos el tiempo que paso desde que se activo el sensor start/stop

    m = (tiempo / 1000) / 60;           //Calculamos los minutos
    mu = m % 10;                        //Descomponemos los minutos y sacamos el valor de las unidades
    md = (m - mu) / 10;                 //Descomponemos los minutos y sacamos el valor de las decenas

    s = (tiempo / 1000) % 60;           //Calculamos los segundos
    su = s % 10;                        //Descomponemos los segundos y sacamos el valor de las unidades
    sd = (s - su) / 10;                 //Descomponemos los segundos y sacamos el valor de las decenas

    l = (tiempo % 1000);                //Calculamos las milesimas de segundo
    lu = l % 10;                        //Descomponemos las milesimas y sacamos el valor de las unidades
    ld = ((l - lu) / 10) % 10;          //Descomponemos las milesimas y sacamos el valor de las decenas
    lc = (l - (ld * 10) - lu) / 100;    //Descomponemos las milesimas y sacamos el valor de las centenas*/

  dp.DisplayUI(ldata);
  smartDelay(1000);
  //onlineStatusPerifericalCheck();

}


void onlineStatusPerifericalCheck() {
  if (millis() > ldata.getCassetteShifterOnLine_LAST_TIME() + cassetteShifterOnLine_MAX_TIME) {
    ldata.setCassetteShifterOnLine(false);
  }

}

void inputProcessing(String input) {
  Serial.println(input);
  switch (input.charAt(0)) {
    case'0': //VELOCIMETER
      //velocimeter(input);
      break;
    case '1': //CASSETTE
      cassetteShiffeter(input.charAt(2));
      ldata.setCassetteShifterOnLine(true);
      ldata.setCassetteShifterOnLine_LAST_TIME(millis());
      break;
    case '2': //Crank

      break;
  }
}


void cassetteShiffeter(char input) {
  switch (input) {
    case '0': //gear down
      if (ldata.getCurrentCassetteGear() > 1) {
        ldata.setCurrentCassetteGear(ldata.getCurrentCassetteGear() - 1 );
      }
      ldata.setCassetteShifterOnLine_LAST_TIME(millis());
      break;
    case '1': //gear up
      if (ldata.getCurrentCassetteGear() < MAX_CassetteGear) {
        ldata.setCurrentCassetteGear(ldata.getCurrentCassetteGear() + 1);
      }
      ldata.setCassetteShifterOnLine_LAST_TIME(millis());
      break;
    default:
      //nothing
      break;
  }
}

void velocimeter(String input) {
  Serial.println(input);

}





// This custom version of delay() ensures that the gps object
// is being "fed".
static void smartDelay(unsigned long ms)
{
  /*unsigned long start = millis();
    do
    {*/
  while (Serial3.available()) {
    gps.encode(Serial3.read());
  }
  //} while (millis() - start < ms);
}
