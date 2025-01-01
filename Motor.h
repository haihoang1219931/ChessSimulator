#ifndef MOTOR_H
#define MOTOR_H


class Motor
{
public:
    Motor();
    int targetStep();
    int currentStep();
    int dirStep();
    bool isMoveDone();
    void setTargetStep(int targetStep);
    void setCurrentStep(int currentStep);
    void setDirStep(int dirStep);
    void move();
private:
    int m_targetStep;
    int m_currentStep;
    int m_dirStep;
    bool m_isHome;
};

#endif // MOTOR_H
