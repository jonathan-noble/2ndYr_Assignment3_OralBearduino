/* Vibration Sensor (Shake Switch) - Testing with buzzer     */
   
const int buzzer = D8; //Buzzer connected to pin 8 of Arduino uno / mega
int sensor;           //Variable to store analog value (0-1023)


void setup()
{
  Serial.begin(115200);      //Only for debugging
  pinMode(buzzer, OUTPUT);
  Serial.println("Connecting Sensor");
}

void loop()
{
  sensor = analogRead(A0);


  //While sensor is not moving, analog pin receive 1023~1024 value
  if (sensor<1024){
    tone(buzzer, 500);
    Serial.print("Sensor Value: ");
    Serial.println(sensor);
  }
  
  else{ 
    noTone(buzzer);
    Serial.print("Sensor Value: ");
    Serial.println(sensor);
  }
  
  
  delay(100); //Small delay
}
