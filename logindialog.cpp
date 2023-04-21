#include "logindialog.h"
#include "ui_logindialog.h"
#include "qmessagebox.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

    QPixmap Images("C:\\Users\\lenovo\\Desktop\\cover.png");
    QPalette Palette = this->palette();
    Palette.setBrush(QPalette::Background, Images);
    this->setPalette(Palette);

    ui->pushButton->setStyleSheet(
        //正常状态样式
        "QPushButton{"
        "background-color:rgb(210,157,151);"//设置按钮背景色
        "border-radius:5px;"//设置圆角半径
        "color:white;"//设置按钮字体颜色
        "font-family: Helvetica;"
        "font-size: 12pt;"
        "font-weight: bold;"
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


    connect(this, &LoginDialog::login, this, &LoginDialog::loginSlot);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_pushButton_clicked()
{
    emit login();

}

void LoginDialog::loginSlot()
{
    QMessageBox::information(this, "Notice", "Login Successfully!");
    parentWidget()->show();
    this->hide();
}

