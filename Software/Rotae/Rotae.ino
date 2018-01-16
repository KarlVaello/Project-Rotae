#include <TFT_ST7735.h> // Graphics and font library for ST7735 driver chip
#include <SPI.h>

TFT_ST7735 tft = TFT_ST7735();  // Invoke library, pins defined in User_Setup.h

#define color_background 0xEF9E
#define color_speed 0x256C
#define color_a 0x0000


int sensorPin = 3;

int currentState_A = 0;
int currentState_B = 0;
int lastState = 0;

int spinCount = 0;
float rRueda = 29.5; //INGRESAR radio de la rueda en cm
float pi = 3.1416;
float pRueda = 2 * pi * (rRueda / 100); //Calcula Perimetro en metros

int time_A = 0; //tiempo paso de rueda
int time_B = 0; //timepo paso de rueda
int diferenceTime = 0;
float timeHours = 0;


int currentSpeed = 0;
int currentDistance = 0;

void setup()
{
  Serial.begin(9600);
  Serial.print("Setup");

  pinMode(sensorPin, INPUT);

  tft.init();
  tft.setRotation(0);
  tft.fillScreen(color_background);
  tft.fillRect(-2, 0, 150, 150, color_background);
  currentDistance = 0;
  currentSpeed = 0;
}


void loop()
{
  //priemra lectura
  currentState_A = digitalRead(sensorPin);
  delay(10);
  //segunda lencuta
  currentState_B = digitalRead(sensorPin);

  if (currentState_A == currentState_B) {
    if (currentState_A != lastState) { // diferentes estados actua
      if (currentState_A == HIGH) {

        spinCount = spinCount + 1; // suma una vuelta

        currentSpeed = velocityCalculations(); // calcualdora de velocidad
        currentDistance = currentDistance + pRueda;

        //actualización tft
        tft.setTextColor(color_speed, color_background);
        tft.fillRect(-2, 20, 130, 50, color_background);
        tft.setTextSize(1);
        char copy[3];
        String(currentSpeed).toCharArray(copy, 3);
        tft.drawCentreString(copy, 64, 20, 7); // Overwrite the text to clear it7
        tft.drawCentreString("km/h", 64, 70, 1); // Overwrite the text to clear it
        tft.drawNumber(currentDistance, 5, 100, 4); // Overwrite the text to clear it
      }
    }
  }
  lastState = currentState_A; //guardamos el útimo estado
}


// funcion que calcula y devuelve la velocidad. en km/h
int  velocityCalculations() {
  int speedCalculated;
  if (spinCount % 2 == 0 ) { // sabemos si la vuelta e spar o impar
    time_A = millis();
  }
  else {
    time_B = millis();
  }

  diferenceTime = abs(time_B - time_A); //resta e ultiam vuelta menos la anterior para saber el tiempo transcurrido

  timeHours = (((diferenceTime / 1000.0) / 60.0) / 60.0); //pasamos el tiempo a horas
  
  return speedCalculated;
}

