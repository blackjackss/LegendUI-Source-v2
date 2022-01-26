#include "ChatterBoxServer.h"
#include <QMessageBox>
#include <QTcpSocket>
#include <QRegExp>

ChatterBoxServer::ChatterBoxServer(QObject *parent) : QTcpServer(parent)
{
}

void ChatterBoxServer::incomingConnection(int socketfd)
{

}

void ChatterBoxServer::readyRead()
{

}
