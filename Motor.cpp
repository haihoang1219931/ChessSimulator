#include "Motor.h"

Motor::Motor():
    m_targetStep(0),
    m_currentStep(0),
    m_dirStep(0),
    m_isHome(false)
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
bool Motor::isHome() {
    return m_isHome;
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
void Motor::setHome(bool isHome) {
    m_isHome = isHome;
}
void Motor::move() {
    m_currentStep += m_dirStep;
}
