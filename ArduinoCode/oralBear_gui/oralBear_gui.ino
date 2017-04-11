/*
    User interface for Robobearduino,
    will be displayed on the tft lcd screen
    1.home menu
      options:
        -timer
        -game
        -tips/advice on how to brush teeth
*/

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library
#include <TouchScreen.h>
#include <MCUFRIEND_kbv.h>

#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0
#define LCD_RESET A4

// 16-bit color values into their names
#define BLACK       0x0000      /*   0,   0,   0 */
#define NAVY        0x000F      /*   0,   0, 128 */
#define DARKGREEN   0x03E0      /*   0, 128,   0 */
#define DARKCYAN    0x03EF      /*   0, 128, 128 */
#define MAROON      0x7800      /* 128,   0,   0 */
#define PURPLE      0x780F      /* 128,   0, 128 */
#define OLIVE       0x7BE0      /* 128, 128,   0 */
#define LIGHTGREY   0xC618      /* 192, 192, 192 */
#define DARKGREY    0x7BEF      /* 128, 128, 128 */
#define BLUE        0x001F      /*   0,   0, 255 */
#define GREEN       0x07E0      /*   0, 255,   0 */
#define CYAN        0x07FF      /*   0, 255, 255 */
#define RED         0xF800      /* 255,   0,   0 */
#define MAGENTA     0xF81F      /* 255,   0, 255 */
#define YELLOW      0xFFE0      /* 255, 255,   0 */
#define WHITE       0xFFFF      /* 255, 255, 255 */
#define ORANGE      0xFD20      /* 255, 165,   0 */
#define GREENYELLOW 0xAFE5      /* 173, 255,  47 */
#define PINK        0xF81F

/******************* UI details */
#define BUTTON_X 120
#define BUTTON_Y 100
#define BUTTON_W 60
#define BUTTON_H 30
#define BUTTON_SPACING_X 20
#define BUTTON_SPACING_Y 20
#define BUTTON_TEXTSIZE 2

//pins
#define YP A2   // analog
#define XM A3   // analog
#define YM 8    // digital
#define XP 9    // digital

//TouchScreen co-ordinates on welcomeScreen()
#define TS_MINX 204
#define TS_MINY 195
#define TS_MAXX 948
#define TS_MAXY 910

//Old pins & coords
//#define YP A3   // analog
//#define XM A2   // analog
//#define YM 9    // digital
//#define XP 8    // digital

//#define TS_MINX 100
//#define TS_MAXX 920
//#define TS_MINY 70
//#define TS_MAXY 900

MCUFRIEND_kbv tft;
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
Adafruit_GFX_Button buttons[15];

char btnlabels[15][5] = {"Game", "", "", "Timer", "", "", "Guide" , "", "", "", "", "", "", "", "" };
uint16_t btncolors[3] = {DARKGREEN, CYAN, ORANGE};
char currentPage = '1';

void setup() {
  Serial.begin(9600);

  tft.reset();

  uint16_t identifier = tft.readID();
  if (identifier == 0x9325) {
    Serial.println(F("Found ILI9325 LCD driver"));
  } else if (identifier == 0x9328) {
    Serial.println(F("Found ILI9328 LCD driver"));
  } else if (identifier == 0x4535) {
    Serial.println(F("Found LGDP4535 LCD driver"));
  } else if (identifier == 0x7575) {
    Serial.println(F("Found HX8347G LCD driver"));
  } else if (identifier == 0x9341) {
    Serial.println(F("Found ILI9341 LCD driver"));
  } else if (identifier == 0x7783) {
    Serial.println(F("Found ST7781 LCD driver"));
  } else if (identifier == 0x8230) {
    Serial.println(F("Found UC8230 LCD driver"));
  }
  else if (identifier == 0x8357) {
    Serial.println(F("Found HX8357D LCD driver"));
  } else if (identifier == 0x0101)
  {
    identifier = 0x9341;
    Serial.println(F("Found 0x9341 LCD driver"));
  } else {
    Serial.print(F("Unknown LCD driver chip: "));
    Serial.println(identifier, HEX);
    identifier = 0x9341;
  }

  tft.begin(identifier);
  tft.setRotation(1);
  tft.fillScreen(BLACK);

  //Draw white frame
  //tft.drawRect(0,0,240,320,WHITE);  //if setRotation(0)
  tft.drawRect(0, 0, 319, 240, WHITE);

  welcomeScreen();
  currentPage = '1';

}

#define MINPRESSURE 0
#define MAXPRESSURE 1000
boolean welcomeBtn = true;
boolean backBtn = true;

void loop() {

  digitalWrite(13, HIGH);
  digitalWrite(13, LOW);
  TSPoint p = ts.getPoint();
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);

  if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
    // scale from 0->1023 to tft.width
    //    p.x = map(p.x, TS_MINX, TS_MAXX, tft.width(), 0);
    //    p.y = (tft.height() - map(p.y, TS_MINY, TS_MAXY, tft.height(), 0));
    p.x = map(p.x, TS_MAXX, TS_MINX, 0, 320);
    p.y = map(p.y, TS_MAXY, TS_MINY, 0, 240);

    if (currentPage = '1') {
      if (p.x > 60 && p.x < 260 && p.y > 180 && p.y < 220 && welcomeBtn) // The user has pressed inside the red rectangle
      {
        welcomeBtn = false; //Disable button
        currentPage = '2';
        menuScreen();
      }

    if (currentPage = '2') { 
      if (p.x > 80 && p.x < 235 && p.y > 25 && p.y < 75 && backBtn) // The user has pressed inside the red rectangle
      {
        backBtn = false; //Disable button
        setup();
      }
    }
  }

  // this code goes through all the buttons to error-check its functionality
  for (uint8_t b = 0; b < 15; b++) {
    if (buttons[b].contains(p.x, p.y)) {
      Serial.print("Pressing: "); Serial.println(b);
      buttons[b].press(true);  // tell the button it is pressed
    } else {
      buttons[b].press(false);  // tell the button it is NOT pressed
    }
  }
  delay(10); // UI debouncing
}

}

void welcomeScreen() {
  //Print "Hello" Text
  tft.setCursor(100, 30);
  tft.setTextColor(WHITE);
  tft.setTextSize(4);
  tft.print("Hello");

  //Print "Master!" text
  tft.setCursor(80, 100);
  tft.setTextColor(RED);
  tft.setTextSize(4);
  tft.print("Master!");

  //Create Red Button
  tft.fillRect(60, 180, 200, 40, RED);
  tft.drawRect(60, 180, 200, 40, WHITE);
  tft.setCursor(70, 188);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.print("START MENU");

}

void menuScreen() {
  //Erase the screen
  tft.fillScreen(BLACK);

  //Draw frame
  tft.drawRect(0, 0, 319, 240, WHITE);

  // create buttons
  for (uint8_t row = 0; row < 3; row++) {

    for (uint8_t col = 0; col < 1; col++) {
      //initButton(&MCU, x, y, w, h, outline, fill, text)
      buttons[col + row * 3].initButton(&tft, BUTTON_X + col * (BUTTON_W + BUTTON_SPACING_X),
                                        BUTTON_Y + row * (BUTTON_H + BUTTON_SPACING_Y),
                                        BUTTON_W, BUTTON_H, WHITE, btncolors[col + row * 3], WHITE,
                                        btnlabels[col + row * 3], BUTTON_TEXTSIZE);

      buttons[col + row * 3].drawButton();
    }
  }

  tft.drawRect(80, 25, 155, 50, RED);
}

void gameScreen() {
  //Erase the screen
  tft.fillScreen(BLACK);

  //Draw frame
  tft.drawRect(0, 0, 319, 240, WHITE);

  tft.setCursor(100, 30);
  tft.setTextColor(WHITE);
  tft.setTextSize(4);
  tft.print("Hello");
}





