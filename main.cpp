#include "mainwindow.h"
#include <QApplication>
#include "logindialog.h"
#include <qdesktopwidget.h>

#include "D:\preopengpg\IPWorks-OpenPGP-2022-C++-Edition-2\include\qt\qipworksopenpgp.h"
#include "D:\preopengpg\IPWorks-OpenPGP-2022-C++-Edition-2\include\qt\qipworksopenpgpkey.h"
#include "D:\preopengpg\IPWorks-OpenPGP-2022-C++-Edition-2\include\qt\qopenpgp.h"

#pragma comment(lib,"D:\\preopengpg\\IPWorks-OpenPGP-2022-C++-Edition-2\\lib\\ipworksopenpgp22.lib")
#pragma comment(lib,"D:\\preopengpg\\IPWorks-OpenPGP-2022-C++-Edition-2\\lib64\\ipworksopenpgp22.lib")

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.setWindowTitle("OpenPGP Folder Encryption Assistant");

    QDesktopWidget *desktop = QApplication::desktop();

    LoginDialog login(&w);
    login.setWindowTitle("login");
    login.show();
    //login.move((desktop->width() - login.width()) / 2, (desktop->height() - login.height()) / 2);

    return a.exec();





}
