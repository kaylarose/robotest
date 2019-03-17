/*
  This is a test sketch for the Adafruit assembled Motor Shield for Arduino v2
  It won't work with v1.x motor shields! Only for the v2's with built in PWM
  control

  For use with the Adafruit Motor Shield v2
  ---->	http://www.adafruit.com/products/1438

  This sketch creates a fun motor party on your desk *whiirrr*
  Connect a unipolar/bipolar stepper to M3/M4
  Connect a DC motor to M1
  Connect a hobby servo to SERVO1
*/
#include <Arduino.h>

#include <Wire.h>
#include <Servo.h>
#include "CommonUtils.h"
#include "AdaMotors.h"
#include "UltrasonicEyes.h"

AdaMotors motors;
UltrasonicEyes* eyes;

// Connect a stepper motor with 200 steps per revolution (1.8 degree)
// to motor port #2 (M3 and M4)
//Adafruit_StepperMotor *myStepper = AFMS.getStepper(200, 2);

// We'll also test out the built in Arduino Servo library
//Servo servo1;

void setup() {
  // set up Serial library at 9600 bps
  Serial.begin(9600);

  Log::println("Start Robot");
  Log::println("=====It\'s the DEVASTATOR motor party (test run)!=====");

  eyes->attach();

  motors.attach();
  motors.adjustSpeed(255); // Full speed ahead

  // setup the stepper
  //myStepper->setSpeed(10);  // 10 rpm
}

void beOnTheLookout() {
  eyes->eyesFront(); //setservo position according to scaled value
  //delay(DELAY_FOR_ADJUSTING_EYES_TO_NEW_LOC);

  int middleDistance = eyes->distanceTest();
  delay(1000);
  Log::print("middleDistance=");
  Log::println(middleDistance);

  if(middleDistance <= SCREEEEEEECHHHH)
  {
    Log::println("STOP!!");
    motors.stop();
    //delay(500);
    //Log::println("LOOK RIGHT!!");
    //eyes->eyesRight();

    // myservo.write(5);
    // delay(1000);
    int rightDistance = eyes->distanceTest();

    // delay(500);
    //  myservo.write(90);
    // delay(1000);
    // myservo.write(180);
    // delay(1000);
    //Log::println("LOOK LEFT!!");
    //eyes->eyesLeft();
    int leftDistance = eyes->distanceTest();

    // delay(500);
    // myservo.write(90);
    // delay(1000);
    Log::println("RESET TO FRONT!!");
    eyes->eyesFront();
    Log::print("Forward: ");
    Log::print(middleDistance);
    Log::print(" Right: ");
    Log::print(rightDistance);
    Log::print(" Left: ");
    Log::println(leftDistance);
    if((rightDistance > leftDistance) && (rightDistance<=DANGER_AHEAD))
    {
      //motors.right();
      //delay(360);
     }
     else if ((rightDistance < leftDistance) && (leftDistance<=DANGER_AHEAD))
     {
      //motors.left();
      //delay(360);
     }
     else if (rightDistance <= DANGER_AHEAD || leftDistance <= DANGER_AHEAD)
     {
      // If Danger Ahead...throw it in reverse
       Log::print("Throw it in reverse! DANGER AHEAD in less than (CM):");
       Log::println(DANGER_AHEAD);
      //motors.backward();
      //delay(180);
     }
     else
     {
             Log::print("We're fine");

      //motors.forward();
     }
  }
  else
      Log::println("All clear. Forge ahead good rover!!");
      motors.forward();

}

int i;
void loop() {
  Log::println("0 Run: Fwd Faster");
  //beOnTheLookout();
  //  eyes->eyesFront(); //setservo position according to scaled value
  //delay(DELAY_FOR_ADJUSTING_EYES_TO_NEW_LOC);

  int middleDistance = eyes->distanceTest();
  delay(200);

  //motors.forward();

  for (i = 0; i < 255; i++) {
    servo1.write(map(i, 0, 255, 0, 180));
    motors.adjustSpeed(i);

    //myStepper->step(1, FORWARD, INTERLEAVE);
    delay(3);
  }

  Log::println("1 Run: Fwd Slower");
  for (i = 255; i != 10; i--) {
    servo1.write(map(i, 0, 0, 255, 180));
    motors.adjustSpeed(i);

    //myStepper->step(1, BACKWARD, INTERLEAVE);
    delay(3);
  }

  Log::println("2 Run: Backward Faster");
  motors.backward();

  for (i = 0; i < 255; i++) {
    servo1.write(map(i, 0, 255, 0, 180));
    motors.adjustSpeed(i);

    //myStepper->step(1, FORWARD, DOUBLE);
    delay(3);
  }

  Serial.println("3 Run: Backward Slower");
  for (i = 255; i != 10; i--) {
    servo1.write(map(i, 0, 0, 255, 180));
    motors.adjustSpeed(i);

    //myStepper->step(1, BACKWARD, DOUBLE);
    delay(3);
  }

  //motors.square();
}
