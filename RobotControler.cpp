#include "RobotControler.h"

#include "ApplicationController.h"
RobotControler::RobotControler(ApplicationController* app)
{
    m_app = app;
    m_robotState = ROBOT_STATE::ROBOT_WAIT_COMMAND;
    for(int i=0; i< MOTOR::MOTOR_MAX; i++) {
        m_targetStep[i] = 0;
        m_currentStep[i] = 0;
        m_dirStep[i] = 0;
    }
}
void RobotControler::loop() {
    switch (m_robotState) {
    case ROBOT_STATE::ROBOT_WAIT_COMMAND: {
        break;
    }
    case ROBOT_STATE::ROBOT_MOVE_HOST_GO_TO_CURRENT_POS: {
        moveToTargetPostion();
        break;
    }
    }
}
void RobotControler::setRobotState(ROBOT_STATE robotState) {
    m_robotState = robotState;
}
void RobotControler::returnHome(){
//    setTargetPosition(0.0f,0.0f,0.0f);
}
void RobotControler::moveHost(int currentRow, int currentCol, int targetRow, int targetCol) {
    m_targetStep[MOTOR::MOTOR_X] = 100;
    m_targetStep[MOTOR::MOTOR_Y] = 100;
    m_targetStep[MOTOR::MOTOR_Z] = 100;
    setRobotState(ROBOT_STATE::ROBOT_MOVE_HOST_GO_TO_CURRENT_POS_EXECUTE);
}

void RobotControler::captureGuest(int currentRow, int currentCol, int targetRow, int targetCol)
{
    m_targetStep[MOTOR::MOTOR_X] = 100;
    m_targetStep[MOTOR::MOTOR_Y] = 100;
    m_targetStep[MOTOR::MOTOR_Z] = 100;
    setRobotState(ROBOT_STATE::ROBOT_CAPTURE_GUEST_GO_TO_CURRENT_POS_EXECUTE);
}
void RobotControler::moveToTargetPostion() {
    bool moveToTargetDone = true;
    for(unsigned int axis=0; axis< (unsigned int)MOTOR::MOTOR_MAX - 1; axis++) {
        if(!moveDone((MOTOR)axis)){
            moveToTargetDone = false;
            m_currentStep[axis] += m_dirStep[axis];
        }
    }
    if(moveToTargetDone) {

    }
}
bool RobotControler::moveDone(MOTOR axis) {
    return m_dirStep[axis] >= 0 ? m_currentStep[axis] >= m_targetStep[axis]:
                                  m_currentStep[axis] < m_targetStep[axis];
}
void RobotControler::capture() {
    m_dirStep[MOTOR::MOTOR_CAP] = -1;
}
bool RobotControler::captureDone() {

}
void RobotControler::release() {
    m_dirStep[MOTOR::MOTOR_CAP] = 1;
}
bool RobotControler::releaseDone() {

}
