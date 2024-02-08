#include "BlockPickupState.h"
#include <Arduino.h>
#include "BlindTurnState.h"
#include "StateMachine.h"
#include "../Sequencer.h"
#include "ReverseState.h"

BlockPickupState::BlockPickupState(){

}

void BlockPickupState::EnterState(StateMachine* parentMachine){
    Serial.println("Block Pickup State entered");Serial.flush();
}

void BlockPickupState::Update(StateMachine* parentMachine){
    Sequencer::SetBlockType(BlockType::solid);
    parentMachine->ChangeState(ReverseState::GetInstance());return;
}

void BlockPickupState::ExitState(StateMachine* parentMachine){
}

State& BlockPickupState::GetInstance(){
    static BlockPickupState singleton;
    return singleton;
}

