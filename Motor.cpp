#include "Motor.h"

Motor::Motor():
    m_targetStep(0),
    m_currentStep(0),
    m_dirStep(0)
{

}
float Motor::armLength() {
    return m_armLength;
}
int Motor::targetStep() {
    return m_targetStep;
}
int Motor::currentStep() {
    return m_currentStep;
}
int Motor::dirStep() {
    return m_dirStep;
}
bool Motor::isMoveDone() {
    return m_currentStep == m_targetStep;
}
void Motor::setTargetAngle(float targetAngle) {
    m_targetStep = (int)(targetAngle/m_stepAngle);
}
void Motor::setArmLength(float armLength) {
    m_armLength = armLength;
}
void Motor::setStepAngle(float stepAngle) {
    m_stepAngle = stepAngle;
}
void Motor::setTargetStep(int targetStep) {
    m_targetStep = targetStep;
}
void Motor::setCurrentStep(int currentStep) {
    m_currentStep = currentStep;
}
void Motor::setDirStep(int dirStep) {
    m_dirStep = dirStep;
}
void Motor::move() {
    m_currentStep += m_dirStep;
}
