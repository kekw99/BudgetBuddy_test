#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H

// Include QDialog as the base class for dialog windows in Qt
#include <QDialog>

// Forward declaration of the UI class generated from the .ui file
namespace Ui {
class transactions;
}

// Definition of the transactions class, derived from QDialog
class transactions : public QDialog
{
    Q_OBJECT  // Enables Qt's signal-slot mechanism and other meta-object features

public:
    // Constructor - initializes the dialog, optionally with a parent widget
    explicit transactions(QWidget *parent = nullptr);

    // Destructor - cleans up any allocated resources
    ~transactions();

private slots:
    // Slot function that handles the logic when the "Submit" button is clicked
    void on_buttonSubmit_clicked();

private:
    // Pointer to the UI object generated by Qt Designer
    Ui::transactions *ui;

    // Utility function to show messages to the user (e.g., confirmations, errors)
    void showMessage(const QString &msg);
};

#endif // TRANSACTIONS_H