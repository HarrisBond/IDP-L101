#include "BlockDropState.h"
#include "../Sequencer.h"
#include "StateMachine.h"
#include "BlindTurnState.h"
#include "ReverseState.h"
#include <Arduino.h>

BlockDropState::BlockDropState(){

}

void BlockDropState::EnterState(StateMachine* parentMachine){
    Serial.println("Enter State called on Block Drop State");Serial.flush();
}

void BlockDropState::Update(StateMachine* parentMachine){
    // Serial.println("    Update called on Block Drop State");Serial.flush();
    Sequencer::SetBlockType(BlockType::empty);
    // parentMachine->ChangeState(LineFollowState::GetInstance());
    parentMachine->ChangeState(ReverseState::GetInstance());
}

void BlockDropState::ExitState(StateMachine* parentMachine){

}

State& BlockDropState::GetInstance(){
    static BlockDropState singleton;
    return singleton;
}
