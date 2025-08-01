#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>

namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();
    int getCurrentUserId() const;

private slots:
    void on_buttonLogin_clicked();
    void on_buttonSignup_clicked();
    void on_buttonForgotPassword_clicked();
    void on_checkBoxPassword_toggled(bool checked);


private:
    Ui::login *ui;
    void showMessage(const QString &message);
    bool passwordVisible;
    int currentUserId = -1;
};

#endif // LOGIN_H
