#include "BlindForwardState.h"
// #include "../Sequencer.h"
#include "StateMachine.h"
#include <Arduino.h>
// #include "../IO/IO.h";
#include "../Globals.h"

BlindForwardState::BlindForwardState(){
    forwardTimerMilliseconds = 0.0;
}

void BlindForwardState::EnterState(StateMachine* parentMachine){
    Serial.println("Blind Forward State Entered");Serial.flush();
    forwardTimerMilliseconds = forwardTime;
    motorController->SetRelativeSpeeds(1.0, 0.0);
}

void BlindForwardState::Update(StateMachine* parentMachine){
    // Serial.println("    Update called on Block Drop State");Serial.flush();
    forwardTimerMilliseconds -= time->GetDeltaTime();
    if (forwardTimerMilliseconds <= 0.0){
        motorController->Stop();
        parentMachine->ChangeState(LineFollowState::GetInstance());
    }
}

void BlindForwardState::ExitState(StateMachine* parentMachine){

}

State& BlindForwardState::GetInstance(){
    static BlindForwardState singleton;
    return singleton;
}
