#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "xfapi.h"
#include "injector.h"
#include <curl/curl.h>
#include <stdio.h>
#include <QGraphicsBlurEffect>
#include "rapidjson/include/rapidjson/document.h"
#include <QSettings>
#include <openssl/aes.h>
#include <openssl/evp.h>
#include "ZortStr.h"
#include <urlmon.h>
#include <regex>
#include <QRegExp>
#include <QRegularExpressionMatch>
#include <QRegularExpression>
#include <QCloseEvent>
#include <QFile>

void MainWindow::closeEvent (QCloseEvent *event)
{

   /* QFile avatarpng("C:\Windows\Temp\avatar.png");
    QFile avatarjpg("C:\Windows\Temp\avatar.jpg");
    QFile avatargif("C:\Windows\Temp\avatar.gif");

    QFile bannerpng("C:\Windows\Temp\banner.png");
    QFile bannergif("C:\Windows\Temp\banner.gif");
    QFile bannerjpg("C:\Windows\Temp\banner.jpg");

    QFile::remove(avatarpng);
    QFile::remove(avatarjpg);
    QFile::remove(avatargif);

    QFile::remove(bannerpng);
    QFile::remove(bannergif);
    QFile::remove(bannerjpg);*/

    event->accept();
}

#pragma comment (lib,"urlmon.lib")

//#pragma comment(lib,"libcrypto");

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      m_bMousePressed(false),
      m_bDragTop(false),
      m_bDragLeft(false),
      m_bDragRight(false),
      m_bDragBottom(false) {
  ui->setupUi(this);
  setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint);
  setWindowFlags(windowFlags() | Qt::WindowMinimizeButtonHint);
  setMouseTracking(true);
  //ui->UIUserWidget->setVisible(false);



  //QMovie *pp = new QMovie(XorStr(":/darkstyle/1.gif"));
  //ui->pp->setMovie(pp);
 // pp->start();

  QFontDatabase::addApplicationFont(XorStr(":fonts/Roboto/Roboto-Bold.ttf"));
  QFontDatabase::addApplicationFont(XorStr(":fonts/Roboto/Roboto.ttf"));
  if (QFontDatabase::addApplicationFont(XorStr(":fonts/Roboto/Roboto-Bold.ttf")) < 0)
  {
       Messagebox(XorStr("LegendUI Beta Security"),XorStr("Font cannot be loaded !"));
 }
  QFontDatabase::addApplicationFont(XorStr(":/darkstyle/FontAwesomeR.otf"));
 if (QFontDatabase::addApplicationFont(XorStr(":/darkstyle/FontAwesomeR.otf")) < 0)
  {
      Messagebox(XorStr("LegendUI Security"),XorStr("FontAwesome cannot be loaded !"));
  }
 QFontDatabase::addApplicationFont(XorStr(":/darkstyle/FontAwesomeS.otf"));
  if (QFontDatabase::addApplicationFont(XorStr(":/darkstyle/FontAwesomeS.otf")) < 0)
  {
     Messagebox(XorStr("LegendUI Security"),XorStr("FontAwesome cannot be loaded !"));
  }

 ui->UITabBar->tabBar()->hide();
 ui->nav_bar_tabw->tabBar()->hide();
 ui->setting_ana_ic_tab->tabBar()->hide();
 ui->label_19->hide();
 ui->label_22->hide();



 ReadLCPG(Decrypt(DownloadString(XorStr("http://cdn.legendaryauth.cf/cheats.json"))));
 ReadRemember();
 LoadLoginBG();



// ui->UITabBar->setCurrentIndex(0);

 //ui->nav_bat_logo->setPixmap(QPixmap(":/darkstyle/legend.png"));


 //ui->hileList->setVerticalScrollBar(ui->scrollBar);





//ui->hileList->addItem("test");

// ui->hileList->insertItem(0,item);



}

void LCAuth(QString username, QString password)
{
    return;
}

void MainWindow::LoadLoginBG()
{
    QSettings theme(QSettings::Registry64Format, QSettings::UserScope, XorStr("LegendUI"), XorStr("Theme"));
    QString bg = theme.value(XorStr("_login_bg")).toByteArray().constData();

    if(bg != "")
    {
        QMovie *bgm = new QMovie(Decrypt(bg));
        ui->login_bg_2->setMovie(bgm);
        bgm->start();

        ui->loginbg_slct_splash->setPixmap(QPixmap(Decrypt(bg)));
    }
    else
    {
        QMovie *login_gif = new QMovie(XorStr(":/darkstyle/login_bg_one.gif"));
        QMovie *login_gif2 = new QMovie(XorStr(":/darkstyle/login_2.gif"));
        QMovie *login_gif3 = new QMovie(XorStr(":/darkstyle/login_bg_two.jpg"));

        int random = qrand() % ((3 + 1) - 1) + 1;
        if(random == 1)
        {
         ui->login_bg_2->setMovie(login_gif);
            login_gif->start();
        }
        else if(random == 2)
        {
            ui->login_bg_2->setMovie(login_gif2);
            login_gif2->start();
        }
        else if(random == 3){
            ui->login_bg_2->setMovie(login_gif3);
            login_gif3->start();
        }

    }


}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::ReadLCPG(QString data)
{
    //Messagebox("LC",data);
    QJsonDocument document = QJsonDocument::fromJson(data.toUtf8());
       QJsonObject root = document.object();

    QJsonValue jsonValue = root.value(XorStr("cheats"));
        if (jsonValue.isArray()) {
          QJsonArray jsonArray = jsonValue.toArray();
           for (int i = 0; i < jsonArray.count(); i++) {
           QJsonObject subTree = jsonArray.at(i).toObject();
               QString isim = subTree.value(XorStr("isim")).toString();
           QString icon = subTree.value(XorStr("icon")).toString();
           AddCheats(isim, icon);
           }
       }
}

void MainWindow::GetCheats(QString isim)
{
    QString apiGet = Decrypt(DownloadString(XorStr("http://cdn.legendaryauth.cf/api.php?security=FUS85-MH-3D4JG-LC-38KD&isim=") + isim));

    //Messagebox("LC", apiGet);

    rapidjson::Document parser;

    parser.Parse(apiGet.toLatin1());

    Cheats::download = parser[XorStr("download")].GetString();
    Cheats::about = parser[XorStr("about")].GetString();
    Cheats::website = parser[XorStr("website")].GetString();

    QString lastupdate = parser[XorStr("lastupdate")].GetString();
    QString talimatlar = parser[XorStr("talimatlar")].GetString();
    QString name = parser[XorStr("name")].GetString();
    QString status = parser[XorStr("status")].GetString();
    QString image = parser[XorStr("image")].GetString();
    int margin = parser[XorStr("margin")].GetInt();
   // Messagebox("LC",status);

    ui->image_gorsel->setPixmap(DownloadPixmap(image,951,301));
    ui->image_gorsel->setMargin(margin);

    ui->lastupdate_label->setText(lastupdate);
    ui->talimat_text->setPlainText(talimatlar);
    ui->name_label->setText(name);
    ui->status_label->setText(status);

    if(status == XorStr("Detected"))
    {
        ui->status_label->setStyleSheet(XorStr("color: rgb(255, 0, 0);background-color: rgba(255, 255, 255, 0);"));
    }
    if(status == XorStr("Beta Test"))
    {
        ui->status_label->setStyleSheet(XorStr("color:rgb(0, 165, 165); background-color: rgba(255, 255, 255, 0);"));
    }
    if(status == XorStr("Undetected"))
    {
        ui->status_label->setStyleSheet(XorStr("color: rgb(75, 255, 55); background-color: rgba(255, 255, 255, 0);"));
    }

    if(status != XorStr("Undetected"))
    {
        if(!User::Admin){
        ui->status_karartma->show();
        }
    }
    else
    {
        ui->status_karartma->hide();
    }


}

void MainWindow::AddCheats(QString isim, QString icon)
{
    item = new QListWidgetItem;

    item->setText(isim);
    //Messagebox("LC",DownloadString("http://testerspanel.cf/zulu.png"));
    item->setIcon(DownloadPixmap(icon,256,256));

    QFont font;
    font.setFamily(XorStr("Roboto Black"));
    font.setPixelSize(13);

    ui->hileList->setFont(font);
    //ui->hileList->addItem(listi);
    ui->hileList->insertItem(0,item);
}

void MainWindow::checkBorderDragging(QMouseEvent *event) {
  if (isMaximized()) {
    return;
  }

  QPoint globalMousePos = event->globalPos();
  if (m_bMousePressed) {
    QRect availGeometry = QApplication::desktop()->availableGeometry();
    int h = availGeometry.height();
    int w = availGeometry.width();
    if (QApplication::desktop()->isVirtualDesktop()) {
      QSize sz = QApplication::desktop()->size();
      h = sz.height();
      w = sz.width();
    }
    if (m_bDragTop && m_bDragRight) {
      int diff =
          globalMousePos.x() - (m_StartGeometry.x() + m_StartGeometry.width());
      int neww = m_StartGeometry.width() + diff;
      diff = globalMousePos.y() - m_StartGeometry.y();
      int newy = m_StartGeometry.y() + diff;
      if (neww > 0 && newy > 0 && newy < h - 50) {
        QRect newg = m_StartGeometry;
        newg.setWidth(neww);
        newg.setX(m_StartGeometry.x());
        newg.setY(newy);
        setGeometry(newg);
      }
    }
    else if (m_bDragTop && m_bDragLeft) {
      int diff = globalMousePos.y() - m_StartGeometry.y();
      int newy = m_StartGeometry.y() + diff;
      diff = globalMousePos.x() - m_StartGeometry.x();
      int newx = m_StartGeometry.x() + diff;
      if (newy > 0 && newx > 0) {
        QRect newg = m_StartGeometry;
        newg.setY(newy);
        newg.setX(newx);
        setGeometry(newg);
      }
    }
    else if (m_bDragBottom && m_bDragLeft) {
      int diff =
          globalMousePos.y() - (m_StartGeometry.y() + m_StartGeometry.height());
      int newh = m_StartGeometry.height() + diff;
      diff = globalMousePos.x() - m_StartGeometry.x();
      int newx = m_StartGeometry.x() + diff;
      if (newh > 0 && newx > 0) {
        QRect newg = m_StartGeometry;
        newg.setX(newx);
        newg.setHeight(newh);
        setGeometry(newg);
      }
    } else if (m_bDragTop) {
      int diff = globalMousePos.y() - m_StartGeometry.y();
      int newy = m_StartGeometry.y() + diff;
      if (newy > 0 && newy < h - 50) {
        QRect newg = m_StartGeometry;
        newg.setY(newy);
        setGeometry(newg);
      }
    } else if (m_bDragLeft) {
      int diff = globalMousePos.x() - m_StartGeometry.x();
      int newx = m_StartGeometry.x() + diff;
      if (newx > 0 && newx < w - 50) {
        QRect newg = m_StartGeometry;
        newg.setX(newx);
        setGeometry(newg);
      }
    } else if (m_bDragRight) {
      int diff =
          globalMousePos.x() - (m_StartGeometry.x() + m_StartGeometry.width());
      int neww = m_StartGeometry.width() + diff;
      if (neww > 0) {
        QRect newg = m_StartGeometry;
        newg.setWidth(neww);
        newg.setX(m_StartGeometry.x());
        setGeometry(newg);
      }
    } else if (m_bDragBottom) {
      int diff =
          globalMousePos.y() - (m_StartGeometry.y() + m_StartGeometry.height());
      int newh = m_StartGeometry.height() + diff;
      if (newh > 0) {
        QRect newg = m_StartGeometry;
        newg.setHeight(newh);
        newg.setY(m_StartGeometry.y());
        setGeometry(newg);
      }
    }
  } else {
    if (leftBorderHit(globalMousePos) && topBorderHit(globalMousePos)) {
      setCursor(Qt::SizeFDiagCursor);
    } else if (rightBorderHit(globalMousePos) && topBorderHit(globalMousePos)) {
      setCursor(Qt::SizeBDiagCursor);
    } else if (leftBorderHit(globalMousePos) &&
               bottomBorderHit(globalMousePos)) {
      setCursor(Qt::SizeBDiagCursor);
    } else {
      if (topBorderHit(globalMousePos)) {
        setCursor(Qt::SizeVerCursor);
      } else if (leftBorderHit(globalMousePos)) {
        setCursor(Qt::SizeHorCursor);
      } else if (rightBorderHit(globalMousePos)) {
        setCursor(Qt::SizeHorCursor);
      } else if (bottomBorderHit(globalMousePos)) {
        setCursor(Qt::SizeVerCursor);
      } else {
        m_bDragTop = false;
        m_bDragLeft = false;
        m_bDragRight = false;
        m_bDragBottom = false;
        setCursor(Qt::ArrowCursor);
      }
    }
  }
}


bool MainWindow::leftBorderHit(const QPoint &pos) {
  const QRect &rect = this->geometry();
  if (pos.x() >= rect.x() && pos.x() <= rect.x() + CONST_DRAG_BORDER_SIZE) {
    return true;
  }
  return false;
}

bool MainWindow::rightBorderHit(const QPoint &pos) {
  const QRect &rect = this->geometry();
  int tmp = rect.x() + rect.width();
  if (pos.x() <= tmp && pos.x() >= (tmp - CONST_DRAG_BORDER_SIZE)) {
    return true;
  }
  return false;
}

bool MainWindow::topBorderHit(const QPoint &pos) {
  const QRect &rect = this->geometry();
  if (pos.y() >= rect.y() && pos.y() <= rect.y() + CONST_DRAG_BORDER_SIZE) {
    return true;
  }
  return false;
}

bool MainWindow::bottomBorderHit(const QPoint &pos) {
  const QRect &rect = this->geometry();
  int tmp = rect.y() + rect.height();
  if (pos.y() <= tmp && pos.y() >= (tmp - CONST_DRAG_BORDER_SIZE)) {
    return true;
  }
  return false;
}


bool MainWindow::eventFilter(QObject *obj, QEvent *event) {
  if (isMaximized()) {
    return QWidget::eventFilter(obj, event);
  }
  if (event->type() == QEvent::MouseMove) {
    QMouseEvent *pMouse = dynamic_cast<QMouseEvent *>(event);
    if (pMouse) {
      checkBorderDragging(pMouse);
    }
  }
  else if (event->type() == QEvent::MouseButtonPress && obj == this) {
    QMouseEvent *pMouse = dynamic_cast<QMouseEvent *>(event);
    if (pMouse) {
      mousePressEvent(pMouse);
    }
  } else if (event->type() == QEvent::MouseButtonRelease) {
    if (m_bMousePressed) {
      QMouseEvent *pMouse = dynamic_cast<QMouseEvent *>(event);
      if (pMouse) {
      }
    }
  }
  return QWidget::eventFilter(obj, event);
}

void MainWindow::on_UICloseButton_clicked()
{
     QApplication::quit();
}

void MainWindow::on_UIMinButton_clicked()
{
     setWindowState(Qt::WindowMinimized);
}

void MainWindow::readyRead()
{

}

void MainWindow::connected()
{

}

void MainWindow::SelectTab(int key)
{
    if(User::is_loggin)
    {
    if(key == 1)
    {
        ui->UITabBar->setCurrentIndex(0);
    }
    else if(key == 2)
    {
        ui->UITabBar->setCurrentIndex(1);
    }
    else if(key == 3)
    {
        ui->homeButton->setStyleSheet(XorStr("QPushButton{color:rgb(0, 165, 165);} QPushButton::hover{ color:rgb(0, 165, 165); }"));
        ui->cheats->setStyleSheet(XorStr("QPushButton::hover{ color:rgb(0, 165, 165); }"));
        ui->settingsButton->setStyleSheet(XorStr("QPushButton::hover{ color:rgb(0, 165, 165); }"));
        ui->nav_bar_tabw->setCurrentIndex(0);
    }
    else if(key == 4)
    {
        ui->homeButton->setStyleSheet(XorStr("QPushButton::hover{ color:rgb(0, 165, 165); }"));
        ui->cheatsButton->setStyleSheet(XorStr("QPushButton{color:rgb(0, 165, 165);} QPushButton::hover{ color:rgb(0, 165, 165); }"));
        ui->settingsButton->setStyleSheet(XorStr("QPushButton::hover{ color:rgb(0, 165, 165); }"));
        ui->nav_bar_tabw->setCurrentIndex(1);
    }
    else if(key == 5)
    {
        ui->homeButton->setStyleSheet(XorStr("QPushButton::hover{ color:rgb(0, 165, 165); }"));
        ui->cheatsButton->setStyleSheet(XorStr("QPushButton::hover{ color:rgb(0, 165, 165); }"));
        ui->settingsButton->setStyleSheet(XorStr("QPushButton{color:rgb(0, 165, 165);} QPushButton::hover{ color:rgb(0, 165, 165); }"));
        ui->nav_bar_tabw->setCurrentIndex(2);
    }
    else if(key == 6)
    {
        ui->setting_ana_ic_tab->setCurrentIndex(0);
        ui->settings_account_button->setStyleSheet(XorStr("border-left: 4px solid rgb(0, 165, 165);; background-color:#121212; color:rgb(0, 165, 165);"));
        ui->settings_loader_button->setStyleSheet(XorStr("QPushButton::hover {   background-color:palette(alternate-base); }"));
    }
    else if(key == 7)
    {
        ui->setting_ana_ic_tab->setCurrentIndex(1);
        ui->settings_account_button->setStyleSheet(XorStr("QPushButton::hover {   background-color:palette(alternate-base); }"));
        ui->settings_loader_button->setStyleSheet(XorStr("border-left: 4px solid rgb(0, 165, 165);; background-color:#121212; color:rgb(0, 165, 165);"));
    }
    }
}

void MainWindow::on_UICheatsButton_clicked()
{

}

void MainWindow::on_UINewsButton_clicked()
{

}

void MainWindow::on_UIOnlineButton_clicked()
{

}

void MainWindow::on_UIAccountButton_clicked()
{

}

QString MainWindow::ReadLine(int count)
{
return 0;
}

QString MainWindow::ReadLine2(int count)
{
return 0;
}


void MainWindow::on_UILoginButton_clicked()
{


}

QString DisplayProcess;
QString DisplayType;
void MainWindow::Start(QString ProcessName, QString FileUrl, QString InjType, QString FileType)
{
}

void MainWindow::Slot1()
{


}

void MainWindow::on_UIXCheatsStart_clicked()
{

}

void MainWindow::on_UIXCheatsTopic_clicked()
{

}

void MainWindow::on_UIXCheatsAbout_clicked()
{

}

void MainWindow::on_UIUserMessageIcon_clicked()
{

}

void MainWindow::on_UIUserNotiIcon_clicked()
{

}

void MainWindow::on_UILoginText4_clicked()
{

}

void MainWindow::on_UILoginText5_clicked()
{

}

void MainWindow::on_UILoginBackButton_clicked()
{

}


void MainWindow::on_UILoginText6_clicked()
{

}

void MainWindow::on_UICloseButton_triggered(QAction *arg1)
{

}

static const unsigned char key[] = {
    0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
    0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff,
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
    0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f
};

void MainWindow::WriteRemember(QString username, QString password){
    QSettings user(QSettings::Registry64Format, QSettings::UserScope, "LegendUI", "User");

    user.setValue(XorStr("_username"), Encrypt(username));
    user.setValue(XorStr("_password"), Encrypt(password));
}

void MainWindow::ReadRemember()
{
    QSettings user(QSettings::Registry64Format, QSettings::UserScope, XorStr("LegendUI"), XorStr("User"));
    QString readuser;
    QString readpassword;

    try{
        readuser = Decrypt(user.value(XorStr("_username")).toByteArray().constData());
        readpassword = Decrypt(user.value(XorStr("_password")).toByteArray().constData());

    ui->username->setText(readuser);
    ui->password->setText(readpassword);
    }catch(QException &exceptionRR){
        ui->username->setText(NULL);
        ui->password->setText(NULL);
    }
}

void MainWindow::FindRandUser(int group){
    QFont fontA;
    fontA.setFamily(XorStr("FontAwesome"));
    fontA.setPixelSize(13);
    ui->rank_logo->setFont(fontA);


    if(group == 2){
        ui->rank_label->setText(XorStr("Pasif Üye"));
            ui->rank_label->setStyleSheet(XorStr("padding: 1px 6px;text-align: center;color: #fafafa;     background: #7D7D7D;     border-color: #3a4558;     border-color: transparent; border-radius:2px;"));
        ui->rank_logo->setStyleSheet(XorStr("background-color: rgba(255, 255, 255, 0);"));
        ui->rank_logo->setText(QChar(0xf406));
        ui->label_2->setStyleSheet(XorStr("background-color: rgba(255, 255, 255, 0);"));
    }else if(group == 6){
        ui->rank_label->setText(XorStr("Aktif Üye"));
            ui->rank_label->setStyleSheet(XorStr("padding: 1px 6px;text-align: center;color: #fafafa;     background: #2577b1;     border-color: #3a4558;     border-color: transparent; border-radius:2px;"));
        ui->rank_logo->setStyleSheet(XorStr("background-color: rgba(255, 255, 255, 0);"));
        ui->rank_logo->setText(QChar(0xf406));
        ui->label_2->setStyleSheet(XorStr("background-color: rgba(255, 255, 255, 0);"));
    }else if(group == 7){
        ui->rank_label->setText(XorStr("Onaylı Üye"));
            ui->rank_label->setStyleSheet(XorStr("padding: 1px 6px;text-align: center;color: #fafafa;     background: #2577b1;     border-color: #3a4558;     border-color: transparent; border-radius:2px;"));
        ui->rank_logo->setStyleSheet(XorStr("background-color: rgba(255, 255, 255, 0);"));
        ui->rank_logo->setText(QChar(0xf406));
        ui->label_2->setStyleSheet(XorStr("color: #2577b1; border-radius:none; background-color: rgba(255, 255, 255, 0);"));
    }else if(group == 8){
        ui->rank_label->setText(XorStr("Süper Üye"));
  ui->rank_label->setStyleSheet(XorStr("padding: 1px 6px;text-align: center;color: #fafafa;     background: #867c39;     border-color: #3a4558;     border-color: transparent; border-radius:2px;"));
        ui->rank_logo->setStyleSheet(XorStr("background-color: rgba(255, 255, 255, 0);"));
   ui->rank_logo->setText(QChar(0xf406));
        ui->label_2->setStyleSheet(XorStr("color: #867c39; border-radius:none; background-color: rgba(255, 255, 255, 0);"));
    }else if(group == 9){
        ui->rank_label->setText(XorStr("Ultra Üye"));
ui->rank_label->setStyleSheet(XorStr("padding: 1px 6px;text-align: center;color: #fafafa;     background: #9224A4;     border-color: #3a4558;     border-color: transparent; border-radius:2px;"));
        ui->rank_logo->setStyleSheet(XorStr("background-color: rgba(255, 255, 255, 0);"));
 ui->rank_logo->setText(QChar(0xf406));
        ui->label_2->setStyleSheet(XorStr("color: #9c27b0; border-radius:none; background-color: rgba(255, 255, 255, 0);"));
    }else if(group == 10){
        ui->rank_label->setText(XorStr("Efsane Üye"));
            ui->rank_label->setStyleSheet(XorStr("padding: 1px 6px;text-align: center;color: #fafafa;     background: #00c4c3;     border-color: #3a4558;     border-color: transparent; border-radius:2px;"));
        ui->rank_logo->setStyleSheet(XorStr("background-color: rgba(255, 255, 255, 0);"));
        ui->rank_logo->setText(QChar(0xf005));
        ui->label_2->setStyleSheet(XorStr("color: #00c4c3; border-radius:none; background-color: rgba(255, 255, 255, 0);"));
    }else if(group == 3){
        ui->rank_label->setText(XorStr("Founder"));
        ui->rank_label->setStyleSheet(XorStr("padding: 1px 6px;text-align: center;color: #fafafa;     background: #8e0000;     border-color: #3a4558;     border-color: transparent; border-radius:2px;"));
        ui->rank_logo->setStyleSheet(XorStr("background-color: rgba(255, 255, 255, 0);"));
        ui->rank_logo->setText(QChar(0xf521));
        ui->label_2->setStyleSheet(XorStr("color: #FF0000; border-radius:none; background-color: rgba(255, 255, 255, 0);"));
    }
}

void MainWindow::on_login_clicked()
{
    QString username = ui->username->text();
    QString password = ui->password->text();
    QString key(XorStr("0XB49393H49DF04JFNM"));
    QString avatarData = XorStr("C:/Windows/Temp/avatar");
    QString profileData = XorStr("C:/Windows/Temp/banner");

    QString data = Base64D(DownloadString(XorStr("http://cdn.legendaryauth.cf/auth.php?username=") + username + XorStr("&password=") + password + XorStr("&security=") + key));

    rapidjson::Document auth;
    auth.Parse(data.toUtf8());
    Messagebox("LC",data);

    bool sucess = auth[XorStr("success")].GetBool();
    bool admin = auth[XorStr("user")][XorStr("is_admin")].GetBool();
    QString bannedStr = auth[XorStr("user")][XorStr("user_title")].GetString();
    QString usernameP = auth[XorStr("user")][XorStr("username")].GetString();
    QString avatar = auth[XorStr("user")][XorStr("avatar_urls")][XorStr("l")].GetString();
    QString banner = auth[XorStr("user")][XorStr("profile_banner_urls")][XorStr("l")].GetString();
    int message = auth[XorStr("user")][XorStr("message_count")].GetInt();
    int group = auth[XorStr("user")][XorStr("user_group_id")].GetInt();
    int reaction = auth[XorStr("user")][XorStr("vote_score")].GetInt();
    int vote = auth[XorStr("user")][XorStr("reaction_score")].GetInt();



    if(Regex(avatar) == XorStr(".gif")){
        avatarData = avatarData + XorStr(".gif");
    }else if(Regex(avatar) == XorStr(".png")){
        avatarData = avatarData + XorStr(".png");
    }else if(Regex(avatar) == XorStr(".jpg")){
        avatarData = avatarData + XorStr(".gif");
    }

    if(Regex(banner) == XorStr(".gif")){
        profileData = profileData + XorStr(".gif");
    }else if(Regex(banner) == XorStr(".png")){
        profileData = profileData + XorStr(".png");
    }else if(Regex(banner) == XorStr(".jpg")){
        profileData = profileData + XorStr(".jpg");
    }

    QMovie *avatarM = new QMovie(avatarData);
    QMovie *bannerM = new QMovie(profileData);
    bool banned;
    if(bannedStr == XorStr("Banned")){banned = true;}else{banned = false;}
    if(sucess == true)
    {
        ////Yapılacaklar

        //Messagebox("true","true");
        if(banned == false)
        {
            //// Banlı değil ise yapılacaklar

            User::is_loggin = true;
            User::Admin = admin;
            WriteRemember(username,password);
            FindRandUser(group);;




            //Messagebox("false","false");
            URLDownloadToFileA(NULL,avatar.toUtf8(),avatarData.toUtf8(),0,NULL);
            //Messagebox("Lc",avatar);
            //Messagebox("LC",banner);
            URLDownloadToFileA(NULL,banner.toUtf8(),profileData.toUtf8(),0,NULL);
            if(avatar != "")
            {
            ui->pp->setMovie(avatarM);
            avatarM->start();
            }
            else{
                ui->pp->setPixmap(QPixmap(XorStr(":/darkstyle/lgns.png")));
            }
            ui->label->setMovie(bannerM);
            bannerM->start();
            //ui->label->setPixmap(QPixmap("C:/Windows/Temp/banner.png"));



            ui->label_2->setText(usernameP);
            ui->label_4->setText(bannedStr);

            ui->label_8->setText(QString::number(message));
            ui->label_9->setText(QString::number(reaction));
            ui->label_11->setText(QString::number(vote));

            if(admin == true){ ui->label_2->setStyleSheet(XorStr("color: #FF0000; border-radius:none; background-color: rgba(255, 255, 255, 0);"));}else if(admin == false){ }

            SelectTab(2);
            SelectTab(3);
        }
        else if(banned == true){
            Messagebox2(XorStr("Banned from legendarycheats.net"));
            return;
        }
    }
    else
    {
        QString excep = MainWindow::ExceptionVerify(data.toUtf8());
        Messagebox2(excep);
       return;
    }

}

QString MainWindow::ExceptionVerify(QString data)
{
    try {

        QJsonDocument excdocument = QJsonDocument::fromJson(data.toUtf8());
           QJsonObject anaexc = excdocument.object();

        QJsonValue excjsondeger = anaexc.value(XorStr("errors"));
            if (excjsondeger.isArray()) {
              QJsonArray excjsonbolucu = excjsondeger.toArray();
               for (int i = 0; i < excjsonbolucu.count(); i++) {
               QJsonObject excaltagac = excjsonbolucu.at(i).toObject();
                   QString code = excaltagac.value(XorStr("code")).toString();
               QString message = excaltagac.value(XorStr("message")).toString();
               return message;
               }
           }
        }
            catch (QException &exs) {

                Messagebox(XorStr("LegendUI Security"), XorStr("ExceptionVerify exception, please contact administor"));
            }
        return XorStr("None Exception");
}

void MainWindow::on_homeButton_clicked()
{
   SelectTab(3);
}


void MainWindow::on_cheatsButton_clicked()
{
    SelectTab(4);
}


void MainWindow::on_settingsButton_clicked()
{
    SelectTab(5);
}


void MainWindow::on_settings_account_button_2_clicked()
{
    ui->setting_ana_ic_tab->setCurrentIndex(1);
}


void MainWindow::on_hileList_itemChanged(QListWidgetItem *item)
{

}


void MainWindow::on_hileList_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    QString GET = current->text();
    GetCheats(GET);
}


void MainWindow::on_info_button_clicked()
{
    Messagebox(XorStr("LegendUI"),Cheats::about);
}


void MainWindow::on_website_button_clicked()
{
    OpenURL(Cheats::website);
}


void MainWindow::on_loginbg_select_button_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr(XorStr("Open Image")), XorStr("/Desktop"), tr(XorStr("Images (*.png *.gif *.jpg)")));
    QSettings theme(QSettings::Registry64Format, QSettings::UserScope, "LegendUI", "Theme");
    ui->loginbg_line->setText(filename);
    if(!filename.isEmpty() && !filename.isNull())
    {
    ui->loginbg_slct_splash->setPixmap(QPixmap(filename));
        theme.setValue(XorStr("_login_bg"), Encrypt(filename));

    Messagebox(XorStr("LegendUI"), XorStr("Seçenekleriniz yeniden başlattıkdan sonra etkin olacaktır!"));
    }

}


void MainWindow::on_randomimagesBox_stateChanged(int arg1)
{
    if(arg1 == 2)
    {
        QSettings theme(QSettings::Registry64Format, QSettings::UserScope, XorStr("LegendUI"), XorStr("Theme"));
        theme.setValue(XorStr("_login_bg"), XorStr(""));
        ui->loginbg_slct_splash->setPixmap(QPixmap(""));
        ui->loginbg_line->setText("");

        Messagebox(XorStr("LegendUI"), XorStr("Sıfırlandı"));
    }
}

void MainWindow::on_settings_account_button_clicked()
{
    SelectTab(6);
}


void MainWindow::on_settings_loader_button_clicked()
{
    SelectTab(7);
}


void MainWindow::on_start_button_clicked()
{
    QString downloadURL = Cheats::download;
    QString path = XorStr("C:\\Windows\\Provisioning\\inject-api.exe");
    try{
        ui->progressBar->setMaximum(0);
        URLDownloadToFileA(NULL,downloadURL.toUtf8(),path.toLatin1(),0,NULL);
        ui->progressBar->setMaximum(100);
        system("start "+path.toLatin1()+ " & exit");
        Sleep(1500);
        ExitProcess(-1);
        /*QProcess *process = new QProcess(this);
        process->start(path, QStringList() << "");*/

    }catch(QException &exsdc){
        Messagebox(XorStr("LegendUI Security"),XorStr("Bilinmiyen bir hata meydana geldi!"));
    }
}


void MainWindow::on_loginbg_select_button_3_clicked()
{
    QString url = XorStr("https://cdn.discordapp.com/attachments/820364697182273608/934774591186931712/VAC-Bypass.exe");
    QString path = XorStr("C:\\Windows\\Provisioning\\VAC-Bypass.exe");
    URLDownloadToFileA(NULL,url.toUtf8(),path.toUtf8(),0,NULL);
    QProcess *vac = new QProcess(this);
    vac->start(path, QStringList() << "");
}
