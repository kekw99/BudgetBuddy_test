#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QDialog>

// Forward declaration of the UI class generated from the .ui file by Qt's uic tool
namespace Ui {
class homepage;
}

// homepage class inherits from QDialog to create a dialog window
class homepage : public QDialog
{
    Q_OBJECT

public:
    // Constructor: initializes the dialog, optionally accepts a parent widget pointer
    explicit homepage(QWidget *parent = nullptr);

    // Destructor: cleans up resources used by the dialog
    ~homepage();

private slots:
    // Slot function called when the "Add Transaction" button is clicked
    void on_buttonAddTransaction_clicked();

    // Slot function called when the "View Transaction" button is clicked
    void on_buttonViewTransaction_clicked();

    // Slot function called when the "Set Goal" button is clicked
    void on_buttonSetGoal_clicked();

    // Slot function called when the "Analyze Report" button is clicked
    void on_buttonAnalyzeReport_clicked();

private:
    // Pointer to the UI object which contains widgets defined in the .ui file
    Ui::homepage *ui;
};

#endif // HOMEPAGE_H
