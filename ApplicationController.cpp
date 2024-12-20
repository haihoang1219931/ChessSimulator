#include "ApplicationController.h"
ApplicationController::ApplicationController()
{
    m_frameWidth = 128;
    m_frameHeight = 64;
}

ApplicationController::~ApplicationController() {

}

void ApplicationController::loop() {
    switch(m_machineState) {
    case MACHINE_INITIALIZE_ROBOT:{
        break;
    }
    case MACHINE_CHECK_PIECE:{
        break;
    }
    case MACHINE_WAIT_OPPONENT_MOVE:{
        break;
    }
    case MACHINE_CALCULATE_NEXT_MOVE:{
        break;
    }
    case MACHINE_ATTACK_OPPONENT_PIECE:{
        break;
    }
    case MACHINE_MOVE_PIECE:{
        break;
    }
    case MACHINE_RETURN_HOME:{
        break;
    }
    }
}

MACHINE_STATE ApplicationController::stateMachine() {
    return m_machineState;
}

void ApplicationController::setMachineState(MACHINE_STATE machineState) {
    if(machineState != m_machineState) {
        m_machineState = machineState;
    }
}

int ApplicationController::getScreenWidth() {
    return m_frameWidth;
}

int ApplicationController::getScreenHeight() {
    return m_frameHeight;
}
unsigned char* ApplicationController::getScreenData() {
    return m_frameData;
}
