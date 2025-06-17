#include "forgotpassword.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QHBoxLayout>

// Constructor - sets up the UI for password reset
ForgotPassword::ForgotPassword(QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle("Reset Password");

    // Create labels for input fields
    QLabel *labelUsername = new QLabel("Username:");
    QLabel *labelNewPassword = new QLabel("Enter new password:");
    QLabel *labelConfirmPassword = new QLabel("Confirm new password:");

    // Input fields
    lineEditUsername = new QLineEdit();
    lineEditNewPassword = new QLineEdit();
    lineEditConfirmPassword = new QLineEdit();

    // Set password fields to hidden by default
    lineEditNewPassword->setEchoMode(QLineEdit::Password);
    lineEditConfirmPassword->setEchoMode(QLineEdit::Password);

    // Create visibility toggle buttons for password fields
    toggleNewPasswordBtn = new QPushButton("👁️");
    toggleConfirmPasswordBtn = new QPushButton("👁️");
    toggleNewPasswordBtn->setFixedWidth(30);
    toggleConfirmPasswordBtn->setFixedWidth(30);

    // Buttons for reset and cancel
    buttonReset = new QPushButton("Reset Password");
    buttonCancel = new QPushButton("Cancel");

    // Layout for password field + toggle
    QHBoxLayout *newPassLayout = new QHBoxLayout;
    newPassLayout->addWidget(lineEditNewPassword);
    newPassLayout->addWidget(toggleNewPasswordBtn);

    QHBoxLayout *confirmPassLayout = new QHBoxLayout;
    confirmPassLayout->addWidget(lineEditConfirmPassword);
    confirmPassLayout->addWidget(toggleConfirmPasswordBtn);

    // Form layout to arrange labels and fields
    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow(labelUsername, lineEditUsername);
    formLayout->addRow(labelNewPassword, newPassLayout);
    formLayout->addRow(labelConfirmPassword, confirmPassLayout);

    // Layout for buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(buttonReset);
    buttonLayout->addWidget(buttonCancel);

    // Main vertical layout for the dialog
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);

    // Connect signals to slots
    connect(buttonReset, &QPushButton::clicked, this, &ForgotPassword::on_buttonReset_clicked);
    connect(buttonCancel, &QPushButton::clicked, this, &ForgotPassword::on_buttonCancel_clicked);
    connect(toggleNewPasswordBtn, &QPushButton::clicked, this, &ForgotPassword::toggleNewPasswordVisibility);
    connect(toggleConfirmPasswordBtn, &QPushButton::clicked, this, &ForgotPassword::toggleConfirmPasswordVisibility);
}

// Destructor - nothing to manually delete because Qt cleans up child widgets
ForgotPassword::~ForgotPassword() {}

// Show a message box with a simple info message
void ForgotPassword::showMessage(const QString &msg)
{
    QMessageBox::information(this, "Reset Password", msg);
}

// Handles the reset password button click
void ForgotPassword::on_buttonReset_clicked()
{
    QString username = lineEditUsername->text();
    QString newPassword = lineEditNewPassword->text();
    QString confirmPassword = lineEditConfirmPassword->text();

    // Validation
    if (username.isEmpty() || newPassword.isEmpty() || confirmPassword.isEmpty()) {
        showMessage("Please fill in all fields.");
        return;
    }

    if (newPassword != confirmPassword) {
        showMessage("Passwords do not match.");
        return;
    }

    // Update password in the database
    QSqlQuery query;
    query.prepare("UPDATE users SET password = :password WHERE username = :username");
    query.bindValue(":password", newPassword);
    query.bindValue(":username", username);

    if (query.exec() && query.numRowsAffected() > 0) {
        showMessage("Password updated successfully!");
        accept();  // Close dialog with success
    } else {
        showMessage("Username not found or update failed.");
    }
}

// Cancel button - closes the dialog
void ForgotPassword::on_buttonCancel_clicked()
{
    reject();  // Close dialog with cancellation
}

// Toggles visibility of new password field
void ForgotPassword::toggleNewPasswordVisibility()
{
    newPassVisible = !newPassVisible;
    lineEditNewPassword->setEchoMode(newPassVisible ? QLineEdit::Normal : QLineEdit::Password);
    toggleNewPasswordBtn->setText(newPassVisible ? "🙈" : "👁️");
}

// Toggles visibility of confirm password field
void ForgotPassword::toggleConfirmPasswordVisibility()
{
    confirmPassVisible = !confirmPassVisible;
    lineEditConfirmPassword->setEchoMode(confirmPassVisible ? QLineEdit::Normal : QLineEdit::Password);
    toggleConfirmPasswordBtn->setText(confirmPassVisible ? "🙈" : "👁️");
}
