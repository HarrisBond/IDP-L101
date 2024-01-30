#pragma once
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

namespace IO {
    namespace LEDs{
        void IndicateFoamBlock();
        void IndicateSolidBlock();
    }

    class Motors
    {
        public:
            Adafruit_MotorShield AFMS;
            Adafruit_DCMotor *rightMotor;
            Adafruit_DCMotor *leftMotor;
            Motors();
            void Initialise();
            void SetRelativeSpeeds(float linear, float angular);
            void ForwardLeft();
            void ForwardRight();
            void Left();
            void Right();
            void Forward();
            void Stop();
            void SetGripperServoAngle(float angle);
            void SetArmServoAngle(float angle);
            
            const float lineFollowLinearSpeed = 1.0;
            const float lineFollowAngularSpeed = 0.9;
    };


    namespace Sensors{
        //returns 0 when detecting black, 1 when detecting white
        // bool LineSenseLeft();
        // bool LineSenseRight();
        void LineSense(bool& outerLeft, bool& outerRight, bool& innerLeft, bool& innerRight);

        //get distance to block in mm. This can either use the ultrasount or TOF module.
        //maybe we could measure roughness by slowly rotating the robot while collecting TOF data to differentiate between solid and foam blocks?
        void GetBlockDistance(float& blockDistance);

        bool PlatformSwitchPressed();

    }
}