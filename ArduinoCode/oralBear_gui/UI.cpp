#include "UI.h"

#include <MCUFRIEND_kbv.h>

//pins
#define YP A2   // analog
#define XM A3   // analog
#define YM 8    // digital
#define XP 9    // digital

//TouchScreen co-ordinates
#define TS_MINX 204
#define TS_MINY 195
#define TS_MAXX 948
#define TS_MAXY 910

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
#define TEAL        0x03EF
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

#define MINPRESSURE 0
#define MAXPRESSURE 1000

int currentPage = 1;

//UI::UI() {
//
//}

MCUFRIEND_kbv tft;

void UI::init() {
  tft.reset();
  tft.begin(0x9341);
  tft.setRotation(1);
  _ts = new TouchScreen(XP, YP, XM, YM, 300);
  welcomeScreen();
  currentPage = 1;
}

void UI::btnPressed() {
  TSPoint p = _ts->getPoint();

  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  pinMode(XM, OUTPUT);
  pinMode(YM, OUTPUT);

  if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
    // scale from 0->1023 to tft.width
    //    p.x = map(p.x, TS_MINX, TS_MAXX, tft.width(), 0);
    //    p.y = (tft.height() - map(p.y, TS_MINY, TS_MAXY, tft.height(), 0));
    p.x = map(p.x, TS_MAXX, TS_MINX, 0, 320);
    p.y = map(p.y, TS_MAXY, TS_MINY, 0, 240);

    //Welcome Screen
    if (currentPage == 1) {
      if (p.x > 60 && p.x < 260 && p.y > 180 && p.y < 220) // The user has pressed inside the red rectangle
      {
        currentPage = 2;
        menuScreen();
      }
    }

    //Start Menu Screen
    if (currentPage == 2) {
      //Back Button
      if (p.x > 15 && p.x < 55 && p.y > 20 && p.y < 70)
      {
        currentPage = 1;
        welcomeScreen();
      }
      //Timer Button
      if (p.x > 80 && p.x < 235 && p.y > 20 && p.y < 70)
      {
        currentPage = 3;
        timerScreen();
      }
    }

    //Timer Screen
    if (currentPage == 3) {
      //Back Button
      if (p.x > 15 && p.x < 55 && p.y > 20 && p.y < 70)
      {
        currentPage = 2;
        menuScreen();
      }
    }


    // this code goes through all the buttons to error-check its functionality
    //    for (uint8_t b = 0; b < 15; b++) {
    //      if (buttons[b].contains(p.x, p.y)) {
    //        Serial.print("Pressing: "); Serial.println(b);
    //        buttons[b].press(true);  // tell the button it is pressed
    //      } else {
    //        buttons[b].press(false);  // tell the button it is NOT pressed
    //    }
  }
  delay(10); // UI debouncing
}



void UI::welcomeScreen() {
  tft.fillScreen(BLACK);                 //Erase the screen
  tft.drawRect(0, 0, 319, 240, WHITE);   //Draw white frame

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

void UI::menuScreen() {
  tft.fillScreen(BLACK);                 //Erase the screen
  tft.drawRect(0, 0, 319, 240, WHITE);   //Draw white frame

  // create buttons
  //  for (uint8_t row = 0; row < 3; row++) {
  //
  //    for (uint8_t col = 0; col < 1; col++) {
  //      //initButton(&MCU, x, y, w, h, outline, fill, text)
  //      buttons[col + row * 3].initButton(&tft, BUTTON_X + col * (BUTTON_W + BUTTON_SPACING_X),
  //                                        BUTTON_Y + row * (BUTTON_H + BUTTON_SPACING_Y),
  //                                        BUTTON_W, BUTTON_H, WHITE, btncolors[col + row * 3], WHITE,
  //                                        btnlabels[col + row * 3], BUTTON_TEXTSIZE);
  //
  //      buttons[col + row * 3].drawButton();
  //    }
  //  }

  tft.fillRect(15, 20, 40, 30, PURPLE);
  tft.drawRect(15, 20, 40, 30, WHITE);
  tft.setCursor(23, 27);
  tft.setTextColor(BLACK);
  tft.setTextSize(2.5);
  tft.print("<-");

  tft.fillRect(80, 20, 155, 50, ORANGE);
  tft.drawRect(80, 20, 155, 50, WHITE);
  tft.setCursor(98, 27);
  tft.setTextColor(BLACK);
  tft.setTextSize(4);
  tft.print("Timer");
}

float timeDelta = 0;
float timeAccumulator = 60;
int last = 0;

void UI::timerScreen() {
  tft.fillScreen(BLACK);                 //Erase the screen
  tft.drawRect(0, 0, 319, 240, WHITE);   //Draw white frame

  tft.fillRect(15, 20, 40, 30, PURPLE);
  tft.drawRect(15, 20, 40, 30, WHITE);
  tft.setCursor(23, 27);
  tft.setTextColor(BLACK);
  tft.setTextSize(2.5);
  tft.print("<-");

  int now = millis();
  timeDelta = (now - last) / 1000.0f;
  last = now;

  timeAccumulator -= timeDelta;

  tft.setCursor(100, 100);
  tft.setTextColor(TEAL);
  tft.setTextSize(4);
  tft.print(timeAccumulator);

  if (timeAccumulator <= 1) {
    timeAccumulator = 60;
  }

  delay(1000);

}








