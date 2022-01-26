#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QEventLoop>
#include <QObject>
#include <QByteArray>
#include <QMessageBox>
#include <QDesktopServices>
#include "mycrypt.h"
#include "popup.h"
#include "ZortStr.h"
#include <QFile>
#include <iostream>
#include <ctime>

/*XenforoAPI v2.0*/
/*Coded by Blackjack*/

QString MyCryptDs(QString data){ SimpleCrypt crypto(Q_UINT64_C(0x0c2ad4a4acb9f025));QString result = crypto.decryptToString(data);crypto.setCompressionMode(SimpleCrypt::CompressionAlways); crypto.setIntegrityProtectionMode(SimpleCrypt::ProtectionHash);return result;}
QString MyCrypteEs(QString data){SimpleCrypt crypto(Q_UINT64_C(0x0c2ad4a4acb9f025));QString result = crypto.encryptToString(data);crypto.setCompressionMode(SimpleCrypt::CompressionAlways); crypto.setIntegrityProtectionMode(SimpleCrypt::ProtectionHash);return result;}
QString MyCryptD(QString data){ SimpleCrypt crypto(Q_UINT64_C(0x0c2ad4a4acb9f075));QString result = crypto.decryptToString(data); crypto.setCompressionMode(SimpleCrypt::CompressionAlways); crypto.setIntegrityProtectionMode(SimpleCrypt::ProtectionHash); return result;}
QString MyCrypteE(QString data){SimpleCrypt crypto(Q_UINT64_C(0x0c2ad4a4acb9f075));QString result = crypto.encryptToString(data);crypto.setCompressionMode(SimpleCrypt::CompressionAlways); crypto.setIntegrityProtectionMode(SimpleCrypt::ProtectionHash);return result;}
QString MyCryptD1(QString data){ SimpleCrypt crypto(Q_UINT64_C(0x0c9fa2b9bfa5f024));QString result = crypto.decryptToString(data);crypto.setCompressionMode(SimpleCrypt::CompressionAlways); crypto.setIntegrityProtectionMode(SimpleCrypt::ProtectionHash);return result;}
QString MyCrypteE1(QString data){SimpleCrypt crypto(Q_UINT64_C(0x0c9fa2b9bfa5f024));QString result = crypto.encryptToString(data);crypto.setCompressionMode(SimpleCrypt::CompressionAlways); crypto.setIntegrityProtectionMode(SimpleCrypt::ProtectionHash);return result;}
QString MyCryptD2(QString data){ SimpleCrypt crypto(Q_UINT64_C(0x0a6df1b8bbb18f23));QString result = crypto.decryptToString(data);crypto.setCompressionMode(SimpleCrypt::CompressionAlways); crypto.setIntegrityProtectionMode(SimpleCrypt::ProtectionHash);return result;}
QString MyCrypteE2(QString data){SimpleCrypt crypto(Q_UINT64_C(0x0a6df1b8bbb18f23));QString result = crypto.encryptToString(data);crypto.setCompressionMode(SimpleCrypt::CompressionAlways); crypto.setIntegrityProtectionMode(SimpleCrypt::ProtectionHash);return result;}
QString MyCryptD3(QString data){ SimpleCrypt crypto(Q_UINT64_C(0x0c3ff8abacb3a629));QString result = crypto.decryptToString(data);crypto.setCompressionMode(SimpleCrypt::CompressionAlways); crypto.setIntegrityProtectionMode(SimpleCrypt::ProtectionHash);return result;}
QString MyCrypteE3(QString data){SimpleCrypt crypto(Q_UINT64_C(0x0c3ff8abacb3a629));QString result = crypto.encryptToString(data);crypto.setCompressionMode(SimpleCrypt::CompressionAlways); crypto.setIntegrityProtectionMode(SimpleCrypt::ProtectionHash);return result;}
QString MyCryptD4(QString data){ SimpleCrypt crypto(Q_UINT64_C(0x0cf68b4a91a6a888));QString result = crypto.decryptToString(data);crypto.setCompressionMode(SimpleCrypt::CompressionAlways); crypto.setIntegrityProtectionMode(SimpleCrypt::ProtectionHash);return result;}
QString MyCrypteE4(QString data){SimpleCrypt crypto(Q_UINT64_C(0x0cf68b4a91a6a888));QString result = crypto.encryptToString(data);crypto.setCompressionMode(SimpleCrypt::CompressionAlways); crypto.setIntegrityProtectionMode(SimpleCrypt::ProtectionHash);return result;}
QString Base64D(QString data){std::string s = data.toStdString();std::string decoded = base64_decode(s);return QString::fromUtf8(decoded.c_str());}
QString Base64E(QString data){std::string s = data.toStdString();std::string encoded = base64_encode(reinterpret_cast<const unsigned char*>(s.c_str()), s.length());return QString::fromUtf8(encoded.c_str());}


QString Encrypt(QString plaintext)
{
    QString encryptedtext = MyCrypteE(MyCrypteE1(MyCrypteE2(MyCrypteE3(MyCrypteE4(Base64E(MyCrypteE(plaintext.toLatin1())))))));

    return encryptedtext;
}

QString Decrypt(QString plaintext)
{
    QString decryptedtext = MyCryptD(Base64D(MyCryptD4(MyCryptD3(MyCryptD2(MyCryptD1(MyCryptD(plaintext.toLatin1())))))));
    return decryptedtext;
}

QString WebSite = XorStr("http://localhost/dashboard/");
namespace App {
QString Version = XorStr("v1.0.0");
QString ServerIP;
int ServerPort = 4200;
}

namespace Cheats{

QString download;
QString about;
QString website;

}
namespace User {
QString ID;
QString Username;
QString Email;

QString Rank1;
QString Rank2;
QString VRank;


bool Admin = false;
bool Premium = false;
bool Ban = false;

QString Messagecount = 0;
QString Notificationcount = 0;

bool is_loggin = false;
}
QString FindRank(QString rankkey)
{
return 0;
}

QString Regex(QString data){
    QRegExp rx(XorStr("\\b(.gif|.png|.jpg|.jpeg)\\b"));
    QString captured;
    //rx.indexIn("I sent you an email");     // returns -1 (no match)
    rx.indexIn(data); // returns 17

    return captured = rx.cap(1);
}

QPixmap DownloadPixmap(QString Url, int Width,int Height){
    QNetworkAccessManager* Manager = new QNetworkAccessManager;
    QNetworkRequest Request;
    Request.setUrl(Url);
    QSslConfiguration SSLConfig(QSslConfiguration::defaultConfiguration());

    Request.setSslConfiguration(SSLConfig);
    QNetworkReply *Response = Manager->get(Request);
    QEventLoop Event;
    QObject::connect(Response, SIGNAL(finished()), &Event, SLOT(quit()));
    Event.exec();
    QByteArray Bytes = Response->readAll();
    QImage Img(Width, Height, QImage::Format_Indexed8);
    Img.loadFromData(Bytes);
    return QPixmap::fromImage(Img);
}
std::string Discet()
{
    char buffer[MAX_PATH];
    GetModuleFileNameA(NULL, buffer, MAX_PATH);
    std::string::size_type pos = std::string(buffer).find_last_of(XorStr("\\/"));

    return std::string(buffer).substr(0, pos) + XorStr("\\Updater.exe");
}


QString FindRankCSS(QString rankkey)
{
return 0;
}

namespace XenforoAPI {



}


QString DownloadString(QString Url){
    QNetworkAccessManager* Manager = new QNetworkAccessManager;
    QNetworkRequest Request;
    Request.setUrl(Url);
    QSslConfiguration SSLConfig(QSslConfiguration::defaultConfiguration());

    Request.setSslConfiguration(SSLConfig);
    QNetworkReply *Response = Manager->get(Request);
    QEventLoop Event;
    QObject::connect(Response, SIGNAL(finished()), &Event, SLOT(quit()));
    Event.exec();
    return Response->readAll();
}



QString CreateKey()
{
return 0;
}

QString Login(QString Username, QString Password)
{
return 0;
}




void OpenURL(QString url)
{
    QDesktopServices::openUrl(url);
}

void WriteFile(QString filename, QString data)
{

}

void Messagebox(QString title, QString message)
{
    QMessageBox msgBox;
        msgBox.setWindowTitle(title);
        msgBox.setText(message);
        msgBox.exec();
}

void Messagebox2(QString message)
{
    PopUp *popUp;
        popUp = new PopUp();
        popUp->setPopupText(message);
        popUp->show();
}

QString Encode(QString data)
{
return 0;
}

QString Decode(QString data)
{
return 0;
}


QString Server(QString path)
{
return 0;
}



