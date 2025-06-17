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

// Constructor: initialize UI and setup password field & icons
login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login),
    passwordVisible(false)  // Initially password is hidden
{
    ui->setupUi(this);

    // Construct paths to eye icons relative to the app directory
    QString basePath = QCoreApplication::applicationDirPath();
    iconClosedPath = basePath + "/assets/eye_closed.png";
    iconOpenPath = basePath + "/assets/eye_open.png";

    // Warn if icon files are missing
    if (!QFile::exists(iconClosedPath) || !QFile::exists(iconOpenPath)) {
        qWarning() << "⚠️ Eye icon(s) missing:" << iconClosedPath << iconOpenPath;
    }

    // Set password field to hide characters by default
    ui->lineEditPassword->setEchoMode(QLineEdit::Password);

    // Set the toggle button icon to closed eye initially
    ui->buttonTogglePassword->setIcon(QIcon(iconClosedPath));
    ui->buttonTogglePassword->setIconSize(QSize(24, 24));
}

// Destructor: clean up UI pointer
login::~login()
{
    delete ui;
}

// Show an information message box with given text
void login::showMessage(const QString &message)
{
    QMessageBox::information(this, "Login", message);
}

// Slot: triggered when Login button is clicked
void login::on_buttonLogin_clicked()
{
    // Get email and password from input fields
    QString email = ui->lineEditEmail->text();
    QString password = ui->lineEditPassword->text();

    // Prepare SQL query to find matching user
    QSqlQuery query;
    query.prepare("SELECT * FROM users WHERE username = :email AND password = :password");
    query.bindValue(":email", email);
    query.bindValue(":password", password);

    // Execute query and check if user exists
    if (query.exec() && query.next()) {
        showMessage("Login successful!");

        // Open homepage window and hide login window
        homepage *home = new homepage(this);
        home->show();
        this->hide();
    } else {
        // Show error if credentials are invalid
        showMessage("Invalid email or password.");
    }
}

// Slot: triggered when Signup button is clicked
void login::on_buttonSignup_clicked()
{
    // Open the signup dialog as modal
    signup *signupWindow = new signup(this);
    signupWindow->exec();
}

// Slot: triggered when Forgot Password button is clicked
void login::on_buttonForgotPassword_clicked()
{
    // Open the forgot password dialog as modal
    ForgotPassword *fp = new ForgotPassword(this);
    fp->exec();
}

// Slot: triggered when the toggle password visibility button is clicked
void login::on_buttonTogglePassword_clicked()
{
    // Toggle the visibility flag
    passwordVisible = !passwordVisible;

    // Change the echo mode of the password line edit
    ui->lineEditPassword->setEchoMode(passwordVisible ? QLineEdit::Normal : QLineEdit::Password);

    // Set focus back to password field and update UI to reflect change
    ui->lineEditPassword->setFocus();
    ui->lineEditPassword->update();

    // Switch the icon to open or closed eye accordingly
    QIcon icon(passwordVisible ? iconOpenPath : iconClosedPath);
    ui->buttonTogglePassword->setIcon(icon);
}
