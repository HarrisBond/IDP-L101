#pragma once

namespace IO {
    namespace LEDs{
        void IndicateFoamBlock();
        void IndicateSolidBlock();
    }

    namespace Motors{
        //linear speed, +ve is forwards, -ve is backwards. should be in range -1 to 1
        //angular speed, +ve is anticlockwise, -ve is clockwise (for right hand rule angular velocity reasons)
        //set left and right motor speeds to a sum of common mode (for linear) and difference mode (for turning).
        void SetRelativeSpeeds(float linear, float angular);
        void ForwardLeft();
        void ForwardRight();
        void Forward();

        //should just call SetRelativeSpeeds(0,0)
        void Stop();

        //these should both include limits so you can't accidentally tell the robot to break itself
        void SetGripperServoAngle(float angle);
        void SetArmServoAngle(float angle);
        const float lineFollowLinearSpeed = 0.5;
        const float lineFollowAngularSpeed = 0.5;
    }

    namespace Sensors{
        //returns 0 when detecting black, 1 when detecting white
        bool LineSenseLeft();
        bool LineSenseRight();

        //return distance to block in mm. This can either use the ultrasount or TOF module.
        //maybe we could measure roughness by slowly rotating the robot while collecting TOF data to differentiate between solid and foam blocks?
        float GetBlockDistance();
    }
}