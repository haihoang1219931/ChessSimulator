#include "MainProcess.h"

MainProcess::MainProcess(QThread *parent) :
    QThread(parent),
    m_stopped(false),
    m_thread(nullptr)

{
    m_application = new ApplicationSim(this);
    memset(m_renderData,0,sizeof(m_renderData));
}

MainProcess::~MainProcess()
{
    stopService();
    sleep(2);
}
void MainProcess::run() {
    m_application->printf("Start\r\n");
    while(!m_stopped) {
        m_application->loop();
        Q_EMIT readyToUpdate();
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

