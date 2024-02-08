#include "IO.h"



void IO::LEDs::IndicateFoamBlock(){
}

void IO::Motors::Initialise(){
    AFMS = Adafruit_MotorShield();
    leftMotor = AFMS.getMotor(1);
    rightMotor = AFMS.getMotor(2);

    if (!AFMS.begin()) {         // create with the default frequency 1.6KHz
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
    SetRelativeSpeeds(lineFollowLinearSpeed*0.5, lineFollowAngularSpeed*0.3);
}

void IO::Motors::Left(){
    SetRelativeSpeeds(lineFollowLinearSpeed * 0.3, lineFollowAngularSpeed);
}

void IO::Motors::ForwardRight(){
    SetRelativeSpeeds(lineFollowLinearSpeed*0.5, -lineFollowAngularSpeed*0.3);
}

void IO::Motors::Right(){
    SetRelativeSpeeds(lineFollowLinearSpeed * 0.3, -lineFollowAngularSpeed);
}

void IO::Motors::Forward(){
    SetRelativeSpeeds(lineFollowLinearSpeed, 0.0);
}

void IO::Motors::Stop(){
    SetRelativeSpeeds(0.0,0.0);
    leftMotor->run(RELEASE);
    rightMotor->run(RELEASE);
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
    return;
}

void IO::Sensors::GetBlockDistance(float& blockDistance){
    blockDistance = random(100);
}

bool IO::Sensors::PlatformSwitchPressed(){
    if (random(100) / 100.0 < 0.00002){
        return true;
    }
    return false;
}
