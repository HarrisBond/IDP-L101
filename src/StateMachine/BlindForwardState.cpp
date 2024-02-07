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
    // forwardTimerMilliseconds = Sequencer::HasStarted() ? defaultForwardTime : startForwardTime;//should go forward for 2 seconds at the start
    if (!Sequencer::HasStarted()){
        forwardTimerMilliseconds = startForwardTime;
    } else if (Sequencer::IsFinishing()){
        forwardTimerMilliseconds = endForwardTime;
    } else {
        forwardTimerMilliseconds = defaultForwardTime;
    }
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
