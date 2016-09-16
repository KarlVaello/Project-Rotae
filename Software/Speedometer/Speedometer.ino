#include <SoftwareSerial.h>
SoftwareSerial BTSerial(2, 3); // RX | TX

unsigned long awake_LAST_TIME = 0;
long awake_RESENT_TIME = 4000;

unsigned long currentMillis = millis();

int estadoActual1 = 0;
int estadoActual2 = 0;
int estadoUltimo = 0;
int contador = 0;
float radioEnCm = 30.0; //INGRESAR radio de la rueda en cm
float pi = 3.1416;
float perimetroRueda = 2 * pi * (radioEnCm / 100); //Calcula Perimetro en metros
float distRecorrida = 0;
float distKM = 0;
int tiempo1 = 0;
int tiempo2 = 0;
int tiempo3 = 0;
float tiempo4 = 0;
int currentSpeed = 0;

int sensorPin = 9;

void setup()
{


  Serial.begin(9600);
  Serial.println("Arduino with HC-05 is ready");

  // HC-06 default baud rate is 9600
  BTSerial.begin(9600);
  Serial.println("BTserial started at 9600");

  BTSerial.println("0;A");
  pinMode(sensorPin, INPUT);
}


void loop()
{

  currentMillis = millis();

  estadoActual1 = digitalRead(sensorPin);
  //Serial.println(estadoActual1);

  delay(10);
  estadoActual2 = digitalRead(sensorPin);
  //Si los estados no son iguales, el sketch no hace gran cosa
  if (estadoActual1 == estadoActual2) {
    if (estadoActual1 != estadoUltimo) {
      if (estadoActual1 == HIGH) {
        contador = contador + 1;
        Serial.print ("Vueltas ");
        Serial.println(contador);
        //distancia();
        BTSerial.print("0;" + String(VEL()) + "\n");
        Serial.println(VEL());
        //BTSerial.write(currentSpeed);

      }
    }
  }
  estadoUltimo = estadoActual1;

  /*currentSpeed = random(0, 99);
    Serial.println("0;" + String(currentSpeed));
    BTSerial.print("0;" + String(currentSpeed) + "\n");*/

  /*if (currentMillis - awake_LAST_TIME >= awake_RESENT_TIME) {
    BTSerial.write("0;A\n");
    Serial.println("0;A");
    awake_LAST_TIME = currentMillis;
    }*/


  //delay(4000);

}


int  VEL() {
  if (contador % 2 == 0 ) {
    tiempo1 = millis();
  }
  else {
    tiempo2 = millis();
  }
  tiempo3 = abs(tiempo2 - tiempo1); //hay que pasar el tiempo a hrs
  tiempo4 = (((tiempo3 / 1000.0) / 60.0) / 60.0);
  currentSpeed = ((perimetroRueda / 1000) / tiempo4);
  /*Serial.print(" tiempo1= ");
    Serial.print(tiempo1);
    Serial.print("tiempo2= ");
    Serial.print(tiempo2);
    Serial.print(" tiempo3= ");
    Serial.print(tiempo3);
    Serial.print(" tiempo4= ");
    Serial.println(tiempo4);
    Serial.print("velocidad= ");
    Serial.println(currentSpeed);*/
  return currentSpeed;
}

