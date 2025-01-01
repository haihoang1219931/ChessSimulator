#include "Motor.h"

Motor::Motor():
    m_targetStep(0),
    m_currentStep(0),
    m_dirStep(0)
{

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
