#include <ESP8266WiFi.h>  // the ESP8266WiFi.h  lib
const char* SSID = "eir04969720-2.4G"; //"poop";
const char* PASS = "w5hgmmyg"; //"piapiapia";
char server[] = "mail.smtp2go.com";
ADC_MODE(ADC_VCC);  // for reading Voltages
  

int sensorPin = A0;    // select the input pin for the vibration sensor
int sensorValue = 0;  // variable to store the value coming from the sensor

WiFiClient client;
void setup()
{
  Serial.begin(115200);
  delay(10);
  Serial.println("");
  Serial.println("");
  Serial.print("Connecting");
  Serial.println(SSID);
  WiFi.begin(SSID, PASS);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi Connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());


}

void loop()
{
  sensorValue = analogRead(sensorPin);

  if (sensorValue >= 30) {
    byte ret = sendEmail(sensorValue);
  }

  delay(sensorValue);

}

byte sendEmail(int motion)
{
  byte thisByte = 0;
  byte respCode;

  if (client.connect(server, 2525) == 1) {
    Serial.println(F("connected"));
  } else {
    Serial.println(F("connection failed"));
    return 0;
  }
  if (!eRcv()) return 0;

  Serial.println(F("Sending EHLO"));
  client.println("EHLO www.example.com");

  if (!eRcv()) return 0;
  Serial.println(F("Sending auth login"));
  client.println("auth login");

  if (!eRcv()) return 0;
  Serial.println(F("Sending User"));
  // Change to base64, ASCII encoded user
  client.println("b3JhbF9iZWFyZHVpbm8="); // SMTP UserID

  if (!eRcv()) return 0;
  Serial.println(F("Sending Password"));
  // change to base64, ASCII encoded password
  client.println("b3JhbGJlYXI4");//  SMTP Passw

  if (!eRcv()) return 0;
  Serial.println(F("Sending From"));   // change to sender email address
  client.println(F("MAIL From: thenoblelad@gmail.com"));

  if (!eRcv()) return 0;   // change to recipient address
  Serial.println(F("Sending To"));
  client.println(F("RCPT To: c15487922@mydit.ie"));

  if (!eRcv()) return 0;
  Serial.println(F("Sending DATA"));
  client.println(F("DATA"));

  if (!eRcv()) return 0;
  Serial.println(F("Sending email"));   // change to recipient address
  client.println(F("To: c15487922@mydit.ie"));   // change to sender address
  client.println(F("From: thenoblelad@gmail.com"));
  client.println(F("Subject: ORAL BEARDUINO ALERT!\r\n"));

  client.println(F("Toothbrush has been recently activated!"));
  client.print(F("Motion:"));
  Serial.print(motion);
  client.println(F(""));

  client.print(F("Power: "));
  client.print(ESP.getVcc());
  client.println(F("mV"));

  client.print(F("Device ID: "));
  client.println(ESP.getChipId());

  if (!eRcv()) return 0;
  Serial.println(F("Sending QUIT"));
  client.println(F("QUIT"));

  if (!eRcv()) return 0;
  client.stop();
  Serial.println(F("disconnected"));
  return 1;
}

byte eRcv()
{
  byte respCode;
  byte thisByte;
  int loopCount = 0;
  while (!client.available())
  {
    delay(1);
    loopCount++;     // if nothing received for 10 seconds, timeout
    if (loopCount > 10000) {
      client.stop();
      Serial.println(F("\r\nTimeout"));
      return 0;
    }
  }

  respCode = client.peek();
  while (client.available())
  {
    thisByte = client.read();
    Serial.write(thisByte);
  }

  if (respCode >= '4')
  {
    return 0;
  }
  return 1;
}
