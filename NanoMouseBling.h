#include <Arduino.h>
//#include "CommonUtils.h"

class NanoMouseBling {
  // RGB LED Info
  byte redLED;
  byte greenLED;
  byte blueLED;

  private:
    // Ambient light value when emitter is OFF

  public:
    NanoMouseBling(byte redLEDPin, 
                   byte greenLEDPin, 
                   byte blueLEDPin) {

        redLED = redLEDPin;
        greenLED = greenLEDPin;
        blueLED = blueLEDPin;
    }

    void configure() {
      pinMode(redLED, OUTPUT);
      pinMode(greenLED, OUTPUT);
      pinMode(blueLED, OUTPUT);
    }
    
    void setColor(int red, int green, int blue) {

      #ifdef COMMON_ANODE
        Log::println("ANODE");
        red = 255 - red;
        green = 255 - green;
        blue = 255 - blue;
      #endif
            Log::println("R: ", red, "\t",
                   "G: ", green, "\t",
                   "B: ", blue);
      analogWrite(redLED, red);
      //delay(3);
      digitalWrite(greenLED, green);
      //delay(3);
      digitalWrite(blueLED, blue);
      //delay(3); 
    }

    void red() {
      setColor(255, 0, 0);
    }

    void green() {
      setColor(0, 255, 0);
    }

    void blue() {
      setColor(0, 0, 255);
    }     

    void yellow() {
      //setColor(255, 100, 0);
      setColor(200, 100, 0);
    }

    void orange() {
      //setColor(255, 25, 0);
      setColor(245, 25, 0);
    }
    
    void purple() {
      //etColor(80, 0, 80);
      setColor(125, 0, 80);
    }

    void pink() {
      setColor(225, 0, 80);
    }
    
    void aqua() {
      // setColor(0, 255, 255);
      setColor(0, 255, 150); // Adjusted for LED color wonkiness
    }

    void white() {
      setColor(150, 255, 255);
      //setColor(255, 255, 255);
      //setColor(255, 150, 150);  // Adjusted for LED color wonkiness
    }

    void off() {
      setColor(0, 0, 0);
    }
};
