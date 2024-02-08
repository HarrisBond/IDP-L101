#include "BlockDropState.h"


BlockDropState::BlockDropState(){

}

void BlockDropState::EnterState(StateMachine* parentMachine){
    Serial.println("Enter State called on Block Drop State");Serial.flush();
}

void BlockDropState::Update(StateMachine* parentMachine){
    Sequencer::SetBlockType(BlockType::empty);
    parentMachine->ChangeState(ReverseState::GetInstance());return;
}

void BlockDropState::ExitState(StateMachine* parentMachine){

}

State& BlockDropState::GetInstance(){
    static BlockDropState singleton;
    return singleton;
}
