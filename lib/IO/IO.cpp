#include "IO.h"
#include <Arduino.h>


void IO::LEDs::IndicateFoamBlock(){
    Serial.println("libraries work!");
    Serial.flush();
}

void IO::Motors::SetRelativeSpeeds(float linear, float angular){
    // Serial.print("motors speeds set to " + String(linear) + ", " + String(angular) + "\n");
}

void IO::Motors::ForwardLeft(){
    Serial.print("Forward Left");
    Serial.flush();
    IO::Motors::SetRelativeSpeeds(IO::Motors::lineFollowLinearSpeed, IO::Motors::lineFollowAngularSpeed);
}

void IO::Motors::ForwardRight(){
    Serial.print("Forward Right");
    Serial.flush();
    IO::Motors::SetRelativeSpeeds(IO::Motors::lineFollowLinearSpeed, -IO::Motors::lineFollowAngularSpeed);
}

void IO::Motors::Forward(){
    Serial.print("Forward");
    Serial.flush();
    IO::Motors::SetRelativeSpeeds(IO::Motors::lineFollowLinearSpeed, 0.0);
}

void IO::Motors::Stop(){
    Serial.print("motors stopped");
    Serial.flush();
}

void IO::Motors::SetGripperServoAngle(float angle){

}

void IO::Motors::SetArmServoAngle(float angle){

}



bool IO::Sensors::LineSenseLeft(){
    if (random(100) / 100.0 < 0.1){
        return true;
    }
    return false;
}

bool IO::Sensors::LineSenseRight(){
    return true;
}