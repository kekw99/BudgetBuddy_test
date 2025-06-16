#ifndef FORGOTPASSWORD_H
#define FORGOTPASSWORD_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>

// ForgotPassword dialog class handles the UI and logic for resetting a password
class ForgotPassword : public QDialog
{
    Q_OBJECT

public:
    // Constructor: optionally takes a parent widget
    explicit ForgotPassword(QWidget *parent = nullptr);

    // Destructor
    ~ForgotPassword();

private slots:
    // Slot called when the Reset button is clicked
    void on_buttonReset_clicked();

    // Slot called when the Cancel button is clicked
    void on_buttonCancel_clicked();

    // Slot to toggle visibility of the "New Password" input
    void toggleNewPasswordVisibility();

    // Slot to toggle visibility of the "Confirm Password" input
    void toggleConfirmPasswordVisibility();

private:
    // Input field for the username
    QLineEdit *lineEditUsername;

    // Input field for the new password
    QLineEdit *lineEditNewPassword;

    // Input field for confirming the new password
    QLineEdit *lineEditConfirmPassword;

    // Button to submit the password reset request
    QPushButton *buttonReset;

    // Button to cancel the reset and close the dialog
    QPushButton *buttonCancel;

    // Button to toggle showing/hiding the new password text
    QPushButton *toggleNewPasswordBtn;

    // Button to toggle showing/hiding the confirm password text
    QPushButton *toggleConfirmPasswordBtn;

    // Tracks whether new password is visible or masked
    bool newPassVisible = false;

    // Tracks whether confirm password is visible or masked
    bool confirmPassVisible = false;

    // Helper function to show informational messages to the user
    void showMessage(const QString &msg);
};

#endif // FORGOTPASSWORD_H
