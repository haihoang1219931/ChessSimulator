#include "MainProcess.h"

MainProcess::MainProcess(QThread *parent) :
    QThread(parent),
    m_stopped(false),
    m_thread(nullptr)

{
    m_application = new ApplicationSim(this);
    memset(m_renderData,0,sizeof(m_renderData));
    m_mutex = new QMutex;
    m_pauseCond = new QWaitCondition;
}

MainProcess::~MainProcess()
{
    stopService();
    sleep(2);
}
void MainProcess::pause(bool pause){
    if(pause == true){
        m_mutex->lock();
        m_pause = true;
        m_mutex->unlock();
    }else{
        m_mutex->lock();
        m_pause = false;
        m_mutex->unlock();
        m_pauseCond->wakeAll();
    }
}

void MainProcess::run() {
    m_application->printf("Start\r\n");
    while(!m_stopped) {
        m_mutex->lock();
        if(m_pause)
            m_pauseCond->wait(m_mutex); // in this place, your thread will stop to execute until someone calls resume
        m_mutex->unlock();
        m_application->loop();
        Q_EMIT readyToUpdate();
        Q_EMIT robotChanged(
                    m_application->motorPosition(MOTOR::MOTOR_X),
                    m_application->motorPosition(MOTOR::MOTOR_Y),
                    m_application->motorPosition(MOTOR::MOTOR_Z),
                    m_application->motorPosition(MOTOR::MOTOR_CAP));
        m_application->msleep(30);
    }
    m_application->printf("Exit\r\n");
}
void MainProcess::startService() {
    if(m_thread != nullptr)
        m_thread->start();
    else start();
}
void MainProcess::stopService() {
    m_stopped = true;
    m_thread->terminate();
}
void MainProcess::setRender(VideoRender* render)
{
    m_render = render;
}
void MainProcess::updateScreen() {

}

