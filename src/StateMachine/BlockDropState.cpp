#include "BlockDropState.h"


BlockDropState::BlockDropState(){

}

void BlockDropState::EnterState(StateMachine* parentMachine){
    Serial.println("Enter State called on Block Drop State");Serial.flush();
    motorController->SetRelativeSpeeds(-0.5, 0);
    delay(400);
    motorController->Stop();
    motorController->RaiseArm();
    motorController->SetRelativeSpeeds(0.5, 0);
    delay(1300);
    motorController->Stop();
    motorController->LowerArm();
    motorController->GripperOpen();
    delay(1000);
    motorController->SetRelativeSpeeds(-1.0, 0.0);
    delay(500);
    motorController->GripperClose();
    Sequencer::SetBlockType(BlockType::empty);
    parentMachine->ChangeState(ReversePlatformState::GetInstance());return;
}

void BlockDropState::Update(StateMachine* parentMachine){
    
}

void BlockDropState::ExitState(StateMachine* parentMachine){

}

State& BlockDropState::GetInstance(){
    static BlockDropState singleton;
    return singleton;
}
