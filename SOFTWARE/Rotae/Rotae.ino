#include <UTFT.h>
#include <URTouch.h>
#include <URTouchCD.h>
//#include <UTFT_Buttons.h>


#include "TinyGPS++.h"
TinyGPSPlus gps;

UTFT lcd(ILI9481, 38, 39, 40, 41);
URTouch tactil(6, 5, 4, 3, 2);
//UTFT_Buttons myButtons(&lcd, &tactil);

// Declare which fonts we will be using
extern uint8_t BigFont[];
extern uint8_t SmallFont[];
extern uint8_t arial_bold[];
extern uint8_t various_symbols[];
extern uint8_t CalibriBold32x48[];
extern uint8_t SevenSeg_XXXL_Num[];
extern uint8_t SevenSegNumFontPlus[];
extern uint8_t ArialNumFontPlus[];
extern uint8_t OCR_A_Extended_M[];

float ltd, lon;
double alt;
// SCREEN VARIABLES

long x, y;
int pantalla;
bool channel1Screen = false;
bool hommeScreen = false;


// TIME VARIABLES
int m, mu = 0, md = 0;                     //Declaramos las variables que vamos a usar
int s, su = 0, sd = 0;
int l, lu = 0, ld = 0, lc = 0;
long int tiempo, inicio;


// DISTANCE VARIABLES
float distanceTraveled_M_Complete = 1.45f; //distance traveled metros
int distanceTraveled_KM = 0; //distance traveled metros
int distanceTraveled_M = 0 ; //distance traveled metros
bool cycling = true;


//############ GEARS VARIABLES ###########


// CranksetGear
int currentCranksetGear = 2;
int MAX_CranksetGear = 2;

const int UP_SHIFT_CranksetGear = 12;
int UP_SHIFT_CranksetGear_STATE = 0;
const int DOWN_SHIFT_CranksetGear = 11;
int DOWN_SHIFT_CranksetGear_STATE = 0;


int currentCassetteGear = 0;
int MAX_CassetteGear = 8;

int currentSpeed = 0;

//################ INPUT DATA ##############
bool cassetteShifterOnLine = false;
int cassetteShifterOnLine_LAST_TIME = 0;
int cassetteShifterOnLine_MAX_TIME = 8000;

String inputDataString;


void setup()
{
  Serial.begin(9600);      // open the serial port at 9600 bps:
  Serial1.begin(9600);
  Serial3.begin(9600);

  //Pin MODES
  pinMode(UP_SHIFT_CranksetGear, INPUT);
  pinMode(DOWN_SHIFT_CranksetGear, INPUT);


  lcd.InitLCD(PORTRAIT);
  lcd.clrScr();
  tactil.InitTouch(PORTRAIT);
  tactil.setPrecision(PORTRAIT);
  hommeScreen = true;
  lcd.fillScr(210, 215, 211);
  lcd.setColor(103, 129, 159);
  lcd.fillRect(0, 0, 480, 20);
  tactil.setPrecision(PREC_MEDIUM);

}

int state = 0;

const int DOWN_SHIFT_CassetteGear = 11;
int DOWN_SHIFT_CassetteGear_STATE = 0;
int DOWN_SHIFT_CassetteGear_LASTSTATE = 0;

const int UP_SHIFT_CassetteGear = 12;
int UP_SHIFT_CassetteGear_STATE = 0;
int UP_SHIFT_CassetteGear_LASTSTATE = 0;

char dato = ' ';

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

  //int optionButton, pressed_button;

  // myButtons.setTextFont(BigFont);

  //optionButton = myButtons.addButton( 220,  340, 80,  60, "C");
  //myButtons.drawButtons();

  tiempo = millis() - inicio;        //Calculamos el tiempo que paso desde que se activo el sensor start/stop

  m = (tiempo / 1000) / 60;           //Calculamos los minutos
  mu = m % 10;                        //Descomponemos los minutos y sacamos el valor de las unidades
  md = (m - mu) / 10;                 //Descomponemos los minutos y sacamos el valor de las decenas

  s = (tiempo / 1000) % 60;           //Calculamos los segundos
  su = s % 10;                        //Descomponemos los segundos y sacamos el valor de las unidades
  sd = (s - su) / 10;                 //Descomponemos los segundos y sacamos el valor de las decenas

  l = (tiempo % 1000);                //Calculamos las milesimas de segundo
  lu = l % 10;                        //Descomponemos las milesimas y sacamos el valor de las unidades
  ld = ((l - lu) / 10) % 10;          //Descomponemos las milesimas y sacamos el valor de las decenas
  lc = (l - (ld * 10) - lu) / 100;    //Descomponemos las milesimas y sacamos el valor de las centenas


  uiLCD();

  smartDelay(1000);


  /*while (1)
    {
    if (tactil.dataAvailable() == true)
    {
      pressed_button = myButtons.checkButtons();

      if (pressed_button == optionButton) {
        lcd.print("Cat     ", 10, 220);

      }
    }
    }*/
  onlineStatusPerifericalCheck();

}


void onlineStatusPerifericalCheck() {

  if (millis() > cassetteShifterOnLine_LAST_TIME + cassetteShifterOnLine_MAX_TIME) {
    cassetteShifterOnLine = false;
  }

}

void inputProcessing(String input) {
  Serial.println(input);
  switch (input.charAt(0)) {
    case'0': //VELOCIMETER
      velocimeter(input);
      break;
    case '1': //CASSETTE
      cassetteShiffeter(input.charAt(2));
      cassetteShifterOnLine = true;
      cassetteShifterOnLine_LAST_TIME = millis();
      break;
    case '2': //Crank

      break;
  }
}


void cassetteShiffeter(char input) {
  switch (input) {
    case '0': //gear down
      if (currentCassetteGear > 1) {
        currentCassetteGear--;
      }
      cassetteShifterOnLine_LAST_TIME = millis();
      break;
    case '1': //gear up
      if (currentCassetteGear < MAX_CassetteGear) {
        currentCassetteGear++;
      }
      cassetteShifterOnLine_LAST_TIME = millis();
      break;
    default:
      //nothing
      break;
  }
}

void velocimeter(String input) {
  Serial.println(input);

}


void uiLCD() {

  //##### SPEED PRINT #########
  lcd.setFont(SevenSeg_XXXL_Num);
  lcd.setBackColor(210, 215, 211);
  lcd.setColor(32, 73, 120);
  lcd.print(String(currentSpeed), CENTER, 40);
  lcd.setFont(arial_bold);
  lcd.setBackColor(210, 215, 211);
  lcd.print("km/h", CENTER, 150);
  lcd.drawLine(10, 175, 310, 175);

  //##### CRANKSET GEARS PRINT #########
  lcd.setFont(OCR_A_Extended_M);
  lcd.setBackColor(210, 215, 211);
  lcd.setColor(32, 73, 120);
  if (currentCranksetGear + 1 <= MAX_CranksetGear) {
    lcd.print(String(currentCranksetGear + 1 ), 36, 45);
  } else {
    lcd.print(" ", 36, 45);
  }

  lcd.drawLine(35, 70, 55, 70);

  lcd.setFont(SevenSegNumFontPlus);
  lcd.setBackColor(210, 215, 211);
  lcd.setColor(32, 73, 120);
  lcd.print(String(currentCranksetGear), 30, 75);

  lcd.drawLine(35, 130, 55, 130);

  lcd.setFont(OCR_A_Extended_M);
  lcd.setBackColor(210, 215, 211);
  lcd.setColor(32, 73, 120);
  if (currentCranksetGear - 1 >= 1) {
    lcd.print(String(currentCranksetGear - 1  ), 36, 135);
  } else {
    lcd.print(" ", 36, 135);
  }


  //##### CASSETTE GEARS PRINT #########
  if (cassetteShifterOnLine) {
    lcd.setColor(0, 200, 0);

  } else {
    lcd.setColor(200, 0, 0);
  }
  lcd.fillCircle(268, 35, 5);

  lcd.setFont(OCR_A_Extended_M);
  lcd.setBackColor(210, 215, 211);
  lcd.setColor(32, 73, 120);
  if (currentCassetteGear + 1 <= MAX_CassetteGear) {
    lcd.print(String(currentCassetteGear + 1 ), 261, 45);
  } else {
    lcd.print(" ", 261, 45);
  }

  lcd.drawLine(260, 70, 280, 70);

  lcd.setFont(SevenSegNumFontPlus);
  lcd.setBackColor(210, 215, 211);
  lcd.setColor(32, 73, 120);
  lcd.print(String(currentCassetteGear), 255, 75);

  lcd.drawLine(260, 130, 280, 130);

  lcd.setFont(OCR_A_Extended_M);
  lcd.setBackColor(210, 215, 211);
  lcd.setColor(32, 73, 120);
  if (currentCassetteGear - 1 >= 1) {
    lcd.print(String(currentCassetteGear - 1  ), 261, 135);
  } else {
    lcd.print(" ", 261, 135);
  }


  //GPS

  lcd.setFont(OCR_A_Extended_M);
  lcd.setBackColor(210, 215, 211);
  lcd.setColor(32, 73, 120);
  lcd.print(String(ltd), 70, 200);

  lcd.setFont(OCR_A_Extended_M);
  lcd.setBackColor(210, 215, 211);
  lcd.setColor(32, 73, 120);
  lcd.print(String(lon), 70, 240);



  lcd.setFont(OCR_A_Extended_M);
  lcd.setBackColor(210, 215, 211);
  lcd.setColor(32, 73, 120);
  lcd.print(String(alt), 200, 200);


  //DISTANCE
  lcd.drawLine(10, 310, 310, 310);
  lcd.setFont(CalibriBold32x48);
  lcd.print(String(distanceTraveled_KM), 70, 320);
  lcd.fillRect(142, 356, 148, 362);
  lcd.print(String(distanceTraveled_M), 160, 320);
  lcd.setFont(arial_bold);
  lcd.setBackColor(210, 215, 211);
  lcd.print("km", CENTER, 375);
  lcd.drawLine(10, 175, 310, 175);
  lcd.drawLine(10, 400, 310, 400);

  lcd.setFont(CalibriBold32x48);
  lcd.print(String(md), 18, 410);                      //Imprimimos los valores en el display
  lcd.print(String(mu), 50, 410);
  lcd.setFont(ArialNumFontPlus);
  lcd.print(":", 82, 410);
  lcd.setFont(CalibriBold32x48);
  lcd.print(String(sd), 114, 410);
  lcd.print(String(su), 146, 410);
  lcd.setFont(ArialNumFontPlus);
  lcd.print(":", 178, 410);
  lcd.setFont(CalibriBold32x48);
  lcd.print(String(lc), 210, 410);
  lcd.print(String(ld), 242, 410);
  lcd.print(String(lu), 274, 410);


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
