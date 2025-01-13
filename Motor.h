#ifndef MOTOR_H
#define MOTOR_H

class Motor
{
public:
    Motor();
    float armLength();
    float stepAngle();
    int targetStep();
    int currentStep();
    int dirStep();
    bool isMoveDone();
    void setTargetAngle(float targetAngle);
    void setArmLength(float armLength);
    void setStepAngle(float stepAngle);
    void setTargetStep(int targetStep);
    void setCurrentStep(int currentStep);
    void setDirStep(int dirStep);
    void move();
private:
    float m_armLength;
    float m_stepAngle;
    int m_targetStep;
    int m_currentStep;
    int m_dirStep;
};

#endif // MOTOR_H
