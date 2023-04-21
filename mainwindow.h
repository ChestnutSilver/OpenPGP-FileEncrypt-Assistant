#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "D:\preopengpg\IPWorks-OpenPGP-2022-C++-Edition-2\include\qt\qipworksopenpgp.h"
#include "D:\preopengpg\IPWorks-OpenPGP-2022-C++-Edition-2\include\qt\qipworksopenpgpkey.h"
#include "D:\preopengpg\IPWorks-OpenPGP-2022-C++-Edition-2\include\qt\qopenpgp.h"

#pragma comment(lib,"D:\\preopengpg\\IPWorks-OpenPGP-2022-C++-Edition-2\\lib\\ipworksopenpgp22.lib")
#pragma comment(lib,"D:\\preopengpg\\IPWorks-OpenPGP-2022-C++-Edition-2\\lib64\\ipworksopenpgp22.lib")

#include <vector>
#include <Windows.h>
#include <iostream>
using namespace std;



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void mainProcess();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
    string mykeyringdir;
    string aid;
    string apwd;
    QByteArray res;

    string aidSingle;
    string apwdSingle;
    string recipSingle;
    string signSingle;

    string inputfilepathEncryptSingle;

    string aidMultiple;
    string apwdMultiple;
    string recipMultiple;
    string signMultiple;





};

#endif // MAINWINDOW_H
