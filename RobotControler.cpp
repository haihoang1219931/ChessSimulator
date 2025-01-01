#include "RobotControler.h"
#include "ApplicationController.h"
#define CHESS_ROW 8
#define CHESS_COL 8
RobotControler::RobotControler(ApplicationController* app)
{
    m_app = app;
    m_robotState = ROBOT_STATE::ROBOT_INIT_STATE;
}
void RobotControler::loop() {
    switch (m_robotState) {
    case ROBOT_STATE::ROBOT_RETURN_HOME: {
        returnHome();
        break;
    }
    case ROBOT_STATE::ROBOT_MOVE_PIECE: {
        moveToTargetPostion();
        break;
    }
    }
}
void RobotControler::setRobotState(ROBOT_STATE robotState) {
    if(m_robotState == robotState) return;
    m_robotState = robotState;
    switch (m_robotState) {
    case ROBOT_RETURN_HOME: {
        m_app->printf("[RB]  ROBOT_RETURN_HOME\r\n");
        break;
    }
    case ROBOT_MOVE_PIECE: {
        m_app->printf("[RB]  ROBOT_MOVE_PIECE\r\n");
        break;
    }
    }
}
void RobotControler::returnHome(){
    bool allMotorsAreHome = true;
    for(unsigned int axis=0; axis< (unsigned int)MOTOR::MOTOR_MAX; axis++) {
        if(!m_app->isAxisHome((MOTOR)axis)) {
            m_app->controlMotor((MOTOR)axis,MOTOR_DIR_INVERSE);
            allMotorsAreHome = false;
        }
    }
    if(allMotorsAreHome) m_app->setMachineState(MACHINE_CHECK_PIECE);
}
Motor* RobotControler::getMotor(MOTOR axis) {
    return &m_motorList[axis];
}
void RobotControler::moveHost(int currentRow, int currentCol, int targetRow, int targetCol) {
    m_app->printf("Move Host\r\n");
    m_moveSequence[0] = {MOVE_CODE_HAS_MOVE,false,{0,115,65,0}};
    m_moveSequence[1] = {MOVE_CODE_HAS_MOVE,false,{20,147,13,0}};
    m_moveSequence[2] = {MOVE_CODE_HAS_MOVE,false,{20,147,13,100}};
    m_moveSequence[3] = {MOVE_CODE_HAS_MOVE,false,{0,115,65,100}};
    m_moveSequence[4] = {MOVE_CODE_HAS_MOVE,false,{29,118,33,100}};
    m_moveSequence[5] = {MOVE_CODE_HAS_MOVE,false,{29,118,33,0}};
    m_moveSequence[6] = {MOVE_CODE_HAS_MOVE,false,{0,115,65,0}};
    m_moveSequence[7] = {MOVE_CODE_HAS_MOVE,false,{0,180,0,0}};
    m_numberMove = 8;
    m_currentMoveID = 0;
}

void RobotControler::captureGuest(int currentRow, int currentCol, int targetRow, int targetCol)
{
    m_app->printf("Capture Guest\r\n");
    m_moveSequence[0] = {MOVE_CODE_HAS_MOVE,false,{100,100,60,100}};
    m_moveSequence[1] = {MOVE_CODE_HAS_MOVE,false,{100,100,60,0}};
    m_moveSequence[2] = {MOVE_CODE_HAS_MOVE,false,{100,150,180,0}};
    m_moveSequence[3] = {MOVE_CODE_HAS_MOVE,false,{150,150,180,100}};
    m_moveSequence[5] = {MOVE_CODE_HAS_MOVE,false,{100,100,100,100}};
    m_moveSequence[6] = {MOVE_CODE_HAS_MOVE,false,{100,100,100,0}};
    m_moveSequence[7] = {MOVE_CODE_HAS_MOVE,false,{100,150,100,0}};
    m_moveSequence[8] = {MOVE_CODE_HAS_MOVE,false,{150,150,100,100}};
    m_moveSequence[9] = {MOVE_CODE_HAS_MOVE,false,{0,0,0,100}};
    m_numberMove = 10;
    m_currentMoveID = 0;
}
void RobotControler::moveToTargetPostion() {
    if(!m_moveSequence[m_currentMoveID].moveInit) {
        for(unsigned int axis=0; axis< (unsigned int)MOTOR::MOTOR_MAX; axis++) {
            m_motorList[axis].setTargetStep(m_moveSequence[m_currentMoveID].step[axis]);
            m_motorList[axis].setDirStep(m_moveSequence[m_currentMoveID].step[axis] > m_motorList[axis].currentStep() ?
                                                MOTOR_DIR_NORMAL:MOTOR_DIR_INVERSE);
        }
        m_moveSequence[m_currentMoveID].moveInit = true;
    }
    bool allMotorsAreHome = true;
    for(unsigned int axis=0; axis< (unsigned int)MOTOR::MOTOR_MAX; axis++) {
        if(!m_motorList[axis].isMoveDone()){
            allMotorsAreHome = false;
            m_app->controlMotor((MOTOR)axis,m_motorList[axis].dirStep());
        }
    }
    m_app->printf("MOVE[%d] X[%d] Y[%d] Z[%d] CAP[%d]\r\n",
                  m_currentMoveID,
                  m_motorList[MOTOR_X].currentStep(),
                  m_motorList[MOTOR_Y].currentStep(),
                  m_motorList[MOTOR_Z].currentStep(),
                  m_motorList[MOTOR_CAP].currentStep());
    if(allMotorsAreHome) m_currentMoveID++;
    if(m_currentMoveID >= m_numberMove) m_app->setMachineState(MACHINE_STATE::MACHINE_WAIT_OPPONENT_MOVE);
}
bool RobotControler::moveDone(MOTOR axis) {
    return m_motorList[axis].dirStep() >= 0 ? m_motorList[axis].currentStep() >= m_motorList[axis].targetStep():
                                  m_motorList[axis].currentStep() < m_motorList[axis].targetStep();
}
void RobotControler::capture() {
    m_motorList[MOTOR::MOTOR_CAP].setDirStep(MOTOR_DIR_INVERSE);
}
bool RobotControler::captureDone() {

}
void RobotControler::release() {
    m_motorList[MOTOR::MOTOR_CAP].setDirStep(MOTOR_DIR_NORMAL);
}
bool RobotControler::releaseDone() {

}
int RobotControler::motorPosition(MOTOR motorID) {
    return m_motorList[motorID].currentStep();
}
