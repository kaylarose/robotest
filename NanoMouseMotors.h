#include <Arduino.h>
#include <Servo.h>

//#include "CommonUtils.h"

#define LEFT_DIRECTION -1
#define RIGHT_DIRECTION 1
#define KAYLAS_SERVO_AND_RIGHT_SERVO_ARE_BORKED 0 

  // NanoMouseMotors motors;
  //   motors.square();
  //   motors.move(500, 500);
  //   motors.delay(1000);
  //   motors.move(0, 500);
  //   motors.delay(1700);
  //   motors.spiral();
  
class NanoMouseMotors
{
  private:
    Servo leftServo;
    Servo rightServo;

    static const byte  SERVO_POWER_LEVEL = 250; // 500 is max See https://mbbackus.bitbucket.io/ "movement"section comments

  public:
    void attach(byte leftMotor, byte rightMotor) {
      // Setup Code for Servos. Tells programs which pins the motors are attached to.
      leftServo.attach(leftMotor);
      rightServo.attach(rightMotor);
    }

    void stop() {
      // Sends "Stop" Pulse in 1500 Microseconds
      leftServo.writeMicroseconds(1500);
      rightServo.writeMicroseconds(1500);
    }

    void forward() {
      leftServo.writeMicroseconds(1500 - SERVO_POWER_LEVEL);
      // Inverse power because the servo motor is a different orientation
      // Protip: seems to only apply to parallax motors. Kit motors are pre-calibrated
      // Max 1500...otherwise is reverse......????
      // unsigned int would Go up to max 65k secs (0k/+~65k)
      // signed int would Go up to max 32 (32 bit int) seconds (-32k/+32k)
      // https://www.youtube.com/watch?v=dke4o7A2Y44&feature=youtu.be
      rightServo.writeMicroseconds(1500 + SERVO_POWER_LEVEL);
      // TODO This sounds wrong Kayla but it's working that way. Double check.
      // rightServo.writeMicroseconds(1500+SERVO_POWER_LEVEL);
    }

    void forwardTime(unsigned int time) {
      forward();
      delay(time);
      stop();
    }


    void turn(int direction, int degrees) {
      // Because we are using an normal int here, the value is max 32 sec (-32k/+32k),
      // so if we give multiplier directional args (-1/1) the bot should know hich way to turn.
      leftServo.writeMicroseconds(1500 + SERVO_POWER_LEVEL * direction);
      rightServo.writeMicroseconds(1500 + SERVO_POWER_LEVEL * direction);
      // TODO Kayla: Refactor this bot https://www.youtube.com/watch?v=5R59dDwAeco
      if (direction == RIGHT_DIRECTION) {
        delay(degrees * 4.9);
      } else {
        delay(degrees * 5.9);
      }
      stop();
    }



    void move(int leftMotor, int rightMotor) {
      // Because we are using an normal int here, the value is max 32 sec (-32k/+32k),
      // so if we give multiplier directional args (-1/1) the bot should know hich way to turn.
      leftServo.writeMicroseconds(1500 - leftMotor);
      rightServo.writeMicroseconds(1500 + rightMotor);
    }

    void square() {
      //DPRINTLN("Starting Square...");
      for (int i = 0; i <= 4; i++) {
        //DPRINTLN("Square step: " + i);
        forwardTime(1500);
        turn(LEFT_DIRECTION, 90);
        delay(200);
      }
      //DPRINTLN("Completed Square...");
    }

    void spiral() {
      //#DPRINTLN("Starting Spiral...");
      for (int i = 0; i <= 6; i++) {
        //DPRINTLN("Spiral step: " + i);
        move(100 + (i * +10), 500 * (i + 1));
        delay(500 * i + 1);
        //   move(0, 250*i);
        //   delay(1700);
      }
      //DPRINTLN("Completed spiralare...");
    }

    void forwardProportionalControl(int pathDeviationErrorTerm) {
      // Proportional Control. Will account for any wandering of the robot off a straight course,
      // due to servo calibration, terrain differences, etc. It will adjust the power of the individual servos,
      // to account for any directional error, and over/under-power at different levels in order to 
      // enable them drive a straight course, by turning back on course until the error rate is zero again.
      // NOTE: In order for this to work, the motors CANNOT start at 100% power, because you can never add more.
      // https://www.youtube.com/watch?v=yRb_37vzOd0&feature=youtu.be 
      // error = sensors.right = sensors.left
      // leftServoPower = 50% + error
      // rightServoPower = 50% - error
      // NOTE: My sensors are not parallax (as used in video), so need to add the error term instead of subtract

      const float Kp = 2.0; // Constant to amplify the turn rate (higher the number, higher the overcorrection)
      leftServo.writeMicroseconds(1500 - SERVO_POWER_LEVEL + Kp*pathDeviationErrorTerm);
      rightServo.writeMicroseconds(1500 + SERVO_POWER_LEVEL + Kp*pathDeviationErrorTerm);
    }

};

