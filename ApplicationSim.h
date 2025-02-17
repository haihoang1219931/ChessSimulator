#ifndef APPLICATIONSIM_H
#define APPLICATIONSIM_H

#include <QObject>
#include <QThread>
#include <QSize>
#include "ApplicationController.h"
#include "VideoDisplay/VideoRender.h"
class MainProcess;
class ApplicationSim : public ApplicationController
{
public:
    ApplicationSim(MainProcess* m_mainProcess);
    int printf(const char *fmt, ...) override;
    void msleep(int millis) override;
    long getSystemTimeInMillis() override;
    void checkInput() override;
    void controlMotor(MOTOR motorID, int dir) override;
    bool isAxisHome(MOTOR motorID) override;
private:
    MainProcess* m_mainProcess;
};

#endif // APPLICATIONSIM_H
