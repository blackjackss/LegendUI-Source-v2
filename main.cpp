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





int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    a.setStyle(new DarkStyle);



    MainWindow m;
    m.show();


    QDesktopWidget widget;
        QRect screenGeometry = widget.screenGeometry();//.availableGeometry(widget.primaryScreen());

        int height = screenGeometry.height();
        int width = screenGeometry.width();
        m.move(-50000,-50000);

        m.move((width - m.width()) / 2.5,
                        (height - m.height()) / 2.5);



 return a.exec();
}
