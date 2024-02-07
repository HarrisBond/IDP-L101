#include "IO.h"
#include "../Globals.h"
#include <Arduino.h>



void IO::LEDs::IndicateFoamBlock(){
    // green
    digitalWrite(GREEN_LED_PIN, HIGH);
    delay(5000);
    digitalWrite(GREEN_LED_PIN, LOW);
}

void IO::LEDs::IndicateSolidBlock() {
    // red
    digitalWrite(RED_LED_PIN, HIGH);
    delay(5000);
    digitalWrite(RED_LED_PIN, LOW);
}

void IO::LEDs::TurnOffAll() {
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, LOW);
}

// void IO::Motors::SetRelativeSpeeds(float linear, float angular){
//     Serial.println("        motors speeds set to " + String(linear) + ", " + String(angular));
// }

void IO::Motors::Initialise(){
    AFMS = Adafruit_MotorShield();
    leftMotor = AFMS.getMotor(1);
    rightMotor = AFMS.getMotor(2);

    if (!AFMS.begin()) {         // create with the default frequency 1.6KHz
    // if (!AFMS.begin(1000)) {  // OR with a different frequency, say 1KHz
        Serial.println("Could not find Motor Shield. Check wiring.");
        while (1);
    }
    Serial.println("Motor Shield found.");
}

void IO::Motors::SetRelativeSpeeds(float linear, float angular){
    // Serial.println("motors speeds set to " + String(linear) + ", " + String(angular) + "\n");
    float left = linear - angular;
    float right = linear + angular;
    leftMotor->setSpeed(int(constrain(abs(left * 255), 0, 255)));
    rightMotor->setSpeed(int(constrain(abs(right * 255), 0, 255)));
    if (left < 0.0){
        leftMotor->run(BACKWARD);
    } else {
        leftMotor->run(FORWARD);
    }

    if (right < 0.0){
        rightMotor->run(BACKWARD);
    } else {
        rightMotor->run(FORWARD);
    }
}

void IO::Motors::ForwardLeft(){
    // Serial.println("        Forward Left");Serial.flush();
    SetRelativeSpeeds(lineFollowLinearSpeed*0.8, lineFollowAngularSpeed);
}

void IO::Motors::Left(){
    // Serial.println("        Left");Serial.flush();
    SetRelativeSpeeds(lineFollowLinearSpeed * 0.3, lineFollowAngularSpeed);
}

void IO::Motors::ForwardRight(){
    // Serial.println("        Forward Right");Serial.flush();
    SetRelativeSpeeds(lineFollowLinearSpeed*0.8, -lineFollowAngularSpeed);
}

void IO::Motors::Right(){
    // Serial.println("        Right");Serial.flush();
    SetRelativeSpeeds(lineFollowLinearSpeed * 0.3, -lineFollowAngularSpeed);
}

void IO::Motors::Forward(){
    // Serial.println("        Forward");Serial.flush();
    SetRelativeSpeeds(lineFollowLinearSpeed, 0.0);
}

void IO::Motors::Stop(){
    // Serial.println("        Motors stopped");Serial.flush();
}

void IO::Motors::SetGripperServoAngle(float angle){

}

void IO::Motors::SetArmServoAngle(float angle){

}

void IO::Sensors::LineSense(bool& outerLeft, bool& outerRight, bool& innerLeft, bool& innerRight){
    outerLeft = digitalRead(OUTER_LEFT_LINE_SENSOR_PIN);
    outerRight = digitalRead(OUTER_RIGHT_LINE_SENSOR_PIN);
    innerLeft = digitalRead(INNER_LEFT_LINE_SENSOR_PIN);
    innerRight = digitalRead(INNER_RIGHT_LINE_SENSOR_PIN);
    // outerLeft = (random(100) / 100.0) < 0.5;
    // outerRight = (random(100) / 100.0) < 0.5;
    // innerLeft = (random(100) / 100.0) < 0.5;
    // innerRight = (random(100) / 100.0) < 0.5;
    return;
}

void IO::TimeFlightSensor::Initialise() {
    Wire.begin();
    timeFlightSensor.begin(0x50);
    //Set to Back-to-back mode and high precision mode
    timeFlightSensor.setMode(timeFlightSensor.eContinuous, timeFlightSensor.eHigh);
    //Laser rangefinder begins to work
    timeFlightSensor.start();
}


void IO::TimeFlightSensor::GetBlockDistance(float& blockDistance){
    blockDistance = timeFlightSensor.getDistance();
}

bool IO::Sensors::PlatformSwitchPressed(){
    if (random(100) / 100.0 < 0.001){
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