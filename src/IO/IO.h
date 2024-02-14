#pragma once
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <Servo.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
#include "DFRobot_VL53L0X.h"

// #define true false
// #define false true

#define OUTER_RIGHT_LINE_SENSOR_PIN (2)
#define INNER_RIGHT_LINE_SENSOR_PIN (3)
#define INNER_LEFT_LINE_SENSOR_PIN (4)
#define OUTER_LEFT_LINE_SENSOR_PIN (5)
#define GREEN_LED_PIN (6)
#define RED_LED_PIN (7)
#define BLUE_LED_PIN (8)
#define ARM_SERVO_PIN (9)
#define CRASH_SENSOR_PIN (10)
#define GRIPPER_SWITCH_PIN (11)
#define START_BUTTON_PIN (12)
namespace IO {
    namespace LEDs{
        void IndicateFoamBlock();
        void IndicateSolidBlock();
        void ToggleBlueLED();
    }

    class Motors
    {
        public:
            Adafruit_MotorShield AFMS;
            Adafruit_DCMotor *rightMotor;
            Adafruit_DCMotor *leftMotor;
            Adafruit_DCMotor *gripperMotor;
            Servo armServo;
            void Initialise();
            void SetRelativeSpeeds(float linear, float angular);
            void SetSpeeds(float left, float right);
            void ForwardLeft();
            void ForwardRight();
            void Left();
            void Right();
            void Forward();
            void Stop();
            void RaiseArm();
            void LowerArm();
            void GripperClose();
            void GripperOpen();
            void GripperStop();
            const float lineFollowLinearSpeed = 1.0;
            const float lineFollowAngularSpeed = 0.9;
            const int ArmServoTopAngle = 45;
            const int ArmServoBottomAngle = 75;
    };


    namespace Sensors{
        void LineSense(bool& outerLeft, bool& outerRight, bool& innerLeft, bool& innerRight);
        bool GripperSwitchPressed();
        bool PlatformSwitchPressed();
        bool StartSwitchPressed();
    }
}