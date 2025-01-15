#include "ApplicationController.h"
#include "RobotControler.h"
#include "ChessController.h"
ApplicationController::ApplicationController()
{
    m_frameWidth = 128;
    m_frameHeight = 64;
    m_robot = new RobotControler(this);
    m_chess = new ChessController(this);
}

ApplicationController::~ApplicationController() {

}

void ApplicationController::loop() {
    this->checkInput();
    switch(m_machineState) {
    case MACHINE_INITIALIZE_ROBOT:{
        m_robot->setRobotState(ROBOT_RETURN_HOME);
        m_robot->loop();
        break;
    }
    case MACHINE_CHECK_PIECE:{
        m_chess->checkPiece();
        break;
    }
    case MACHINE_WAIT_OPPONENT_MOVE:{
        m_chess->waitOpponentMove();
        break;
    }
    case MACHINE_CALCULATE_NEXT_MOVE:{
        m_chess->calculateNextMove();
        break;
    }
    case MACHINE_MOVE_PIECE:{
        m_robot->moveHost(m_chess->nextMove());
        setMachineState(MACHINE_MOVE_PIECE_EXECUTE);
        break;
    }
    case MACHINE_MOVE_PIECE_EXECUTE:{
        m_robot->setRobotState(ROBOT_MOVE_PIECE);
        m_robot->loop();
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
ChessController* ApplicationController::chessController() {
    return m_chess;
}
int ApplicationController::motorPosition(MOTOR motorID) {
    return m_robot->motorPosition(motorID);
}
void ApplicationController::setMachineState(MACHINE_STATE machineState) {
    if(m_machineState == machineState) return;
    m_machineState = machineState;
    switch (m_machineState) {
    case MACHINE_INITIALIZE_ROBOT:{
        printf("[MC]MACHINE_INITIALIZE_ROBOT\r\n");
        break;
    }
    case MACHINE_CHECK_PIECE:{
        printf("[MC]MACHINE_CHECK_PIECE\r\n");
        break;
    }
    case MACHINE_WAIT_OPPONENT_MOVE:{
        printf("[MC]MACHINE_WAIT_OPPONENT_MOVE\r\n");
        break;
    }
    case MACHINE_CALCULATE_NEXT_MOVE:{
        printf("[MC]MACHINE_CALCULATE_NEXT_MOVE\r\n");
        break;
    }case MACHINE_ATTACK_OPPONENT_PIECE:{
        printf("[MC]MACHINE_ATTACK_OPPONENT_PIECE\r\n");
        break;
    }
    case MACHINE_MOVE_PIECE:{
        printf("[MC]MACHINE_MOVE_PIECE\r\n");
        break;
    }
    case MACHINE_MOVE_PIECE_EXECUTE:{
        printf("[MC]MACHINE_MOVE_PIECE_EXECUTE\r\n");
        break;
    }
    case MACHINE_RETURN_HOME:{
        printf("[MC]MACHINE_RETURN_HOME\r\n");
        break;
    }

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
