#include "BlockPickupState.h"
#include <Arduino.h>
// #include "LineFollowState.h"
#include "BlindTurnState.h"
#include "StateMachine.h"
#include "../Sequencer.h"
#include "ReverseState.h"
#include "../IO/IO.h"

#define MAX_RANG (520)
#define ADC_SOLUTION (1023.0)

float BlockPickupState::UltraRead(float dist_t, BlockType& currentBlockType) {
    float sensity_t = analogRead(ULTRA_SENSOR_PIN);
    float new_dist_t = sensity_t * MAX_RANG / ADC_SOLUTION;
    if (new_dist_t > 500 || new_dist_t < 7) {
            touching = true;
            if (new_dist_t > 500) {
                currentBlockType = BlockType::solid;
                Serial.println("solid touching!");
            } else {
                currentBlockType = BlockType::foam;
                currentTime = millis();
                Serial.println("foam touching!");
            }
            //Serial.println("last dist: " + String(dist_t) + " this dist: " + String(new_dist_t));
    }
    return new_dist_t;
}

void BlockPickupState::TouchStateDetect(float *dist_t, BlockType& currentBlockType) {
    Serial.println("block kind: " + String(currentBlockType));
    float sensity_t = analogRead(ULTRA_SENSOR_PIN);
    // turn the ledPin on
    *dist_t = sensity_t * MAX_RANG / ADC_SOLUTION;
    if (currentBlockType == BlockType::solid) {
            if (*dist_t > 500) touchingCount++;
            else touchingCount--;
            // Serial.println("touching dist: " + String(*dist_t));
            if (touchingCount > 50) {
                touched = true;
                Serial.println("solid touched!");
                grabberMotor->setSpeed(0);
                grabberMotor->run(RELEASE);
            }
        else if (touchingCount < 0) {
            touching = false;
            touchingCount = 0;
            currentBlockType = BlockType::empty;
        }
    } 
    else if (currentBlockType == BlockType::foam) {
            Serial.println("Time: " + String(millis() - currentTime));
            if (*dist_t > 30) {
                touching = false;
                currentTime = 0;
                currentBlockType = BlockType::empty;
            }
            else if (millis() - currentTime > 1000) {
                touched = true;
                Serial.println("foam touched!");
                grabberMotor->setSpeed(0);
                grabberMotor->run(RELEASE);
            }
    }
}

void BlockPickupState::BlockPick() {
    float dist_t;
    if (analogRead(ULTRA_SENSOR_PIN) * MAX_RANG / ADC_SOLUTION < 500) {
        for (int i = 0; i < 10; i++) {
            grabberMotor->setSpeed(255);
            grabberMotor->run(FORWARD);
            delay(50);
        }
    }
    while (!touched) {
        grabberMotor->setSpeed(255);
        grabberMotor->run(FORWARD);
        delay(100);
        if (!touching) dist_t = UltraRead(dist_t, currentBlockType);
        else TouchStateDetect(&dist_t, currentBlockType);
    }

    // lift
    lifter.write(LIFT_ANGLE);
}

void BlockPickupState::PickingLED() {
    // !!! Will stay here for 5 secs !!!
    switch(currentBlockType) {
        case BlockType::solid:
            IO::LEDs::IndicateSolidBlock();
            break;
        case BlockType::foam:
            IO::LEDs::IndicateFoamBlock();
            break;
        default:
            break;
    }
}

BlockPickupState::BlockPickupState(){
    Adafruit_MotorShield AFMS;
    AFMS = Adafruit_MotorShield();
    grabberMotor = AFMS.getMotor(3);
    lifter.attach(9);
    IO::LEDs::TurnOffAll();
}

void BlockPickupState::EnterState(StateMachine* parentMachine){
    Serial.println("Block Pickup State entered");Serial.flush();
    touching = false;
    touched = false;
    currentBlockType = BlockType::empty;
    // pick and lift
    BlockPick();
    PickingLED();
    // Sequencer::SetNextTurnAngle(180);
}

void BlockPickupState::Update(StateMachine* parentMachine){
    // Serial.println("    Update called on Block Pickup State");Serial.flush();
    // BlockType type = BlockType::solid;

    // if (type == BlockType::solid){
    //     Sequencer::SetNextTurnAngle()    
    // }
    Sequencer::SetBlockType(currentBlockType);
    // parentMachine->ChangeState(LineFollowState::GetInstance());
    parentMachine->ChangeState(ReverseState::GetInstance());
}

void BlockPickupState::ExitState(StateMachine* parentMachine){
    // Serial.println("Block Pickup State exited");Serial.flush();
}

State& BlockPickupState::GetInstance(){
    static BlockPickupState singleton;//this line seems to break everything :(
    return singleton;
}

