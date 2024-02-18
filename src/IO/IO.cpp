#include "IO.h"


void IO::LEDs::ToggleBlueLED(){
    static bool blueLEDState;
    digitalWrite(BLUE_LED_PIN, blueLEDState);
    blueLEDState = !blueLEDState;
}

void IO::Motors::Initialise(){
    AFMS = Adafruit_MotorShield();
    leftMotor = AFMS.getMotor(1);
    rightMotor = AFMS.getMotor(2);
    gripperMotor = AFMS.getMotor(3);
    armServo.attach(ARM_SERVO_PIN);
    Serial.println(String(armServo.read()));

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

void IO::Motors::SetSpeeds(float left, float right){
    leftMotor->setSpeed(int(abs(left * 255)));
    rightMotor->setSpeed(int(abs(right * 255)));
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
    SetSpeeds(0.3, 1.0);
}

void IO::Motors::Left(){
    SetSpeeds(-0.6, 1.0);
}

void IO::Motors::ForwardRight(){
    SetSpeeds(1.0, 0.3);
}

void IO::Motors::Right(){
    SetSpeeds(1.0, -0.6);
}

void IO::Motors::Forward(){
    SetRelativeSpeeds(lineFollowLinearSpeed, 0.0);
}

void IO::Motors::Stop(){
    SetRelativeSpeeds(0.0,0.0);
    leftMotor->run(RELEASE);
    rightMotor->run(RELEASE);
}

void IO::Motors::RaiseArm(){
    Serial.println("raising arm");
    for (int pos = ArmServoBottomAngle; pos > ArmServoTopAngle; pos --){
        armServo.write(pos);
        delay(15);
    }
}

void IO::Motors::LowerArm(){
    Serial.println("lowering arm");
  for (int pos = ArmServoTopAngle; pos < ArmServoBottomAngle; pos ++){
    armServo.write(pos);
    delay(15);
  }
}

void IO::Motors::GripperClose(){
    gripperMotor->setSpeed(255);
    gripperMotor->run(FORWARD);
}

void IO::Motors::GripperOpen(){
    gripperMotor->setSpeed(255);
    gripperMotor->run(BACKWARD);
}

void IO::Motors::GripperStop(){
    gripperMotor->setSpeed(0);
    gripperMotor->run(RELEASE);
}

void IO::Sensors::LineSense(bool& outerLeft, bool& outerRight, bool& innerLeft, bool& innerRight){
    outerLeft = digitalRead(OUTER_LEFT_LINE_SENSOR_PIN);
    outerRight = digitalRead(OUTER_RIGHT_LINE_SENSOR_PIN);
    innerLeft = digitalRead(INNER_LEFT_LINE_SENSOR_PIN);
    innerRight = digitalRead(INNER_RIGHT_LINE_SENSOR_PIN);
    return;
}

bool IO::Sensors::GripperSwitchPressed(){
    return digitalRead(GRIPPER_SWITCH_PIN);
}

bool IO::Sensors::PlatformSwitchPressed(){
    bool pressed = !digitalRead(CRASH_SENSOR_PIN);
    Serial.println(pressed);
    return pressed;
}

bool IO::Sensors::StartSwitchPressed(){
    return digitalRead(START_BUTTON_PIN);
}
