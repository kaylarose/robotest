#include <Arduino.h>
//#include "CommonUtils.h"

class NanoMouseSensors {
  byte frontDetector;
  byte frontEmitter;
  byte leftDetector;
  byte leftEmitter;
  byte rightDetector;
  byte rightEmitter;
  private:
    // Ambient light value when emitter is OFF
    int frontAmbient;
    // Light value when emitter is ON
    int frontCombined;
    // Filtered out Ambient light
    int frontReflected;

    int leftAmbient;
    int leftCombined;
    int leftReflected;

    int rightAmbient;
    int rightCombined;
    int rightReflected;

    const static byte NUM_SMOOTHING_READINGS = 10;
    byte smoothingIndex;
    int frontTotal;
    int frontReadings[NUM_SMOOTHING_READINGS];
    int frontSmoothed;
    int leftTotal;
    int leftReadings[NUM_SMOOTHING_READINGS];
    int leftSmoothed;
    int rightTotal;
    int rightReadings[NUM_SMOOTHING_READINGS];
    int rightSmoothed;
  public:
    int front;
    int left;
    int right;
    NanoMouseSensors(byte frontDetectorPin, 
                     byte frontEmitterPin, 
                     byte leftDetectorPin,
                     byte leftEmitterPin,
                     byte rightDetectorPin,
                     byte rightEmitterPin) {

        frontDetector = frontDetectorPin;
        frontEmitter = frontEmitterPin;
        leftDetector = leftDetectorPin;
        leftEmitter = leftEmitterPin;
        rightDetector = rightDetectorPin;
        rightEmitter = rightEmitterPin;

           for (int thisReading = 0; thisReading < NUM_SMOOTHING_READINGS; thisReading++) {
              frontReadings[thisReading] = 0;
              leftReadings[thisReading] = 0;
              rightReadings[thisReading] = 0;
           }
    }

    void configure() {
      pinMode(frontEmitter, OUTPUT);
      pinMode(leftEmitter, OUTPUT);
      pinMode(rightEmitter, OUTPUT);
    }

    void sense() {
      // Emitter ON
       digitalWrite(frontEmitter, HIGH);
       digitalWrite(leftEmitter, HIGH);
       digitalWrite(rightEmitter, HIGH);
       delay(1);
       frontCombined = analogRead(frontDetector);
       leftCombined = analogRead(leftDetector);
       rightCombined = analogRead(rightDetector);
       // Emitter OFF
       digitalWrite(frontEmitter, LOW);
       digitalWrite(leftEmitter, LOW);
       digitalWrite(rightEmitter, LOW);
       delay(1);
       // Record Ambient Light
       frontAmbient = analogRead(frontDetector);
       leftAmbient = analogRead(leftDetector);
       rightAmbient = analogRead(rightDetector);
       // Filter out Ambient Light to get true object detection based on reflected light
       frontReflected = frontCombined - frontAmbient;
       leftReflected = leftCombined - leftAmbient;
       rightReflected = rightCombined - rightAmbient;

        // Smooth out with moving averages
        // Note the first time around index defaults to 0
        // Remove last item from total, and will cycle through array
        // starting over when number of max readings reached
        // Higer max number will cause the initial "smoothed"
        // value to take longer to calculate.
       frontTotal -= frontReadings[smoothingIndex]; 
       frontReadings[smoothingIndex] = frontReflected;
       frontTotal += frontReadings[smoothingIndex];
       leftTotal -= leftReadings[smoothingIndex]; 
       leftReadings[smoothingIndex] = leftReflected;
       leftTotal += leftReadings[smoothingIndex];
       rightTotal -= rightReadings[smoothingIndex]; 
       rightReadings[smoothingIndex] = rightReflected;
       rightTotal += rightReadings[smoothingIndex];
       smoothingIndex += 1;

       if (smoothingIndex >= NUM_SMOOTHING_READINGS) {
         smoothingIndex = 0;
       }

       frontSmoothed = frontTotal/NUM_SMOOTHING_READINGS;
       leftSmoothed = leftTotal/NUM_SMOOTHING_READINGS;
       rightSmoothed = rightTotal/NUM_SMOOTHING_READINGS;

       front = frontSmoothed;
       left = leftSmoothed;
       right = rightSmoothed;
    }
    
    void view() {
      Log::println("L: ", left, "\t",
                   "F: ", front, "\t",
                   "R: ", right);
    }

    void reinitialize() {
      // Flood the smoothing array with new values
      // should be used after making a turn or movement,
      // so that values pre-move are not averaged with those POST-move.
    
       for (byte i = 0; i < NUM_SMOOTHING_READINGS; i++) {
          sense();
       }
    }
};
