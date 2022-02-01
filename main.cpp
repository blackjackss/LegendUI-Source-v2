#include <QApplication>
#include "DarkStyle.h"
#include "mainwindow.h"
#include <QSslSocket>
#include <iostream>
#include <windows.h>
#include <QtWidgets>
#include <QtNetwork>
#include <QUrl>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QTimer>
#include <QSplashScreen>
#include "xor.h"
#include "tlhelp32.h"


bool IsNetwork()
{
    QList<QNetworkInterface> ifaces = QNetworkInterface::allInterfaces();
    bool result = false;
    for (int i = 0; i < ifaces.count(); i++)
    {
        QNetworkInterface iface = ifaces.at(i);
        if (iface.flags().testFlag(QNetworkInterface::IsUp)
            && !iface.flags().testFlag(QNetworkInterface::IsLoopBack))
        {
            for (int j = 0; j<iface.addressEntries().count(); j++)
            {
                if (result == false)
                    result = true;
            }
        }
    }
    return result;
}

DWORD WINAPI AntiSuspend()
{
    DWORD TimeTest1=0, TimeTest2=0;
    while(true)
    {
        TimeTest1 = TimeTest2;
        TimeTest2 = GetTickCount();
        if(TimeTest1 != 0)
        {
            if((TimeTest2-TimeTest1) > 1500)
            {
                ExitProcess(0);
                TerminateProcess(GetCurrentProcess(), 1);
            }
        }
        Sleep(10);
    }
    return 0;
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    a.setStyle(new DarkStyle);
    CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)AntiSuspend, NULL, NULL, NULL);


    MainWindow m;
    m.show();

    if(!IsNetwork()){
        ExitProcess(-1);
    }

    QDesktopWidget widget;
        QRect screenGeometry = widget.screenGeometry();//.availableGeometry(widget.primaryScreen());

        int height = screenGeometry.height();
        int width = screenGeometry.width();
        m.move(-50000,-50000);

        m.move((width - m.width()) / 2.5,
                        (height - m.height()) / 2.5);



 return a.exec();
}
