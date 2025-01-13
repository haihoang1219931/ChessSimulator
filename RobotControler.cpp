#include "RobotControler.h"
#include "ApplicationController.h"
#include <math.h>
#define CHESS_ROW 8
#define CHESS_COL 8
RobotControler::RobotControler(ApplicationController* app)
{
    m_app = app;
    m_robotState = ROBOT_STATE::ROBOT_INIT_STATE;
    m_distanceToChessBoard = 50.0f; // mm
    m_chessBoardSquareLength = 25.0f; // mm
    m_motorList[MOTOR::MOTOR_BASE].setArmLength(129.0f);
    m_motorList[MOTOR::MOTOR_ARM1].setArmLength(139.0f);
    m_motorList[MOTOR::MOTOR_ARM2].setArmLength(139.0f);
    m_motorList[MOTOR::MOTOR_ARM3].setArmLength(109.0f);
    m_motorList[MOTOR::MOTOR_BASE].setStepAngle(1.0f);
    m_motorList[MOTOR::MOTOR_ARM1].setStepAngle(1.0f);
    m_motorList[MOTOR::MOTOR_ARM2].setStepAngle(1.0f);
    m_motorList[MOTOR::MOTOR_ARM3].setStepAngle(1.0f);
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
void RobotControler::moveHost(ChessMove chessMove) {
    m_app->printf("Move Host\r\n");
    int currentRow;
    int currentCol;
    int targetRow;
    int targetCol;
    float xRobotToCurrentPos = (currentCol-4) * m_chessBoardSquareLength;
    float yRobotToCurrentPos = currentRow * m_chessBoardSquareLength + m_distanceToChessBoard;
    float dRobotToCurrentPos = sqrt(xRobotToCurrentPos*xRobotToCurrentPos+yRobotToCurrentPos*yRobotToCurrentPos);
    float robotToCurrentPosBaseAngle = atanf(xRobotToCurrentPos/yRobotToCurrentPos);

    float robotToCurrentPosAngleArm1;
    float robotToCurrentPosAngleArm2;
    calculateRobotArm(dRobotToCurrentPos,m_motorList[MOTOR::MOTOR_ARM3].armLength() - m_motorList[MOTOR::MOTOR_BASE].armLength(),
            m_motorList[MOTOR::MOTOR_ARM1].armLength(),m_motorList[MOTOR::MOTOR_ARM2].armLength(),
            &robotToCurrentPosAngleArm1,&robotToCurrentPosAngleArm2);
    float xRobotToTargetPos = (targetCol-4) * m_chessBoardSquareLength;
    float yRobotToTargetPos = targetRow * m_chessBoardSquareLength + m_distanceToChessBoard;
    float dRobotToTargetPos = sqrt(xRobotToTargetPos*xRobotToTargetPos+yRobotToTargetPos*yRobotToTargetPos);
    float robotToTargetPosAngle = atanf(xRobotToTargetPos/yRobotToTargetPos);

    float robotToTargetPosAngleArm1;
    float robotToTargetPosAngleArm2;
    calculateRobotArm(dRobotToTargetPos,m_motorList[MOTOR::MOTOR_ARM3].armLength() - m_motorList[MOTOR::MOTOR_BASE].armLength(),
            m_motorList[MOTOR::MOTOR_ARM1].armLength(),m_motorList[MOTOR::MOTOR_ARM2].armLength(),
            &robotToTargetPosAngleArm1,&robotToTargetPosAngleArm2);

    m_moveSequence[0] = {false,{robotToCurrentPosBaseAngle,robotToCurrentPosAngleArm1+90,180-robotToCurrentPosAngleArm2,65,0}};
    m_moveSequence[1] = {false,{robotToCurrentPosBaseAngle,robotToCurrentPosAngleArm1+90,180-robotToCurrentPosAngleArm2,65,100}};
    m_moveSequence[2] = {false,{robotToTargetPosAngle,robotToTargetPosAngleArm1+90,180-robotToTargetPosAngleArm2,65,100}};
    m_moveSequence[3] = {false,{robotToTargetPosAngle,robotToTargetPosAngleArm1+90,180-robotToTargetPosAngleArm2,65,0}};
    m_moveSequence[4] = {false,{0,135+90,180-robotToCurrentPosAngleArm2,65,0}};
    m_numberMove = 8;
    m_currentMoveID = 0;
}

void RobotControler::moveToTargetPostion() {
    if(!m_moveSequence[m_currentMoveID].moveInit) {
        for(unsigned int axis=0; axis< (unsigned int)MOTOR::MOTOR_MAX; axis++) {
            m_motorList[axis].setTargetAngle(m_moveSequence[m_currentMoveID].armAngle[axis]);
            m_motorList[axis].setDirStep(m_motorList[axis].targetStep() > m_motorList[axis].currentStep() ?
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
                  m_motorList[MOTOR_ARM1].currentStep(),
                  m_motorList[MOTOR_ARM2].currentStep(),
                  m_motorList[MOTOR_ARM3].currentStep(),
                  m_motorList[MOTOR_CAP].currentStep());
    if(allMotorsAreHome) m_currentMoveID++;
    if(m_currentMoveID >= m_numberMove) m_app->setMachineState(MACHINE_STATE::MACHINE_WAIT_OPPONENT_MOVE);
}
bool RobotControler::moveDone(MOTOR axis) {
    return m_motorList[axis].dirStep() >= 0 ? m_motorList[axis].currentStep() >= m_motorList[axis].targetStep():
                                  m_motorList[axis].currentStep() < m_motorList[axis].targetStep();
}

int RobotControler::motorPosition(MOTOR motorID) {
    return m_motorList[motorID].currentStep();
}
void RobotControler::calculateRobotArm(float x, float y, float a1, float a2, float* q1, float* q2) {
    *q2 = -acos(x*x + y*y -a1*a1-a2*a2/(2*a1*a2));
    *q1 = atan(y/x) + atan(a2*sin(*q2)/(a1+a2*cos(*q2)));
}
