#include "BlockPickupState.h"
#include <Arduino.h>
// #include "LineFollowState.h"
#include "BlindTurnState.h"
#include "StateMachine.h"
#include "../Sequencer.h"
#include "ReverseState.h"

BlockPickupState::BlockPickupState(){

}

void BlockPickupState::EnterState(StateMachine* parentMachine){
    Serial.println("Block Pickup State entered");Serial.flush();
    // Sequencer::SetNextTurnAngle(180);
}

void BlockPickupState::Update(StateMachine* parentMachine){
    // Serial.println("    Update called on Block Pickup State");Serial.flush();
    // BlockType type = BlockType::solid;

    // if (type == BlockType::solid){
    //     Sequencer::SetNextTurnAngle()    
    // }

    Sequencer::SetBlockType(BlockType::solid);
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

