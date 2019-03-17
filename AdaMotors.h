#include <Arduino.h>
#include <Servo.h>
#include <Adafruit_MotorShield.h>

//#include "CommonUtils.h"

#define LEFT_DIRECTION -1
#define RIGHT_DIRECTION 1
// FORWARD AND BACKWARD are abitrary, based on motor wiring
// reverse polarity of DC motors if you want the code to make more sense.
#define ADJUSTED_DC_BACKWARD FORWARD
#define ADJUSTED_DC_FORWARD BACKWARD
#define MOTOR_TURN_90_DEGREE_TIME_MS 1500

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
int motorTurnTimeMs;

// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61);

// Connect a stepper motor with 200 steps per revolution (1.8 degree)
// to motor port #2 (M3 and M4)
//Adafruit_StepperMotor *myStepper = AFMS.getStepper(200, 2);
// And connect a DC motor to port M1
//Adafruit_DCMotor *myLeftMotor = AFMS.getMotor(1);
//Adafruit_DCMotor *myRightMotor = AFMS.getMotor(2);

  // NanoMouseMotors motors;
  //   motors.square();
  //   motors.move(500, 500);
  //   motors.delay(1000);
  //   motors.move(0, 500);
  //   motors.delay(1700);
  //   motors.spiral();

class AdaMotors
{
  private:
    Adafruit_DCMotor* myLeftMotor;
    Adafruit_DCMotor* myRightMotor;
    int motorTurnTimeMs = MOTOR_TURN_90_DEGREE_TIME_MS;

  public:
    void attach(byte leftMotor = 1, byte rightMotor = 2) {
      Log::println("Initialize Motors...");
      // And connect a DC motor to port M1 & M2
      myLeftMotor = AFMS.getMotor(leftMotor);
      myRightMotor = AFMS.getMotor(rightMotor);
      //AFMS.begin();  // create with the default frequency 1.6KHz
      //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
      // turn on motor M1 and M2 (assuming args are 1 & 2 respectively)
      // TODO support additional motors, and document arguments
      AFMS.begin();
    }

    void die() {
        Log::println("Seize control!!!!");
        myLeftMotor->run(RELEASE);
        myRightMotor->run(RELEASE);
    }

    void stop() {
        Log::println("Brake!!!!");
        // myLeftMotor->run(BRAKE);
        // myRightMotor->run(BRAKE);
        myLeftMotor->run(RELEASE);
        myRightMotor->run(RELEASE);
    }

    void adjustSpeed(byte speedInterval = 255) {
      //0-255 (full speed)
      // Adjust speed to both motors
      //Log::println("Adjusting speed...");
      myLeftMotor->setSpeed(speedInterval);
      myRightMotor->setSpeed(speedInterval);
    }

    void backward() {
        Log::println("Go Backward!");
        myLeftMotor->run(ADJUSTED_DC_BACKWARD);
        myRightMotor->run(ADJUSTED_DC_BACKWARD);
    }

    void forward() {
        Log::println("Go Forward!");
        myLeftMotor->run(ADJUSTED_DC_FORWARD);
        myRightMotor->run(ADJUSTED_DC_FORWARD);
    }

    void turn(int direction, int degrees = 90) {
        if (direction == RIGHT_DIRECTION) {
           Log::println("Turn Right!");
           myLeftMotor->run(RELEASE);
           myRightMotor->run(ADJUSTED_DC_FORWARD);
         } else {
           Log::println("Turn Left!");
           myLeftMotor->run(ADJUSTED_DC_FORWARD);
           myRightMotor->run(RELEASE);
         }
      //   delay(1500);
      // Do we need this, if we have delays elsewhere?
      // TODO Do we need to DRY up the *byDegrees functions and just have the calcs here?
      // if (direction == RIGHT_DIRECTION) {
      //   delay(degrees * 4.9);
      // } else {
      //   delay(degrees * 5.9);
      // }
    }

    void right() {
        turn(RIGHT_DIRECTION);
        delay(motorTurnTimeMs);
    }

    void left() {
        turn(LEFT_DIRECTION);
        delay(motorTurnTimeMs);
    }

    void turnLeftByDegrees(double angleInDegrees = 90.0) const {
        //left();
        turn(LEFT_DIRECTION);
        delay(motorTurnTimeMs * angleInDegrees / 90.0);
    }

    void turnRightByDegrees(double angleInDegrees = 90.0) const {
        //right();
        turn(RIGHT_DIRECTION);
        delay(motorTurnTimeMs * angleInDegrees / 90.0);
    }

    void forwardForPeriodOfTime(unsigned int durationMs) {
      forward();
      delay(durationMs);
      //stop();
    }

      void square() {
        Log::println("Starting Square...");

        for (int i = 0; i <= 4; i++) {
          Log::println("Square step: " + i);
          forwardForPeriodOfTime(1500);
          turnLeftByDegrees();
        }
        Log::println("Completed Square...");
      }
//
//    void spiral() {
//      Log::println("Starting Spiral...");
//      for (int i = 0; i <= 6; i++) {
//        Log::println("Spiral step: " + i);
//        move(100 + (i * +10), 500 * (i + 1));
//        delay(500 * i + 1);
//        //   move(0, 250*i);
//        //   delay(1700);
//      }
//      Log::println("Completed spiral...");
//    }

//    void forwardProportionalControl(int pathDeviationErrorTerm) {
//      // Proportional Control. Will account for any wandering of the robot off a straight course,
//      // due to servo calibration, terrain differences, etc. It will adjust the power of the individual servos,
//      // to account for any directional error, and over/under-power at different levels in order to
//      // enable them drive a straight course, by turning back on course until the error rate is zero again.
//      // NOTE: In order for this to work, the motors CANNOT start at 100% power, because you can never add more.
//      // https://www.youtube.com/watch?v=yRb_37vzOd0&feature=youtu.be
//      // error = sensors.right = sensors.left
//      // leftServoPower = 50% + error
//      // rightServoPower = 50% - error
//      // NOTE: My sensors are not parallax (as used in video), so need to add the error term instead of subtract
//
//      const float Kp = 2.0; // Constant to amplify the turn rate (higher the number, higher the overcorrection)
//      leftServo.writeMicroseconds(1500 - SERVO_POWER_LEVEL + Kp*pathDeviationErrorTerm);
//      rightServo.writeMicroseconds(1500 + SERVO_POWER_LEVEL + Kp*pathDeviationErrorTerm);
//    }

};
