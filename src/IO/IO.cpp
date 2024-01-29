#include "IO.h"
#include "../Globals.h"
#include <Arduino.h>


void IO::LEDs::IndicateFoamBlock(){
    Serial.println("libraries work!");
}

void IO::Motors::SetRelativeSpeeds(float linear, float angular){
    Serial.println("        motors speeds set to " + String(linear) + ", " + String(angular));
}

void IO::Motors::ForwardLeft(){
    Serial.println("        Forward Left");
    Serial.flush();
    IO::Motors::SetRelativeSpeeds(IO::Motors::lineFollowLinearSpeed, IO::Motors::lineFollowAngularSpeed);
}

void IO::Motors::Left(){
    Serial.println("        Left");
    Serial.flush();
    IO::Motors::SetRelativeSpeeds(0.0, IO::Motors::lineFollowAngularSpeed);
}

void IO::Motors::ForwardRight(){
    Serial.println("        Forward Right");
    Serial.flush();
    IO::Motors::SetRelativeSpeeds(IO::Motors::lineFollowLinearSpeed, -IO::Motors::lineFollowAngularSpeed);
}

void IO::Motors::Right(){
    Serial.println("        Right");
    Serial.flush();
    IO::Motors::SetRelativeSpeeds(0.0, -IO::Motors::lineFollowAngularSpeed);
}

void IO::Motors::Forward(){
    Serial.println("        Forward");
    Serial.flush();
    IO::Motors::SetRelativeSpeeds(IO::Motors::lineFollowLinearSpeed, 0.0);
}

void IO::Motors::Stop(){
    Serial.println("        Motors stopped");
    Serial.flush();
}

void IO::Motors::SetGripperServoAngle(float angle){

}

void IO::Motors::SetArmServoAngle(float angle){

}

void IO::Sensors::LineSense(bool& outerLeft, bool& outerRight, bool& innerLeft, bool& innerRight){
    // outerLeft = digitalRead(OUTER_LEFT_LINE_SENSOR_PIN);
    // outerRight = digitalRead(OUTER_RIGHT_LINE_SENSOR_PIN);
    // innerLeft = digitalRead(INNER_LEFT_LINE_SENSOR_PIN);
    // innerRight = digitalRead(INNER_RIGHT_LINE_SENSOR_PIN);
    outerLeft = (random(100) / 100.0) < 0.5;
    outerRight = (random(100) / 100.0) < 0.5;
    innerLeft = (random(100) / 100.0) < 0.5;
    innerRight = (random(100) / 100.0) < 0.5;
    return;
}

void IO::Sensors::GetBlockDistance(float& blockDistance){
    blockDistance = random(100);
}

bool IO::Sensors::PlatformSwitchPressed(){
    if (random(100) / 100.0 < 0.1){
        return true;
    }
    return false;
}
// bool IO::Sensors::LineSenseLeft(){
//     if (random(100) / 100.0 < 0.1){
//         return true;
//     }
//     return false;
// }

// bool IO::Sensors::LineSenseRight(){
//     return true;
// }