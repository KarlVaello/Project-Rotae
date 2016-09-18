char c = ' ';

void setup()
{
  Serial.begin(9600);
  Serial.println("Arduino is ready");
  Serial.println("Remember to select Both NL & CR in the serial monitor");

  // HC-05 default serial speed for AT mode is 38400
  Serial1.begin(9600);
}

void loop()
{

  // Keep reading from HC-05 and send to Arduino Serial Monitor
  if (Serial1.available())
  {
    c = Serial1.read();
    Serial.write(c);
  }

  // Keep reading from Arduino Serial Monitor and send to HC-05
  if (Serial.available())
  {
    c =  Serial.read();
    Serial.print(c);
    Serial1.write(c);
  }
}
