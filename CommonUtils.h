#include <Arduino.h>

#define DEBUG 1

#ifdef DEBUG
  #define DPRINT(...)    Serial.print(__VA_ARGS__);
  #define DPRINTLN(...)  Serial.println(__VA_ARGS__);
#else
  #define DPRINT(...)
  #define DPRINTLN(...)
#endif

class CommonUtils
{
  public:
    void blinkTest() {
      DPRINTLN("Blink Board...");
      // Test Code to Validate Board is Responding (Will Blink LED)
      digitalWrite(LED_BUILTIN, HIGH);
      delay(1000);
      digitalWrite(LED_BUILTIN, LOW);
      delay(1000);
    }
};

class Log
{
  public:
    template<typename X>
    static void print(X&& x) {
      Serial.print(x);
    }

    template<typename X, typename... Args>
    static void print(X&& x, Args&&... args) {
      Serial.print(x);
      print(args...);
    }

    template<typename X>
    static void println(X&& x) {
      Serial.println(x);
    }

    template<typename X, typename... Args>
    static void println(X&& x, Args&&... args) {
      Serial.print(x);
      println(args...);
    }
};
