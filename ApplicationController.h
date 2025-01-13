#ifndef APPLICATIONCONTROLLER_H
#define APPLICATIONCONTROLLER_H

#include "ProjectTypes.h"

class RobotControler;
class ChessController;
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
    int motorPosition(MOTOR motorID);
    virtual int printf(const char *fmt, ...) = 0;
    virtual void msleep(int millis) = 0;
    virtual long getSystemTimeInMillis() = 0;
    virtual void checkInput() = 0;
    virtual void controlMotor(MOTOR motorID, int dir) = 0;
    virtual bool isAxisHome(MOTOR motorID) = 0;
protected:
    MACHINE_STATE m_machineState;
    RobotControler* m_robot;
    ChessController* m_chess;
    int m_frameWidth;
    int m_frameHeight;
    unsigned char m_frameData[9600]; // 320x240 bit
};

#endif // APPLICATIONCONTROLLER_H
