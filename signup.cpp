#include "signup.h"
#include "ui_signup.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QFile>
#include <QCoreApplication>
#include <QDebug>

// Constructor: initialize UI and setup password visibility toggle
signup::signup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::signup),
    passwordVisible(false)
{
    ui->setupUi(this);

    // Set placeholder text for input fields
    ui->lineEditUsername->setPlaceholderText("Enter Username");
    ui->lineEditPassword->setPlaceholderText("Enter Password");
    ui->lineEditConfirmPwd->setPlaceholderText("Confirm Password");

    // Password fields show dots initially
    ui->lineEditPassword->setEchoMode(QLineEdit::Password);
    ui->lineEditConfirmPwd->setEchoMode(QLineEdit::Password);

    // Load eye icons from assets folder to toggle password visibility
    QString basePath = QCoreApplication::applicationDirPath();
    iconClosedPath = basePath + "/assets/eye_closed.png";
    iconOpenPath = basePath + "/assets/eye_open.png";

    if (!QFile::exists(iconClosedPath) || !QFile::exists(iconOpenPath)) {
        qWarning() << "❗ Eye icon(s) not found!";
    }

    // Set initial icon on toggle button and size
    ui->buttonTogglePassword->setIcon(QIcon(iconClosedPath));
    ui->buttonTogglePassword->setIconSize(QSize(24, 24));
}

// Destructor: clean up UI pointer
signup::~signup()
{
    delete ui;
}

// Utility method to show an information message box with a custom title
void signup::showMessage(const QString &msg)
{
    QMessageBox::information(this, "Signup", msg);
}

// Slot: toggles password visibility for both password fields
void signup::on_buttonTogglePassword_clicked()
{
    passwordVisible = !passwordVisible;

    // Switch echo modes between normal text and password dots
    ui->lineEditPassword->setEchoMode(passwordVisible ? QLineEdit::Normal : QLineEdit::Password);
    ui->lineEditConfirmPwd->setEchoMode(passwordVisible ? QLineEdit::Normal : QLineEdit::Password);

    // Update the toggle button icon accordingly
    ui->buttonTogglePassword->setIcon(QIcon(passwordVisible ? iconOpenPath : iconClosedPath));

    // Debug log for visibility toggle
    qDebug() << "Password toggle clicked. Now visible:" << passwordVisible;
}

// Slot: handles the creation of a new account on button click
void signup::on_buttonCreateAccount_clicked()
{
    QString username = ui->lineEditUsername->text();
    QString password = ui->lineEditPassword->text();
    QString confirmPassword = ui->lineEditConfirmPwd->text();

    // Validate all fields are filled
    if (username.isEmpty() || password.isEmpty() || confirmPassword.isEmpty()) {
        showMessage("Please fill in all fields.");
        return;
    }

    // Check password confirmation match
    if (password != confirmPassword) {
        showMessage("Passwords do not match.");
        return;
    }

    // Check if username already exists in the database
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT id FROM users WHERE username = :username");
    checkQuery.bindValue(":username", username);
    checkQuery.exec();

    if (checkQuery.next()) {
        showMessage("Username already exists.");
        return;
    }

    // Insert new user record into database
    QSqlQuery insertQuery;
    insertQuery.prepare("INSERT INTO users (username, password) VALUES (:username, :password)");
    insertQuery.bindValue(":username", username);
    insertQuery.bindValue(":password", password);

    if (insertQuery.exec()) {
        showMessage("Account created! You can now log in.");
        this->close();  // Close signup dialog on success
    } else {
        // Show database error if insert failed
        showMessage("Signup failed: " + insertQuery.lastError().text());
    }
}
