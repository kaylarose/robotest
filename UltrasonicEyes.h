#include <Arduino.h>
#include <Servo.h>
#include <Adafruit_MotorShield.h>
#include <NewPing.h>
//#include "CommonUtils.h"

// #define LEFT_DIRECTION -1
// #define RIGHT_DIRECTION 1
#define SCREEEEEEECHHHH 50
// Distance at which to stomp the brakes (units: cm. originally 20)
#define DANGER_AHEAD 80 // Distance at which to assume you can't go left or right (units: cm. originally 20)
#define TRIGGER_PIN 12
#define ECHO_PIN 13

#define SERVO_NECK_PIN 10 // Pin 10
#define MAX_DISTANCE 500
#define DELAY_FOR_ADJUSTING_EYES_TO_NEW_LOC 1000
#define AVOID_TO_RIGHT 0
#define AVOID_TO_LEFT 1
#define AVOID_TO_BACK 2
#define DONT_AVOID -1

// Create the motor shield object with the default I2C address
// Adafruit_MotorShield AFMS = Adafruit_MotorShield();
// int motorTurnTimeMs;
//
// int Echo = A4;
// int Trig = A5;

// Use the built in Arduino Servo library (we could also use the AdaFruit Stepper Abstraction)
Servo servo1;
//NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
//Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);

class UltrasonicEyes
{
  private:
    //NewPing mySonarEyes;
    // Adafruit_DCMotor* myRightMotor;
    // int motorTurnTimeMs = MOTOR_TURN_90_DEGREE_TIME_MS;
    int triggerPin, echoPin;
    
  public:
    void attach() {
      Log::println("Initialize Eyes...");
      // pinMode(trigPin, OUTPUT);
      // pinMode(echoPin, INPUT);
      //mySonarEyes = sonar;
      // Attach a servo to pin SERVO_NECK_PIN
      this->triggerPin = TRIGGER_PIN;
      this->echoPin = ECHO_PIN;
      pinMode(triggerPin, OUTPUT);
      pinMode(echoPin, INPUT);
      
      servo1.attach(SERVO_NECK_PIN);
    }
//
//    int distanceTest() {
//        Log::println("Start Distance Test....");
//        //echoCheck();
//        Log::println("Echo Test Complete:");
//        unsigned int x = mySonarEyes.ping();  
//        //double y = x / US_ROUNDTRIP_CM;
//        Log::print("Distance Test Complete:");
//        Log::print(x);
//        //Log::print(" ");
//        //Log::print(y);
//        Log::println(".....");
//        return x;
//    }

    double distanceTest() {
        Log::println("Start Distance Test....");
        // Make sure that trigger pin is LOW.
        digitalWrite(triggerPin, LOW);
        delayMicroseconds(2);
        // Hold trigger for 10 microseconds, which is signal for sensor to measure distance.
        digitalWrite(triggerPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(triggerPin, LOW);

        // Measure the length of echo signal, which is equal to the time needed for sound to go there and back.
        unsigned long durationMicroSec = pulseIn(echoPin, HIGH, 250000);
        double distanceCm = durationMicroSec / 2.0 * 0.0343;

        Log::println("======Distance Test Complete:========");
        Log::print("Cm: ");
        Log::print(distanceCm);
        Log::print(" MicroSec Duraction: ");
        Log::println(durationMicroSec);
        Log::println("==============");

        if (distanceCm == 0 || distanceCm > 400) {
            return -1.0 ;
        } else {
            return distanceCm;
        }
    
//        Log::print("Distance Test Complete:");
//        Log::print(distanceCm);
//        Log::println(".....");
    }
    
    void eyesFront() {
      //Log::println("Test 90 front!!!!");

      // Move servo to 0 deg
      eyesLook(90);
    }

    void eyesLeft() {
      //Log::println("Test 180 left!!!!");

      // Move servo to 180 deg
      eyesLook(180);
    }

    void eyesRight() {
      //Log::println("Test 5 right!!!!");

      // Move servo to -180 deg
      eyesLook(5);
    }

    void eyesLook(int degrees) {
      // Move servo to X deg
      servo1.write(degrees);
      delay(DELAY_FOR_ADJUSTING_EYES_TO_NEW_LOC);
    }

    void eyesStop() {
        // Stop Servo
    }

   void echoCheck() { // Timer2 interrupt calls this function every 24uS where you can check the ping status.
    // Don't do anything here!
//    if (mySonarEyes.check_timer()) { // This is how you check to see if the ping was received.
//      // Here's where you can add code.
//      Serial.print("Ping: ");
//      Serial.print(mySonarEyes.ping_result / US_ROUNDTRIP_CM); // Ping returned, uS result in ping_result, convert to cm with US_ROUNDTRIP_CM.
//      Serial.println("cm");
//    } else {
//      Serial.println("Timer not complete!");
//    }
    // Don't do anything here!
  }

};
