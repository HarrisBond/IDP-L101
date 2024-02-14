#include "IndustrialAState.h"


IndustrialAState::IndustrialAState(){
    
}

void IndustrialAState::EnterState(StateMachine* parentMachine){
    Serial.println("Industrial A state entered");
    state = industrialState::firstForward;
    timer = firstForwardTime;
}

void IndustrialAState::Update(StateMachine* parentMachine){
    timer -= time->GetDeltaTime();
    switch (state){
        case (industrialState::firstForward) : UpdateFirstForward(); break;
        case (industrialState::secondForward) : UpdateSecondForward(parentMachine); break;
    }
}

void IndustrialAState::UpdateFirstForward(){
    LineFollow();
    if (timer <= 0){
        timer = secondForwardTime;
        state = industrialState::secondForward;
    }
}

void IndustrialAState::UpdateSecondForward(StateMachine* parentMachine){
    if (timer <= 0){
        parentMachine->ChangeState(BlockPickupState::GetInstance());
    }
}

void IndustrialAState::LineFollow(){
    bool outerLeft, outerRight, innerLeft, innerRight;
    IO::Sensors::LineSense(outerLeft, outerRight, innerLeft, innerRight);
    
    if (outerLeft && !outerRight){
        motorController->Left();//anticlockwise
    } else if (!outerLeft && outerRight){
        motorController->Right();//clockwise
    } else if (outerLeft && outerRight){
        motorController->Forward();
    } else {
        if (innerLeft && !innerRight){
            motorController->ForwardLeft();//anticlockwise
        } else if (!innerLeft && innerRight){
            motorController->ForwardRight();//clockwise
        } else if (innerLeft && innerRight){
            motorController->Forward();
        } else {
            motorController->Forward();
        }
    }
}

void IndustrialAState::ExitState(StateMachine* parentMachine){
    
}

State& IndustrialAState::GetInstance(){
    static IndustrialAState singleton;
    return singleton;
}
