#include "checkEmail.h"

//ADC_MODE(ADC_VCC);

checkEmail chk;

int sensorPin = A0;    // select the input pin for the vibration sensor
int sensorValue = 0;  // variable to store the value coming from the sensor

void setup()
{
  Serial.begin(115200);
  delay(10);
  chk.init();
}

void loop()
{
  sensorValue = analogRead(sensorPin);

  if (sensorValue >= 35) {
    byte ret = chk.sendEmail(sensorValue);
  }

  delay(sensorValue);
  //delay(180000);  // wait for 3 minutes

}


