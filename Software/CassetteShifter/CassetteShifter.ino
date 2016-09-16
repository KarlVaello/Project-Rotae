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

const int DOWN_SHIFT_CassetteGear = 11;
int DOWN_SHIFT_CassetteGear_STATE = 0;
int DOWN_SHIFT_CassetteGear_LASTSTATE = 0;

const int UP_SHIFT_CassetteGear = 12;
int UP_SHIFT_CassetteGear_STATE = 0;
int UP_SHIFT_CassetteGear_LASTSTATE = 0;

unsigned long awake_LAST_TIME = 0;
long awake_RESENT_TIME = 4000;

int ledPin = 13;
unsigned long currentMillis = millis();

#include <SoftwareSerial.h>
SoftwareSerial BTSerial(2, 3); // RX | TX
int state = 0;
void setup()
{
  Serial.begin(9600);
  Serial.println("Arduino with HC-05 is ready");

  BTSerial.begin(9600);
  Serial.println("BTserial started at 9600");

  digitalWrite(ledPin, LOW);

  pinMode(UP_SHIFT_CassetteGear, INPUT);
  pinMode(DOWN_SHIFT_CassetteGear, INPUT);
  pinMode(ledPin, OUTPUT);
  BTSerial.println("1;A");
}

void loop()
{
  currentMillis = millis();

  UP_SHIFT_CassetteGear_STATE = digitalRead(UP_SHIFT_CassetteGear);
  DOWN_SHIFT_CassetteGear_STATE = digitalRead(DOWN_SHIFT_CassetteGear);

  if (UP_SHIFT_CassetteGear_STATE != UP_SHIFT_CassetteGear_LASTSTATE) {
    if (UP_SHIFT_CassetteGear_STATE == HIGH) {
      digitalWrite(ledPin, HIGH);
      BTSerial.write("1;1\n");
      Serial.println("1;1");
    }
    delay(50);
  }
  UP_SHIFT_CassetteGear_LASTSTATE = UP_SHIFT_CassetteGear_STATE;


  if ( DOWN_SHIFT_CassetteGear_STATE != DOWN_SHIFT_CassetteGear_LASTSTATE) {

    if (DOWN_SHIFT_CassetteGear_STATE == HIGH) {
      digitalWrite(ledPin, LOW);
      BTSerial.write("1;0\n");
      Serial.println("1;0");
    }
    delay(50);
  }
  DOWN_SHIFT_CassetteGear_LASTSTATE = DOWN_SHIFT_CassetteGear_STATE;

  if(currentMillis - awake_LAST_TIME >= awake_RESENT_TIME) {
    BTSerial.write("1;A\n");
    Serial.println("1;A");
    awake_LAST_TIME = currentMillis;   
  }
}
