#ifndef APPLICATIONCONTROLLER_H
#define APPLICATIONCONTROLLER_H

#include "RobotControler.h"
#include "ChessController.h"

typedef enum{
    MACHINE_INITIALIZE_ROBOT,
    MACHINE_CHECK_PIECE,
    MACHINE_WAIT_OPPONENT_MOVE,
    MACHINE_CALCULATE_NEXT_MOVE,
    MACHINE_ATTACK_OPPONENT_PIECE,
    MACHINE_MOVE_PIECE,
    MACHINE_MOVE_PIECE_EXECUTE,
    MACHINE_RETURN_HOME,
} MACHINE_STATE;
class ApplicationController
{
public:
    explicit ApplicationController();
    virtual ~ApplicationController();
    
    int getScreenWidth();
    int getScreenHeight();
    unsigned char* getScreenData();
    void loop();
    MACHINE_STATE stateMachine();
    void setMachineState(MACHINE_STATE machineState);
    virtual int printf(const char *fmt, ...) = 0;
    virtual void msleep(int millis) = 0;
    virtual long getSystemTimeInMillis() = 0;
    virtual void checkInput() = 0;
    virtual void controlMotor(MOTOR motorID, int dir) = 0;

protected:
    MACHINE_STATE m_machineState;
    RobotControler* m_robot;
    ChessController* m_chess;
    int m_frameWidth;
    int m_frameHeight;
    unsigned char m_frameData[9600]; // 320x240 bit
};

#endif // APPLICATIONCONTROLLER_H
