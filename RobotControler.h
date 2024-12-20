#ifndef ROBOTCONTROLER_H
#define ROBOTCONTROLER_H

#include <stdio.h>
typedef enum {
    MOTOR_X,
    MOTOR_Y,
    MOTOR_Z,
    MOTOR_CAP,
    MOTOR_MAX,
} MOTOR;

typedef enum {
    ROBOT_WAIT_COMMAND,
    ROBOT_MOVE_HOST_GO_TO_CURRENT_POS,
    ROBOT_MOVE_HOST_GO_TO_CURRENT_POS_EXECUTE,
    ROBOT_MOVE_HOST_CAPTURE,
    ROBOT_MOVE_HOST_CAPTURE_EXECUTE,
    ROBOT_MOVE_HOST_GO_TO_TARGET_POS,
    ROBOT_MOVE_HOST_GO_TO_TARGET_POS_EXECUTE,
    ROBOT_MOVE_HOST_RELEASE,
    ROBOT_MOVE_HOST_RELEASE_EXECUTE,
    ROBOT_CAPTURE_GUEST_GO_TO_CURRENT_POS,
    ROBOT_CAPTURE_GUEST_GO_TO_CURRENT_POS_EXECUTE,
    ROBOT_CAPTURE_GUEST_CAPTURE,
    ROBOT_CAPTURE_GUEST_CAPTURE_EXECUTE,
    ROBOT_CAPTURE_GUEST_GO_TO_BOX_POS,
    ROBOT_CAPTURE_GUEST_GO_TO_BOX_POS_EXECUTE,
    ROBOT_CAPTURE_GUEST_RELEASE,
    ROBOT_CAPTURE_GUEST_RELEASE_EXECUTE,
} ROBOT_STATE;

class ApplicationController;
class RobotControler
{
public:
    RobotControler(ApplicationController* app);
    void loop();
    void setRobotState(ROBOT_STATE robotState);
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
    unsigned int m_targetStep[MOTOR::MOTOR_MAX];
    unsigned int m_currentStep[MOTOR::MOTOR_MAX];
    int m_dirStep[MOTOR::MOTOR_MAX];
};

#endif // ROBOTCONTROLER_H
