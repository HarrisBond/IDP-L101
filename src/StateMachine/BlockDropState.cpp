#include "BlockDropState.h"


BlockDropState::BlockDropState(){

}

void BlockDropState::EnterState(StateMachine* parentMachine){
    Serial.println("Enter State called on Block Drop State");Serial.flush();
    //short reverse
    motorController->SetRelativeSpeeds(-1.0, 0);
    delay(300);
    motorController->Stop();
    //raise
    motorController->RaiseArm();
    //forward until block over platform
    motorController->SetRelativeSpeeds(1.0, 0);
    delay(1200);
    motorController->Stop();
    //lower and release
    motorController->LowerArm();
    motorController->GripperOpen();
    delay(1000);
    motorController->SetRelativeSpeeds(-1.0, 0.0);
    delay(500);
    motorController->Stop();
    motorController->GripperClose();
    delay(1000);

    //the following code executes a "double tap": closes the gripper and pushes the block forward to ensure it is on the platform
    //it should work but is untested and was removed for the final competition

    // motorController->RaiseArm();
    // //forward for tap
    // motorController->SetRelativeSpeeds(1.0, 0.0);
    // delay(700);
    // //reverse from tap
    // motorController->SetRelativeSpeeds(-1.0, 0.0);
    // delay(700);
    // motorController->Stop();
    // motorController->LowerArm();

    
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
