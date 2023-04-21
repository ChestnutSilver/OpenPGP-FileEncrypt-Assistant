#include "mainwindow.h"
#include "ui_mainwindow.h"

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "D:\preopengpg\IPWorks-OpenPGP-2022-C++-Edition-2\include\qt\qopenpgp.h"
#include "D:\preopengpg\IPWorks-OpenPGP-2022-C++-Edition-2\include\qt\qipworksopenpgp.h"
#include "D:\preopengpg\IPWorks-OpenPGP-2022-C++-Edition-2\include\qt\qipworksopenpgpkey.h"

#pragma comment(lib,"D:\\preopengpg\\IPWorks-OpenPGP-2022-C++-Edition-2\\lib\\ipworksopenpgp22.lib")
#pragma comment(lib,"D:\\preopengpg\\IPWorks-OpenPGP-2022-C++-Edition-2\\lib64\\ipworksopenpgp22.lib")


#include <vector>
#include <Windows.h>
#include <iostream>
using namespace std;

#include "user.h"
#include "global.h"
#include "KeyManage.h"
#include "ModeManage.h"
#include "sddl.h"
#include "filemanage.h"
#include <sstream>
#include <QScrollBar>
#include <QLineEdit>
#include <QLabel>
#define LINE_LEN 100

//用来打印信息的函数，方便不同环境下的修改
void WriteLine(string console)
{
    std::cout << console << endl;
}

//wchar_t变量转换为szDst
string WcharToString(wchar_t wText[])
{
    std::string szDst;
    DWORD dwNum = WideCharToMultiByte(CP_OEMCP, NULL, wText, -1, NULL, 0, NULL, FALSE);
    char* psText;
    psText = new char[dwNum];
    WideCharToMultiByte(CP_OEMCP, NULL, wText, -1, psText, dwNum, NULL, FALSE);
    szDst = psText;
    delete[]psText;

    return szDst;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    mainProcess();

    QPixmap Images("C:\\Users\\lenovo\\Desktop\\mainbkg2.png");
    QPalette Palette = this->palette();
    Palette.setBrush(QPalette::Background, Images);
    this->setPalette(Palette);

    //QTextBrowser#textBrowser
    ui->textBrowser->setStyleSheet(
    "QTextBrowser{"
        "border:1px solid transparent;"
        "border-radius:2px;"
        "color: white;"
        "background-color: rgba(22,99,138,50%);"
        "border-color: rgba(0,156,255,50%);"
        "font-size: 14px;"
        "font-weight: 400;"
        "selection-background-color: #8c8c8c;"
        "selection-color:#e6e6e6;"
        "padding-left:6px;"
        "padding-right:6px;"
    "}"

    "QScrollBar:vertical{"
        "border: none;"
        "background: transparent;"
        "width: 6px;"
    "}"
    );

    ui->textBrowser_2->setStyleSheet(
    "QTextBrowser{"
        "border:1px solid transparent;"
        "border-radius:2px;"
        "color: white;"
        "background-color: rgba(22,99,138,50%);"
        "border-color: rgba(0,156,255,50%);"
        "font-size: 14px;"
        "font-weight: 400;"
        "selection-background-color: #8c8c8c;"
        "selection-color:#e6e6e6;"
        "padding-left:6px;"
        "padding-right:6px;"
    "}"

    "QScrollBar:vertical{"
        "border: none;"
        "background: transparent;"
        "width: 6px;"
    "}"
    );

    ui->textBrowser_3->setStyleSheet(
    "QTextBrowser{"
        "border:1px solid transparent;"
        "border-radius:2px;"
        "color: white;"
        "background-color: rgba(22,99,138,50%);"
        "border-color: rgba(0,156,255,50%);"
        "font-size: 14px;"
        "font-weight: 400;"
        "selection-background-color: #8c8c8c;"
        "selection-color:#e6e6e6;"
        "padding-left:6px;"
        "padding-right:6px;"
    "}"

    "QScrollBar:vertical{"
        "border: none;"
        "background: transparent;"
        "width: 6px;"
    "}"
    );

    ui->lineEdit->setStyleSheet(
    "QLineEdit{"
        "border:1px solid transparent;"
        "border-radius:2px;"
        "color: white;"
        "background-color: rgba(22,99,138,50%);"
        "border-color: rgba(0,156,255,50%);"
        "font-size: 14px;"
        "font-weight: 400;"
        "selection-background-color: #8c8c8c;"
        "selection-color:#e6e6e6;"
        "padding-left:6px;"
        "padding-right:6px;"
    "}"
    );

    ui->lineEdit_2->setStyleSheet(
    "QLineEdit{"
        "border:1px solid transparent;"
        "border-radius:2px;"
        "color: white;"
        "background-color: rgba(22,99,138,50%);"
        "border-color: rgba(0,156,255,50%);"
        "font-size: 14px;"
        "font-weight: 400;"
        "selection-background-color: #8c8c8c;"
        "selection-color:#e6e6e6;"
        "padding-left:6px;"
        "padding-right:6px;"
    "}"
    );

    ui->lineEdit_3->setStyleSheet(
    "QLineEdit{"
        "border:1px solid transparent;"
        "border-radius:2px;"
        "color: white;"
        "background-color: rgba(22,99,138,50%);"
        "border-color: rgba(0,156,255,50%);"
        "font-size: 14px;"
        "font-weight: 400;"
        "selection-background-color: #8c8c8c;"
        "selection-color:#e6e6e6;"
        "padding-left:6px;"
        "padding-right:6px;"
    "}"
    );

    ui->lineEdit_4->setStyleSheet(
    "QLineEdit{"
        "border:1px solid transparent;"
        "border-radius:2px;"
        "color: white;"
        "background-color: rgba(22,99,138,50%);"
        "border-color: rgba(0,156,255,50%);"
        "font-size: 14px;"
        "font-weight: 400;"
        "selection-background-color: #8c8c8c;"
        "selection-color:#e6e6e6;"
        "padding-left:6px;"
        "padding-right:6px;"
    "}"
    );

    ui->lineEdit_5->setStyleSheet(
    "QLineEdit{"
        "border:1px solid transparent;"
        "border-radius:2px;"
        "color: white;"
        "background-color: rgba(22,99,138,50%);"
        "border-color: rgba(0,156,255,50%);"
        "font-size: 14px;"
        "font-weight: 400;"
        "selection-background-color: #8c8c8c;"
        "selection-color:#e6e6e6;"
        "padding-left:6px;"
        "padding-right:6px;"
    "}"
    );

    ui->lineEdit_6->setStyleSheet(
    "QLineEdit{"
        "border:1px solid transparent;"
        "border-radius:2px;"
        "color: white;"
        "background-color: rgba(22,99,138,50%);"
        "border-color: rgba(0,156,255,50%);"
        "font-size: 14px;"
        "font-weight: 400;"
        "selection-background-color: #8c8c8c;"
        "selection-color:#e6e6e6;"
        "padding-left:6px;"
        "padding-right:6px;"
    "}"
    );

    ui->lineEdit_7->setStyleSheet(
    "QLineEdit{"
        "border:1px solid transparent;"
        "border-radius:2px;"
        "color: white;"
        "background-color: rgba(22,99,138,50%);"
        "border-color: rgba(0,156,255,50%);"
        "font-size: 14px;"
        "font-weight: 400;"
        "selection-background-color: #8c8c8c;"
        "selection-color:#e6e6e6;"
        "padding-left:6px;"
        "padding-right:6px;"
    "}"
    );

    ui->lineEdit_8->setStyleSheet(
    "QLineEdit{"
        "border:1px solid transparent;"
        "border-radius:2px;"
        "color: white;"
        "background-color: rgba(22,99,138,50%);"
        "border-color: rgba(0,156,255,50%);"
        "font-size: 14px;"
        "font-weight: 400;"
        "selection-background-color: #8c8c8c;"
        "selection-color:#e6e6e6;"
        "padding-left:6px;"
        "padding-right:6px;"
    "}"
    );

    ui->lineEdit_9->setStyleSheet(
    "QLineEdit{"
        "border:1px solid transparent;"
        "border-radius:2px;"
        "color: white;"
        "background-color: rgba(22,99,138,50%);"
        "border-color: rgba(0,156,255,50%);"
        "font-size: 14px;"
        "font-weight: 400;"
        "selection-background-color: #8c8c8c;"
        "selection-color:#e6e6e6;"
        "padding-left:6px;"
        "padding-right:6px;"
    "}"
    );

    ui->lineEdit_10->setStyleSheet(
    "QLineEdit{"
        "border:1px solid transparent;"
        "border-radius:2px;"
        "color: white;"
        "background-color: rgba(22,99,138,50%);"
        "border-color: rgba(0,156,255,50%);"
        "font-size: 14px;"
        "font-weight: 400;"
        "selection-background-color: #8c8c8c;"
        "selection-color:#e6e6e6;"
        "padding-left:6px;"
        "padding-right:6px;"
    "}"
    );

    ui->label->setStyleSheet(
    "QLabel{"
        "color: white;"
        "font-family: SimHei;"
    "}"
    );
    ui->label_2->setStyleSheet(
    "QLabel{"
        "color: white;"
        "font-family: SimHei;"
    "}"
    );
    ui->label_3->setStyleSheet(
    "QLabel{"
        "color: white;"
        "font-family: SimHei;"
    "}"
    );
    ui->label_4->setStyleSheet(
    "QLabel{"
        "color: white;"
        "font-family: SimHei;"
    "}"
    );
    ui->label_5->setStyleSheet(
    "QLabel{"
        "color: white;"
        "font-family: SimHei;"
    "}"
    );
    ui->label_6->setStyleSheet(
    "QLabel{"
        "color: white;"
        "font-family: SimHei;"
    "}"
    );
    ui->label_7->setStyleSheet(
    "QLabel{"
        "color: white;"
        "font-family: SimHei;"
    "}"
    );
    ui->label_8->setStyleSheet(
    "QLabel{"
        "color: white;"
        "font-family: SimHei;"
    "}"
    );
    ui->label_9->setStyleSheet(
    "QLabel{"
        "color: white;"
        "font-family: SimHei;"
    "}"
    );
    ui->label_10->setStyleSheet(
    "QLabel{"
        "color: white;"
        "font-family: SimHei;"
    "}"
    );
    ui->label_11->setStyleSheet(
    "QLabel{"
        "color: white;"
        "font-family: SimHei;"
    "}"
    );
    ui->label_12->setStyleSheet(
    "QLabel{"
        "color: white;"
        "font-family: SimHei;"
    "}"
    );
    ui->label_13->setStyleSheet(
    "QLabel{"
        "color: white;"
        "font-family: SimHei;"
    "}"
    );
    ui->label_14->setStyleSheet(
    "QLabel{"
        "color: white;"
        "font-family: SimHei;"
    "}"
    );
    ui->label_15->setStyleSheet(
    "QLabel{"
        "color: white;"
        "font-family: SimHei;"
    "}"
    );
    ui->label_16->setStyleSheet(
    "QLabel{"
        "color: white;"
        "font-family: SimHei;"
    "}"
    );

    ui->pushButton->setStyleSheet(
        //正常状态样式
        "QPushButton{"
        "background-color:rgb(179,179,255);"//设置按钮背景色
        "border-radius:5px;"//设置圆角半径
        "color:white;"//设置按钮字体颜色
        "font-family: SimHei;"
        "font-size: 9pt;"
        "}"

        //鼠标悬停样式
        "QPushButton:hover{"
        "background-color:#5f9ae6;"
        "color:white;"
        "}"

        //按钮按下样式
        "QPushButton:pressed{"
        /*背景颜色*/
        "background-color:rgb(14,145,208);"
        /*左内边距为3像素，让按下时字向右移动3像素*/
        "padding-left:3px;"
        /*上内边距为3像素，让按下时字向下移动3像素*/
        "padding-top:3px;"
        "}"
        );

    ui->pushButton_2->setStyleSheet(
        //正常状态样式
        "QPushButton{"
        "background-color:rgb(153,153,255);"//设置按钮背景色
        "border-radius:5px;"//设置圆角半径
        "color:white;"//设置按钮字体颜色
        "font-family: SimHei;"
        "font-size: 9pt;"
        "}"

        //鼠标悬停样式
        "QPushButton:hover{"
        "background-color:#5f9ae6;"
        "color:white;"
        "}"

        //按钮按下样式
        "QPushButton:pressed{"
        /*背景颜色*/
        "background-color:rgb(14,145,208);"
        /*左内边距为3像素，让按下时字向右移动3像素*/
        "padding-left:3px;"
        /*上内边距为3像素，让按下时字向下移动3像素*/
        "padding-top:3px;"
        "}"
        );

    ui->pushButton_3->setStyleSheet(
        //正常状态样式
        "QPushButton{"
        "background-color:rgb(102,102,255);"//设置按钮背景色
        "border-radius:5px;"//设置圆角半径
        "color:white;"//设置按钮字体颜色
        "font-family: SimHei;"
        "font-size: 9pt;"
        "}"

        //鼠标悬停样式
        "QPushButton:hover{"
        "background-color:#5f9ae6;"
        "color:white;"
        "}"

        //按钮按下样式
        "QPushButton:pressed{"
        /*背景颜色*/
        "background-color:rgb(14,145,208);"
        /*左内边距为3像素，让按下时字向右移动3像素*/
        "padding-left:3px;"
        /*上内边距为3像素，让按下时字向下移动3像素*/
        "padding-top:3px;"
        "}"
        );

    ui->pushButton_4->setStyleSheet(
        //正常状态样式
        "QPushButton{"
        "background-color:rgb(77,77,255);"//设置按钮背景色
        "border-radius:5px;"//设置圆角半径
        "color:white;"//设置按钮字体颜色
        "font-family: SimHei;"
        "font-size: 9pt;"
        "}"

        //鼠标悬停样式
        "QPushButton:hover{"
        "background-color:#5f9ae6;"
        "color:white;"
        "}"

        //按钮按下样式
        "QPushButton:pressed{"
        /*背景颜色*/
        "background-color:rgb(14,145,208);"
        /*左内边距为3像素，让按下时字向右移动3像素*/
        "padding-left:3px;"
        /*上内边距为3像素，让按下时字向下移动3像素*/
        "padding-top:3px;"
        "}"
        );


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::mainProcess()
{


}

void MainWindow::on_pushButton_clicked()
{
    //展示文件夹创建
    Global global;

    //用户创建
    User user;
    string userID = user.getUserID();

    //密钥生成和导出

    KeyManage keyManage;
    keyManage.init(global, user);

    //密码唯一，且由用户的用户名和安全序列号唯一生成
    string pwd = ToString(hash<string>{}(user.getUsername()) ^ hash<PVOID>{}(user.getStringSid()));

    keyManage.GenerateKeyPairRSA(userID, pwd);
    keyManage.ExportPublicKey(userID, pwd);
    keyManage.ExportPrivateKey(userID, pwd);//私钥敏感信息不能导出
    keyManage.KeyStoreListKeys(pwd);

    QString tbu, tbp;
    tbu = QString::fromStdString(userID);
    tbp = QString::fromStdString(pwd);
    ui->textBrowser_3->setText("Key has been generated! The UserID is: " + tbu + ", The pwd is: " + tbp);

    //模式选择：原理展示/存储模式/调阅模式
    //用户界面
    while (true)
    {
        ModeManage modeManage;
        int Mode = modeManage.modeInput(global, user);
        Mode = 1;
        //modeManage.modeControl(Mode, user, pwd);
        //modeManage.modeControl(Mode, user, pwd);

        OpenPGP pgp;
        MyKeyMgr keymgr;
        int ret_code = 0;
        char command[LINE_LEN];     // user's command
        char mykeyringDir[LINE_LEN];
        char passphrase[LINE_LEN];
        char privateKey[LINE_LEN];
        char recipientKey[LINE_LEN];
        char signerKey[LINE_LEN];


        QString tempmykeyringdir = ui->lineEdit->text();
        mykeyringdir = tempmykeyringdir.toStdString();
        //string mykeyringdir="D:\\OpenPGP_File_Manage_show\\lenovo\\Key\\key-store";

        QString aidtemp = ui->lineEdit_2->text();
        aid = aidtemp.toStdString();
        QString apwdtemp = ui->lineEdit_3->text();
        apwd = apwdtemp.toStdString();

        strcpy(mykeyringDir,mykeyringdir.c_str());
        strcpy(passphrase,apwd.c_str());
        strcpy(privateKey,aid.c_str());
        strcpy(recipientKey,aid.c_str());
        strcpy(signerKey,aid.c_str());


    /*
        printf("Keyring Directory: ");
        fgets(mykeyringDir, LINE_LEN, stdin);
        fgets(mykeyringDir, LINE_LEN, stdin);
        mykeyringDir[strlen(mykeyringDir) - 1] = '\0';
        keymgr.LoadKeyring(mykeyringDir);

        printf("\nPrivate Key User Id (Used to sign outgoing messages and decrypt incoming messages): ");
        fgets(privateKey, LINE_LEN, stdin);
        privateKey[strlen(privateKey) - 1] = '\0';
        printf("Passphrase: ");
        fgets(passphrase, LINE_LEN, stdin);
        passphrase[strlen(passphrase) - 1] = '\0';
        printf("Recipient Key User Id (Used to encrypt outgoing messages): ");
        fgets(recipientKey, LINE_LEN, stdin);
        recipientKey[strlen(recipientKey) - 1] = '\0';
        printf("Signer Key User Id (Used to verify the signature of an incoming message): ");
        fgets(signerKey, LINE_LEN, stdin);
        signerKey[strlen(signerKey) - 1] = '\0';
    */
        while (1)
        {
            pgp.Reset();

            printf("Please enter the message. When finished enter \":q\" on a line by itself:\n");
            char message[100];
            string msg;
            msg = "this is the original message";
            strcpy(message,msg.c_str());

            /*
            message[0] = '\0';
            while (fgets(command, LINE_LEN, stdin))
            {
                command[strlen(command) - 1] = '\0';
                if (strcmp(command, ":q") == 0)
                    break;
                strcat(message, command);
                strcat(message, "\n");
            }
            */
            pgp.SetInputMessage(message);


            if (strlen(privateKey) <= 0)
            {
                printf("Please select a private key.\n");
                break;
            }
            if (strlen(recipientKey) <= 0)
            {
                printf("Please select a recipient key.\n");
                break;
            }
            if (strlen(signerKey) <= 0)
            {
                printf("Please select a signer key.\n");
                break;
            }

            pgp.SetASCIIArmor(false);
            pgp.SetKeyCount(1);
            pgp.SetKeyKeyring(0, mykeyringDir);
            pgp.SetKeyUserId(0, privateKey);
            pgp.SetKeyPassphrase(0, passphrase);
            pgp.SetRecipientKeyCount(1);
            pgp.SetRecipientKeyKeyring(0, mykeyringDir);
            pgp.SetRecipientKeyUserId(0, recipientKey);

            string outputfilepath = "D:\\OpenPGP_File_Manage_show\\lenovo\\File\\" + userID + "Encrypted.gpg";
            QString Qoutputfilepath = QString::fromStdString(outputfilepath);
            pgp.SetOutputFile(Qoutputfilepath);
            ret_code = pgp.SignAndEncrypt();
            if (ret_code) goto done;

            pgp.SetASCIIArmor(true);
            string outputfilepathASCII = "D:\\OpenPGP_File_Manage_show\\lenovo\\File\\" + userID + "ASCIIEncrypted.gpg";
            QString QoutputfilepathASCII = QString::fromStdString(outputfilepathASCII);
            pgp.SetOutputFile(QoutputfilepathASCII);
            ret_code = pgp.SignAndEncrypt();

            //if (strlen(pgp.GetOutputFile()) <= 0)
            {
                printf("\nSigned & Encrypted Message:\n");
                //char* output;
                //int len;
                res = pgp.GetOutputMessage();


                //pgp.GetOutputMessage();
                //printf("%s\n", output);

                //output[strlen(output) - 1] = '\0';
                //pgp.SetInputMessage(output);

                //Output = output;
            }

            QString data;
            QFile file(QoutputfilepathASCII); //path是文件的路径
            if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                qDebug()<<"文件未打开!";
            }
            while(!file.atEnd())
            {
                QByteArray array = file.readLine();
                QString str(array);
               // qDebug()<< str;
                data.append(str);
            }
            ui->textBrowser->setText(data);

            //解密
            pgp.SetInputFile(Qoutputfilepath);
            pgp.SetKeyCount(1);
            pgp.SetKeyKeyring(0, mykeyringDir);
            pgp.SetKeyUserId(0, privateKey);
            pgp.SetKeyPassphrase(0, passphrase);
            pgp.SetSignerKeyCount(1);
            pgp.SetSignerKeyKeyring(0, mykeyringDir);
            pgp.SetSignerKeyUserId(0, signerKey);

            string outputfilepathDecrypt = "D:\\OpenPGP_File_Manage_show\\lenovo\\File\\" + userID + "Decrypted.txt";
            QString QoutputfilepathDecrypt = QString::fromStdString(outputfilepathDecrypt);
            pgp.SetOutputFile(QoutputfilepathDecrypt);

            ret_code = pgp.DecryptAndVerifySignature();
            if (ret_code) goto done;

            //if (strlen(pgp.GetOutputFile()) <= 0)
            {
                printf("\nDecrypted & Verified Message:\n");
                pgp.GetOutputMessage();
            }

            QString dataDecrypt;
            QFile fileDecrypt(QoutputfilepathDecrypt); //path是文件的路径
            if(!fileDecrypt.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                qDebug()<<"文件未打开!";
            }
            while(!fileDecrypt.atEnd())
            {
                QByteArray array = fileDecrypt.readLine();
                QString str(array);
               // qDebug() << str;
                dataDecrypt.append(str);
            }
            ui->textBrowser_2->setText(dataDecrypt);

            break;
        }

    done:
        if (ret_code)     // Got an error.  The user is done.
        {
            printf("\nError: %d", ret_code);
            ui->textBrowser->setText(pgp.GetLastError());
            //if (pgp.GetLastError())
            //{
            //    printf(" \"%s\"\n", pgp.GetLastError());
            //}
        }


        WriteLine("程序已结束，按q退出，按其他任意键返回用户界面...");
        string quit;
        quit = "q";
        //cin >> quit;
        if (quit == "q")
            break;
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    //展示文件夹创建
    Global global;

    //用户创建
    User user;
    string userID = user.getUserID();

    //密钥生成和导出

    KeyManage keyManage;
    keyManage.init(global, user);

    //密码唯一，且由用户的用户名和安全序列号唯一生成
    string pwd = ToString(hash<string>{}(user.getUsername()) ^ hash<PVOID>{}(user.getStringSid()));

    keyManage.GenerateKeyPairRSA(userID, pwd);
    keyManage.ExportPublicKey(userID, pwd);
    keyManage.ExportPrivateKey(userID, pwd);//私钥敏感信息不能导出
    keyManage.KeyStoreListKeys(pwd);

    QString tbu, tbp;
    tbu = QString::fromStdString(userID);
    tbp = QString::fromStdString(pwd);
    ui->textBrowser_3->setText("Key has been generated! The UserID is: " + tbu + ", The pwd is: " + tbp);


    //模式选择：原理展示/存储模式/调阅模式
    //用户界面
    while (true)
    {
        ModeManage modeManage;
        int Mode = modeManage.modeInput(global, user);
        Mode = 21;
        //modeManage.modeControl(Mode, user, pwd);
        //modeManage.modeControl(Mode, user, pwd);

        string keyringDir = conbineStrings(global.pathStringKey, "key-store");

        string newFile = ToString(userID) + "EncryptedSingle.gpg"; //生成文件名为 userID + Encrypted.gpg
        string outputFile = conbineStrings(global.pathStringFile, newFile);

        char mykeyringDir[LINE_LEN];
        char passphrase[LINE_LEN];
        char privateKey[LINE_LEN];
        char recipientKey[LINE_LEN];
        char signerKey[LINE_LEN];

        QString tempmykeyringdir = ui->lineEdit->text();
        mykeyringdir = tempmykeyringdir.toStdString();
        //string mykeyringdir="D:\\OpenPGP_File_Manage_show\\lenovo\\Key\\key-store";

        QString aidtempSingle = ui->lineEdit_2->text();
        aidSingle = aidtempSingle.toStdString();
        QString apwdtempSingle = ui->lineEdit_3->text();
        apwdSingle = apwdtempSingle.toStdString();

        QString reciptempSingle = ui->lineEdit_4->text();
        recipSingle = reciptempSingle.toStdString();
        QString signtempSingle = ui->lineEdit_5->text();
        signSingle = signtempSingle.toStdString();

        strcpy(mykeyringDir,mykeyringdir.c_str());
        strcpy(passphrase,apwdSingle.c_str());
        strcpy(privateKey,aidSingle.c_str());
        strcpy(recipientKey,recipSingle.c_str());
        strcpy(signerKey,signSingle.c_str());


    /*
        printf("\nPrivate Key User Id (Used to sign outgoing messages and decrypt incoming messages): ");
        fgets(privateKey, LINE_LEN, stdin);
        privateKey[strlen(privateKey) - 1] = '\0';
        printf("Passphrase: ");
        fgets(passphrase, LINE_LEN, stdin);
        passphrase[strlen(passphrase) - 1] = '\0';
        printf("Recipient Key User Id (Used to encrypt outgoing messages): ");
        fgets(recipientKey, LINE_LEN, stdin);
        recipientKey[strlen(recipientKey) - 1] = '\0';
        printf("Signer Key User Id (Used to verify the signature of an incoming message): ");
        fgets(signerKey, LINE_LEN, stdin);
        signerKey[strlen(signerKey) - 1] = '\0';
    */
        //modeUserIDPwd.modeUserID = privateKey;
        //modeUserIDPwd.modePwd = passphrase;

        char inFileEncryptSingle[LINE_LEN];
        QString QinputfilepathEncryptSingle = ui->lineEdit_10->text();
        inputfilepathEncryptSingle = QinputfilepathEncryptSingle.toStdString();


        QString QoutputfilepathEncryptSingle = QString::fromStdString(outputFile);

        OpenPGP pgp;

        size_t size = inputfilepathEncryptSingle.length();
        std::vector<wchar_t> buffer(inputfilepathEncryptSingle.size() + 1);
        MultiByteToWideChar(CP_ACP, 0, inputfilepathEncryptSingle.c_str(), -1, buffer.data(), static_cast<int>(buffer.size()));

        // 打开文件句柄
        HANDLE hFile = CreateFile(buffer.data(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile == INVALID_HANDLE_VALUE) {
            std::cerr << "Failed to open file." << std::endl;
        }

        // 创建文件映射对象
        HANDLE hMapFile = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
        if (hMapFile == NULL) {
            std::cerr << "Failed to create file mapping object." << std::endl;
            CloseHandle(hFile);
        }

        // 映射文件到进程地址空间
        LPVOID lpMapView = MapViewOfFile(hMapFile, FILE_MAP_READ, 0, 0, 0);
        if (lpMapView == NULL) {
            std::cerr << "Failed to map view of file." << std::endl;
            CloseHandle(hMapFile);
            CloseHandle(hFile);
        }

        // 从内存中读取文件
        char* pBuffer = static_cast<char*>(lpMapView);
        std::cout << "Content of the file:" << std::endl;
        std::cout << pBuffer << std::endl;

        std::cout << "Succeeded in overwriting the mapped view of the file!" << std::endl;


        pgp.SetInputMessage(pBuffer);
        pgp.SetOutputFile(QoutputfilepathEncryptSingle);

        pgp.SetASCIIArmor(false);
        pgp.SetOverwrite(true);//覆盖写
        pgp.SetKeyCount(1);
        pgp.SetKeyKeyring(0, mykeyringDir);
        pgp.SetKeyUserId(0, privateKey);
        pgp.SetKeyPassphrase(0, passphrase);
        pgp.SetRecipientKeyCount(1);
        pgp.SetRecipientKeyKeyring(0, mykeyringDir);
        pgp.SetRecipientKeyUserId(0, recipientKey);

        int ret_code = pgp.SignAndEncrypt();

        pgp.GetOutputFile();

        ui->textBrowser->setText("单用户文件存储成功！存储位置："+QoutputfilepathEncryptSingle);

        cout << ret_code << endl;
        if (ret_code)     // Got an error.  The user is done.
        {
            printf("\nError: %d", ret_code);
            /*if (pgp.GetLastError())
            {
                printf(" \"%s\"\n", pgp.GetLastError());
            }*/
        }


        string outputfilepathMultipleDecrypt = "D:\\OpenPGP_File_Manage_show\\lenovo\\File\\" + userID + "SingleDecrypted.txt";
        QString QoutputfilepathMultipleDecrypt = QString::fromStdString(outputfilepathMultipleDecrypt);

        pgp.SetOverwrite(1);
        pgp.SetInputFile(QoutputfilepathEncryptSingle);
        pgp.SetOutputFile(QoutputfilepathMultipleDecrypt);

        pgp.SetKeyCount(1);
        pgp.SetKeyKeyring(0, mykeyringDir);
        pgp.SetKeyUserId(0, privateKey);
        pgp.SetKeyPassphrase(0, passphrase);
        pgp.SetSignerKeyCount(1);
        pgp.SetSignerKeyKeyring(0, mykeyringDir);
        pgp.SetSignerKeyUserId(0, signerKey);
        int ret_code_mul = pgp.DecryptAndVerifySignature();

        pgp.GetOutputFile();

        QString dataDecrypt;
        QFile fileDecrypt(QoutputfilepathMultipleDecrypt); //path是文件的路径
        if(!fileDecrypt.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qDebug()<<"文件未打开!";
        }
        while(!fileDecrypt.atEnd())
        {
            QByteArray array = fileDecrypt.readLine();
            QString str(array);
           // qDebug() << str;
            dataDecrypt.append(str);
        }

        ui->textBrowser_2->setText("单用户文件真实性认证完成、解密成功！解密文件存储位置："+QoutputfilepathMultipleDecrypt+"\n\n解密结果是："+dataDecrypt);

        // 覆盖文件映射的地址空间
        // SecureZeroMemory(lpMapView, GetFileSize(hFile, NULL));

        // 关闭文件映射
        UnmapViewOfFile(lpMapView);
        CloseHandle(hMapFile);

        // 关闭文件句柄
        CloseHandle(hFile);



        break;
    }



}




/*
QTextBrowser QScrollBar::handle:vertical
{
    background-color: rgb(13,74,107);
    min-height: 30px;
    border-radius:3px;
    width: 6px;
}

QTextBrowser QScrollBar::add-line:vertical
{
   border: none;
   height: 0px;
 }

QTextBrowser QScrollBar::sub-line:vertical
{
   border: none;
   height: 0px;
}

QTextBrowser QScrollBar::add-page:vertical,QScrollBar::sub-page:vertical
{
    background:transparent;
    border-radius:3px;
}
*/



void MainWindow::on_pushButton_3_clicked()
{
    //展示文件夹创建
    Global global;

    //用户创建
    User user;
    string userID = user.getUserID();

    //密钥生成和导出

    KeyManage keyManage;
    keyManage.init(global, user);

    //密码唯一，且由用户的用户名和安全序列号唯一生成
    string pwd = ToString(hash<string>{}(user.getUsername()) ^ hash<PVOID>{}(user.getStringSid()));

    keyManage.GenerateKeyPairRSA(userID, pwd);
    keyManage.ExportPublicKey(userID, pwd);
    keyManage.ExportPrivateKey(userID, pwd);//私钥敏感信息不能导出
    keyManage.KeyStoreListKeys(pwd);

    QString tbu, tbp;
    tbu = QString::fromStdString(userID);
    tbp = QString::fromStdString(pwd);
    ui->textBrowser_3->setText("Key has been generated! The UserID is: " + tbu + ", The pwd is: " + tbp);


    //模式选择：原理展示/存储模式/调阅模式
    //用户界面
    while (true)
    {
        ModeManage modeManage;
        int Mode = modeManage.modeInput(global, user);
        Mode = 22;
        //modeManage.modeControl(Mode, user, pwd);
        //modeManage.modeControl(Mode, user, pwd);

        string keyringDir = conbineStrings(global.pathStringKey, "key-store");

        string newFile = ToString(userID) + "EncryptedMultiple.gpg"; //生成文件名为 userID + Encrypted.gpg
        string outputFile = conbineStrings(global.pathStringFile, newFile);

        char mykeyringDir[LINE_LEN];
        char passphrase[LINE_LEN];
        char privateKey[LINE_LEN];
        char recipientKey[LINE_LEN];
        char signerKey[LINE_LEN];

        QString tempmykeyringdir = ui->lineEdit->text();
        mykeyringdir = tempmykeyringdir.toStdString();
        //string mykeyringdir="D:\\OpenPGP_File_Manage_show\\lenovo\\Key\\key-store";

        QString aidtempSingle = ui->lineEdit_2->text();
        aidSingle = aidtempSingle.toStdString();
        QString apwdtempSingle = ui->lineEdit_3->text();
        apwdSingle = apwdtempSingle.toStdString();

        QString reciptempSingle = ui->lineEdit_4->text();
        recipSingle = reciptempSingle.toStdString();
        QString signtempSingle = ui->lineEdit_5->text();
        signSingle = signtempSingle.toStdString();

        strcpy(mykeyringDir,mykeyringdir.c_str());
        strcpy(passphrase,apwdSingle.c_str());
        strcpy(privateKey,aidSingle.c_str());
        strcpy(recipientKey,recipSingle.c_str());
        strcpy(signerKey,signSingle.c_str());


    /*
        printf("\nPrivate Key User Id (Used to sign outgoing messages and decrypt incoming messages): ");
        fgets(privateKey, LINE_LEN, stdin);
        privateKey[strlen(privateKey) - 1] = '\0';
        printf("Passphrase: ");
        fgets(passphrase, LINE_LEN, stdin);
        passphrase[strlen(passphrase) - 1] = '\0';
        printf("Recipient Key User Id (Used to encrypt outgoing messages): ");
        fgets(recipientKey, LINE_LEN, stdin);
        recipientKey[strlen(recipientKey) - 1] = '\0';
        printf("Signer Key User Id (Used to verify the signature of an incoming message): ");
        fgets(signerKey, LINE_LEN, stdin);
        signerKey[strlen(signerKey) - 1] = '\0';
    */
        //modeUserIDPwd.modeUserID = privateKey;
        //modeUserIDPwd.modePwd = passphrase;

        char inFileEncryptSingle[LINE_LEN];
        QString QinputfilepathEncryptSingle = ui->lineEdit_10->text();
        inputfilepathEncryptSingle = QinputfilepathEncryptSingle.toStdString();

        QString QoutputfilepathEncryptSingle = QString::fromStdString(outputFile);

        OpenPGP pgp;

        size_t size = inputfilepathEncryptSingle.length();
        std::vector<wchar_t> buffer(inputfilepathEncryptSingle.size() + 1);
        MultiByteToWideChar(CP_ACP, 0, inputfilepathEncryptSingle.c_str(), -1, buffer.data(), static_cast<int>(buffer.size()));

        // 打开文件句柄
        HANDLE hFile = CreateFile(buffer.data(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile == INVALID_HANDLE_VALUE) {
            std::cerr << "Failed to open file." << std::endl;
        }

        // 创建文件映射对象
        HANDLE hMapFile = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
        if (hMapFile == NULL) {
            std::cerr << "Failed to create file mapping object." << std::endl;
            CloseHandle(hFile);
        }

        // 映射文件到进程地址空间
        LPVOID lpMapView = MapViewOfFile(hMapFile, FILE_MAP_READ, 0, 0, 0);
        if (lpMapView == NULL) {
            std::cerr << "Failed to map view of file." << std::endl;
            CloseHandle(hMapFile);
            CloseHandle(hFile);
        }

        // 从内存中读取文件
        char* pBuffer = static_cast<char*>(lpMapView);
        std::cout << "Content of the file:" << std::endl;
        std::cout << pBuffer << std::endl;

        std::cout << "Succeeded in overwriting the mapped view of the file!" << std::endl;

        pgp.SetInputMessage(pBuffer);
        pgp.SetOutputFile(QoutputfilepathEncryptSingle);

        pgp.SetASCIIArmor(false);
        pgp.SetOverwrite(true);//覆盖写
        pgp.SetKeyCount(1);
        pgp.SetKeyKeyring(0, mykeyringDir);
        pgp.SetKeyUserId(0, privateKey);
        pgp.SetKeyPassphrase(0, passphrase);
        pgp.SetRecipientKeyCount(1);
        pgp.SetRecipientKeyKeyring(0, mykeyringDir);
        pgp.SetRecipientKeyUserId(0, recipientKey);

        int ret_code = pgp.SignAndEncrypt();

        pgp.GetOutputFile();

        ui->textBrowser->setText("多用户文件存储成功！存储位置："+QoutputfilepathEncryptSingle);

        cout << ret_code << endl;
        if (ret_code)     // Got an error.  The user is done.
        {
            printf("\nError: %d", ret_code);
            /*if (pgp.GetLastError())
            {
                printf(" \"%s\"\n", pgp.GetLastError());
            }*/
        }

        char passphrase2[LINE_LEN];
        char privateKey2[LINE_LEN];
        char recipientKey2[LINE_LEN];
        char signerKey2[LINE_LEN];

        QString aidtempMultiple = ui->lineEdit_8->text();
        aidMultiple = aidtempMultiple.toStdString();
        QString apwdtempMultiple = ui->lineEdit_7->text();
        apwdMultiple = apwdtempMultiple.toStdString();

        QString reciptempMultiple = ui->lineEdit_6->text();
        recipMultiple = reciptempMultiple.toStdString();
        QString signtempMultiple = ui->lineEdit_9->text();
        signMultiple = signtempMultiple.toStdString();

        strcpy(passphrase2,apwdMultiple.c_str());
        strcpy(privateKey2,aidMultiple.c_str());
        strcpy(recipientKey2,recipMultiple.c_str());
        strcpy(signerKey2,signMultiple.c_str());


        string outputfilepathMultipleDecrypt = "D:\\OpenPGP_File_Manage_show\\lenovo\\File\\" + userID + "MultipleDecrypted.txt";
        QString QoutputfilepathMultipleDecrypt = QString::fromStdString(outputfilepathMultipleDecrypt);

        pgp.SetOverwrite(1);
        pgp.SetInputFile(QoutputfilepathEncryptSingle);
        pgp.SetOutputFile(QoutputfilepathMultipleDecrypt);

        pgp.SetKeyCount(1);
        pgp.SetKeyKeyring(0, mykeyringDir);
        pgp.SetKeyUserId(0, privateKey2);
        pgp.SetKeyPassphrase(0, passphrase2);
        pgp.SetSignerKeyCount(1);
        pgp.SetSignerKeyKeyring(0, mykeyringDir);
        pgp.SetSignerKeyUserId(0, signerKey2);
        int ret_code_mul = pgp.DecryptAndVerifySignature();

        pgp.GetOutputFile();

        QString dataDecrypt;
        QFile fileDecrypt(QoutputfilepathMultipleDecrypt); //path是文件的路径
        if(!fileDecrypt.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qDebug()<<"文件未打开!";
        }
        while(!fileDecrypt.atEnd())
        {
            QByteArray array = fileDecrypt.readLine();
            QString str(array);
           // qDebug() << str;
            dataDecrypt.append(str);
        }

        ui->textBrowser_2->setText("多用户文件真实性认证完成、解密成功！解密文件存储位置："+QoutputfilepathMultipleDecrypt+"\n\n解密结果是："+dataDecrypt);

        // 覆盖文件映射的地址空间
        // SecureZeroMemory(lpMapView, GetFileSize(hFile, NULL));

        // 关闭文件映射
        UnmapViewOfFile(lpMapView);
        CloseHandle(hMapFile);

        // 关闭文件句柄
        CloseHandle(hFile);

        break;
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    //展示文件夹创建
    Global global;

    //用户创建
    User user;
    string userID = user.getUserID();

    //密钥生成和导出

    KeyManage keyManage;
    keyManage.init(global, user);

    //密码唯一，且由用户的用户名和安全序列号唯一生成
    string pwd = ToString(hash<string>{}(user.getUsername()) ^ hash<PVOID>{}(user.getStringSid()));

    keyManage.GenerateKeyPairRSA(userID, pwd);
    keyManage.ExportPublicKey(userID, pwd);
    keyManage.ExportPrivateKey(userID, pwd);//私钥敏感信息不能导出
    keyManage.KeyStoreListKeys(pwd);

    QString tbu, tbp;
    tbu = QString::fromStdString(userID);
    tbp = QString::fromStdString(pwd);
    ui->textBrowser_3->setText("Key has been generated! The UserID is: " + tbu + ", The pwd is: " + tbp);


    //模式选择：原理展示/存储模式/调阅模式
    //用户界面
    while (true)
    {
        ModeManage modeManage;
        int Mode = modeManage.modeInput(global, user);
        Mode = 3;
        //modeManage.modeControl(Mode, user, pwd);
        //modeManage.modeControl(Mode, user, pwd);

        string keyringDir = conbineStrings(global.pathStringKey, "key-store");

        string newFile = ToString(userID) + "EncryptedMultiple.gpg"; //生成文件名为 userID + Encrypted.gpg
        string outputFile = conbineStrings(global.pathStringFile, newFile);

        char mykeyringDir[LINE_LEN];

        QString tempmykeyringdir = ui->lineEdit->text();
        mykeyringdir = tempmykeyringdir.toStdString();
        //string mykeyringdir="D:\\OpenPGP_File_Manage_show\\lenovo\\Key\\key-store";
        strcpy(mykeyringDir,mykeyringdir.c_str());



    /*
        printf("\nPrivate Key User Id (Used to sign outgoing messages and decrypt incoming messages): ");
        fgets(privateKey, LINE_LEN, stdin);
        privateKey[strlen(privateKey) - 1] = '\0';
        printf("Passphrase: ");
        fgets(passphrase, LINE_LEN, stdin);
        passphrase[strlen(passphrase) - 1] = '\0';
        printf("Recipient Key User Id (Used to encrypt outgoing messages): ");
        fgets(recipientKey, LINE_LEN, stdin);
        recipientKey[strlen(recipientKey) - 1] = '\0';
        printf("Signer Key User Id (Used to verify the signature of an incoming message): ");
        fgets(signerKey, LINE_LEN, stdin);
        signerKey[strlen(signerKey) - 1] = '\0';
    */
        //modeUserIDPwd.modeUserID = privateKey;
        //modeUserIDPwd.modePwd = passphrase;

        char passphrase2[LINE_LEN];
        char privateKey2[LINE_LEN];
        char recipientKey2[LINE_LEN];
        char signerKey2[LINE_LEN];

        QString aidtempMultiple = ui->lineEdit_8->text();
        aidMultiple = aidtempMultiple.toStdString();
        QString apwdtempMultiple = ui->lineEdit_7->text();
        apwdMultiple = apwdtempMultiple.toStdString();

        QString reciptempMultiple = ui->lineEdit_6->text();
        recipMultiple = reciptempMultiple.toStdString();
        QString signtempMultiple = ui->lineEdit_9->text();
        signMultiple = signtempMultiple.toStdString();

        strcpy(passphrase2,apwdMultiple.c_str());
        strcpy(privateKey2,aidMultiple.c_str());
        strcpy(recipientKey2,recipMultiple.c_str());
        strcpy(signerKey2,signMultiple.c_str());

        OpenPGP pgp;


        QString QinputfilepathAccess = ui->lineEdit_10->text();


        string outputfilepathMultipleDecrypt = "D:\\OpenPGP_File_Manage_show\\lenovo\\File\\" + userID + "Accessed.txt";
        QString QoutputfilepathMultipleDecrypt = QString::fromStdString(outputfilepathMultipleDecrypt);

        pgp.SetOverwrite(1);
        pgp.SetInputFile(QinputfilepathAccess);
        pgp.SetOutputFile(QoutputfilepathMultipleDecrypt);

        pgp.SetKeyCount(1);
        pgp.SetKeyKeyring(0, mykeyringDir);
        pgp.SetKeyUserId(0, privateKey2);
        pgp.SetKeyPassphrase(0, passphrase2);
        pgp.SetSignerKeyCount(1);
        pgp.SetSignerKeyKeyring(0, mykeyringDir);
        pgp.SetSignerKeyUserId(0, signerKey2);
        int ret_code_mul = pgp.DecryptAndVerifySignature();

        pgp.GetOutputFile();

        QString dataDecrypt;
        QFile fileDecrypt(QoutputfilepathMultipleDecrypt); //path是文件的路径
        if(!fileDecrypt.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qDebug()<<"文件未打开!";
        }
        while(!fileDecrypt.atEnd())
        {
            QByteArray array = fileDecrypt.readLine();
            QString str(array);
           // qDebug() << str;
            dataDecrypt.append(str);
        }

        ui->textBrowser_2->setText("已授权用户调阅成功！解密文件存储位置："+QoutputfilepathMultipleDecrypt+"\n\n解密结果是："+dataDecrypt);


        break;
    }
}
