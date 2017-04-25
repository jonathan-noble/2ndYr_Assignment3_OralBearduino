#ifndef checkEmail_h
#define checkEmail_h

#include <Arduino.h>

class checkEmail {
  public: 
    checkEmail();

    void init();
    byte rcvEmail();
    byte sendEmail(int motion);
};

#endif

