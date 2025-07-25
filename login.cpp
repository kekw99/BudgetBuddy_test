#include "login.h"
#include "ui_login.h"
#include "homepage.h"
#include <QSqlQuery>
#include <QMessageBox>
#include "signup.h"
#include "forgotpassword.h"
#include <QIcon>
#include <QDebug>
#include <QFile>
#include <QCoreApplication>

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login),
    currentUserId(-1)
{
    ui->setupUi(this);

    // Setup password field
    ui->lineEditPassword->setEchoMode(QLineEdit::Password);

    // Connect checkbox to toggle visibility
    connect(ui->checkBoxShowPassword, &QCheckBox::toggled, this, &login::on_checkBox_toggled);
}

login::~login()
{
    delete ui;
}

void login::showMessage(const QString &message)
{
    QMessageBox::information(this, "Login", message);
}

void login::on_buttonLogin_clicked()
{
    QString Username = ui->lineEditUsername->text();
    QString password = ui->lineEditPassword->text();

    QSqlQuery query;
    query.prepare("SELECT id FROM users WHERE username = :username AND password = :password");
    query.bindValue(":username", Username);
    query.bindValue(":password", password);

    if (query.exec() && query.next()) {
        int userId = query.value("id").toInt();
        showMessage("Login successful!");
        homepage *home = new homepage(userId, this);
        home->show();
        this->hide();
    }
    else {
        showMessage("Invalid Username or password.");
    }
}

void login::on_buttonSignup_clicked()
{
    signup *signupWindow = new signup(this);
    signupWindow->exec();
}

void login::on_buttonForgotPassword_clicked()
{
    ForgotPassword *fp = new ForgotPassword(this);
    fp->exec();
}

void login::on_checkBox_toggled(bool checked)
{
    ui->lineEditPassword->setEchoMode(checked ? QLineEdit::Normal : QLineEdit::Password);
}

int login::getCurrentUserId() const
{
    return currentUserId;
}
