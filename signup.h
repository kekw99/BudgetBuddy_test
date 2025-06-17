#ifndef SIGNUP_H
#define SIGNUP_H

// Include the base class for dialog windows in Qt
#include <QDialog>

// Forward declaration of the Ui class for the signup form,
// generated automatically from the corresponding .ui file
namespace Ui {
class signup;
}

// signup class definition, derived from QDialog
class signup : public QDialog
{
    Q_OBJECT  // Required macro to support Qt's signals and slots mechanism

public:
    // Constructor - initializes the signup dialog window
    explicit signup(QWidget *parent = nullptr);

    // Destructor - cleans up resources used by the signup dialog
    ~signup();

private slots:
    // Slot function called when the "Create Account" button is clicked
    void on_buttonCreateAccount_clicked();

    // Slot function to toggle password visibility (show/hide password)
    void on_buttonTogglePassword_clicked();

private:
    // Pointer to the generated UI class from Qt Designer
    Ui::signup *ui;

    // Helper function to show informational or error messages to the user
    void showMessage(const QString &msg);

    // Tracks whether the password is currently visible or hidden
    bool passwordVisible;

    // Path to the icon used when the password is hidden (e.g., closed eye icon)
    QString iconClosedPath;

    // Path to the icon used when the password is visible (e.g., open eye icon)
    QString iconOpenPath;
};

#endif // SIGNUP_H
