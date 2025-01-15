#include "ApplicationSim.h"
#include "RobotControler.h"
#ifdef __linux__
#include <sys/time.h>
#include <unistd.h>
#elif _WIN32
#include <time.h>
#include <unistd.h>
#else
#endif

ApplicationSim::ApplicationSim(MainProcess* mainProcess)
{
    m_mainProcess = mainProcess;
    m_machineState = MACHINE_STATE::MACHINE_INITIALIZE_ROBOT;
    m_robot->getMotor(MOTOR::MOTOR_ARM1)->setCurrentStep(0);
    m_robot->getMotor(MOTOR::MOTOR_ARM2)->setCurrentStep(180);
    m_robot->getMotor(MOTOR::MOTOR_ARM3)->setCurrentStep(0);
    m_robot->getMotor(MOTOR::MOTOR_CAP)->setCurrentStep(100);
    m_robot->getMotor(MOTOR::MOTOR_ARM1)->setTargetStep(0);
    m_robot->getMotor(MOTOR::MOTOR_ARM2)->setTargetStep(180);
    m_robot->getMotor(MOTOR::MOTOR_ARM3)->setTargetStep(0);
    m_robot->getMotor(MOTOR::MOTOR_CAP)->setTargetStep(100);

    ::printf("ApplicationSim constructor\r\n");
}
int ApplicationSim::printf(const char *fmt, ...) {
    char buffer[256];
    va_list args;
    va_start(args, fmt);
    int rc = vsprintf(buffer, fmt, args);
    va_end(args);
    ::printf("%s",buffer);
    fflush(stdout);
    return rc;
}
void ApplicationSim::msleep(int millis) {
#ifdef __linux__
    //linux code goes here
    struct timespec ts = { millis / 1000, (millis % 1000) * 1000 * 1000 };
    nanosleep(&ts, NULL);
#elif _WIN32
    // windows code goes here
    struct timespec ts;
    ts.tv_sec = millis/1000000;
    ts.tv_nsec = millis*1000000;
    nanosleep(&ts, NULL);
#else
#endif
}

long ApplicationSim::getSystemTimeInMillis() {
#ifdef __linux__
    struct timeval curTime;
    gettimeofday(&curTime, NULL);
    return (curTime.tv_usec/1000 + curTime.tv_sec*1000);
#elif _WIN32
    clock_t curTime = clock();
    return curTime * (1000.0 / CLOCKS_PER_SEC);
#else
    return 0;
#endif
}
void ApplicationSim::checkInput() {
#ifdef DEBUG
    this->printf("I");
#endif
}
void ApplicationSim::controlMotor(MOTOR motorID, int dir) {
    if(m_robot->getMotor(motorID)->currentStep() ==
            m_robot->getMotor(motorID)->targetStep()){
    } else {
#ifdef DEBUG
        this->printf("MOTOR[%d] TG[%03d] CR[%03d] H[%s]\r\n",
            motorID,
            m_robot->getMotor(motorID)->targetStep(),
            m_robot->getMotor(motorID)->currentStep(),
            m_robot->getMotor(motorID)->isHome()?"TRUE":"FALSE");
#endif
        m_robot->getMotor(motorID)->setDirStep(dir);
        m_robot->getMotor(motorID)->move();
    }
}
bool ApplicationSim::isAxisHome(MOTOR motorID) {
    return m_robot->getMotor(motorID)->isMoveDone();
}
