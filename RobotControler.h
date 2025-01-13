#ifndef ROBOTCONTROLER_H
#define ROBOTCONTROLER_H

#include <stdio.h>
#include "ProjectTypes.h"
#include "Motor.h"

class ApplicationController;
class RobotControler
{
public:
    RobotControler(ApplicationController* app);
    void loop();
    void setRobotState(ROBOT_STATE robotState);
    Motor* getMotor(MOTOR axis);
    void returnHome();
    void moveHost(ChessMove chessMove);
    void moveToTargetPostion();
    bool moveDone(MOTOR axis);
    int motorPosition(MOTOR motorID);
    void calculateRobotArm(float x, float y, float a1, float a2, float* q1, float* q2);
private:
    ApplicationController* m_app;
    ROBOT_STATE m_robotState;
    float m_distanceToChessBoard;
    float m_chessBoardSquareLength;
    Motor m_motorList[MOTOR::MOTOR_MAX];
    MoveLocation m_moveSequence[MOTOR_MAX_SEQUENCE];
    int m_numberMove;
    int m_currentMoveID;
};

#endif // ROBOTCONTROLER_H
