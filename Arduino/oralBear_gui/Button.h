#ifndef Button_h
#define Button_h

#include <Arduino.h>
#include <Adafruit_GFX.h>

// 16-bit color values into their names
#define BLACK       0x0000      /*   0,   0,   0 */
#define DARKGREEN   0x03E0      /*   0, 128,   0 */
#define DARKCYAN    0x03EF      /*   0, 128, 128 */
#define TEAL        0x03EF
#define BLUE        0x001F      /*   0,   0, 255 */
#define MAROON      0x7800      /* 128,   0,   0 */
#define LIGHTGREY   0xC618      /* 192, 192, 192 */
#define PURPLE      0x780F      /* 128,   0, 128 */
#define GREEN       0x07E0      /*   0, 255,   0 */
#define CYAN        0x07FF      /*   0, 255, 255 */
#define RED         0xF800      /* 255,   0,   0 */
#define YELLOW      0xFFE0      /* 255, 255,   0 */
#define WHITE       0xFFFF      /* 255, 255, 255 */
#define ORANGE      0xFD20      /* 255, 165,   0 */
#define MAGENTA     0xF81F      /* 255,   0, 255 */


class Button {
  public:
    Button();

   /*----functions are declared here----*/
    void drawButton();
    
    bool hit(uint16_t xpos, uint16_t ypos);

    void showButtonAndDraw(bool isVisible);
    void activateButtonAndDraw(bool activate);
    
    void (*callback)();

    Adafruit_GFX *gfx;

    unsigned int x, y, width, height; //variables also used in UI.h
    int id;
    bool visible;
    bool active;
    bool enabled;

  private:
    void animateButtonClick();
};

#endif

