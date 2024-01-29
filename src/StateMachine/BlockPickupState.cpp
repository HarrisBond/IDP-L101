#include "BlockPickupState.h"
#include <Arduino.h>
#include "LineFollowState.h"
#include "StateMachine.h"

BlockPickupState::BlockPickupState(){

}

void BlockPickupState::EnterState(StateMachine* parentMachine){
    Serial.println("Block Pickup State entered");Serial.flush();
}

void BlockPickupState::Update(StateMachine* parentMachine){
    Serial.println("    Update called on Block Pickup State");Serial.flush();
    parentMachine->ChangeState(LineFollowState::GetInstance());
}

void BlockPickupState::ExitState(StateMachine* parentMachine){
    Serial.println("Block Pickup State exited");Serial.flush();
}

State& BlockPickupState::GetInstance(){
    static BlockPickupState singleton;//this line seems to break everything :(
    return singleton;
}

