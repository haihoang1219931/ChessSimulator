#ifndef ROBOTCONTROLER_H
#define ROBOTCONTROLER_H

#include <stdio.h>
#include "Motor.h"

#define MOTOR_DIR_NORMAL 1
#define MOTOR_DIR_INVERSE -1
#define MOTOR_MAX_SEQUENCE 20
#define MOVE_CODE_NO_MOVE 0
#define MOVE_CODE_HAS_MOVE 1
typedef enum {
    MOTOR_X,
    MOTOR_Y,
    MOTOR_Z,
    MOTOR_CAP,
    MOTOR_MAX,
} MOTOR;

typedef enum {
    ROBOT_INIT_STATE,
    ROBOT_RETURN_HOME,
    ROBOT_MOVE_PIECE
} ROBOT_STATE;

#pragma pack(1)
typedef struct {
    unsigned char moveCode;
    bool moveInit;
    int step[MOTOR_MAX];
} MoveLocation;

class ApplicationController;
class RobotControler
{
public:
    RobotControler(ApplicationController* app);
    void loop();
    void setRobotState(ROBOT_STATE robotState);
    Motor* getMotor(MOTOR axis);
    void returnHome();
    void moveHost(int currentRow, int currentCol, int targetRow, int targetCol);
    void captureGuest(int currentRow, int currentCol, int targetRow, int targetCol);
    void moveToTargetPostion();
    bool moveDone(MOTOR axis);
    void capture();
    bool captureDone();
    void release();
    bool releaseDone();
private:
    ApplicationController* m_app;
    ROBOT_STATE m_robotState;
    Motor m_motorList[MOTOR::MOTOR_MAX];
    MoveLocation m_moveSequence[MOTOR_MAX_SEQUENCE];
    int m_numberMove;
    int m_currentMoveID;
};

#endif // ROBOTCONTROLER_H
