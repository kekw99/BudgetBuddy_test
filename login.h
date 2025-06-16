#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>

// Forward declaration of the UI class generated from the .ui file by Qt's uic
namespace Ui {
class login;
}

// login class inherits from QDialog to provide a login dialog window
class login : public QDialog
{
    Q_OBJECT

public:
    // Constructor: initializes the login dialog, optionally with a parent widget
    explicit login(QWidget *parent = nullptr);

    // Destructor: cleans up resources used by the dialog
    ~login();

private slots:
    // Slot called when the "Login" button is clicked
    void on_buttonLogin_clicked();

    // Slot called when the "Signup" button is clicked
    void on_buttonSignup_clicked();

    // Slot called when the "Forgot Password" button is clicked
    void on_buttonForgotPassword_clicked();

    // Slot called when the "Toggle Password" (show/hide) button is clicked
    void on_buttonTogglePassword_clicked();

private:
    // Pointer to the UI elements defined in the .ui file
    Ui::login *ui;

    // Utility function to show a message (e.g., error or info) to the user
    void showMessage(const QString &message);

    // Boolean flag to track whether the password field is currently visible or hidden
    bool passwordVisible;

    // Paths to the icons for the password visibility toggle button:
    // iconClosedPath is the icon when password is hidden
    // iconOpenPath is the icon when password is visible
    QString iconClosedPath;
    QString iconOpenPath;
};

#endif // LOGIN_H
