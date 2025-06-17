#include "homepage.h"
#include "ui_homepage.h"
#include "transactions.h"
#include "monthlygoals.h"  // ✅ Include this header for monthly goals dialog
#include <QMessageBox>
#include "viewtransactions.h"
#include "analyzereport.h"

// Constructor: sets up the UI for the homepage dialog
homepage::homepage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::homepage)
{
    ui->setupUi(this);
}

// Destructor: cleans up the UI object
homepage::~homepage()
{
    delete ui;
}

// Slot called when the "Add Transaction" button is clicked
void homepage::on_buttonAddTransaction_clicked()
{
    // Create and show the transactions dialog as modal
    transactions *txnWindow = new transactions(this);
    txnWindow->exec();
}

// Slot called when the "View Transaction" button is clicked
void homepage::on_buttonViewTransaction_clicked()
{
    // Create and show the viewtransactions dialog as modal
    viewtransactions *vt = new viewtransactions(this);
    vt->exec();
}

// Slot called when the "Set Goal" button is clicked
void homepage::on_buttonSetGoal_clicked()
{
    // Create and show the monthlygoals dialog as modal instead of a message box
    monthlygoals *goalWindow = new monthlygoals(this);
    goalWindow->exec();
}

// Slot called when the "Analyze Report" button is clicked
void homepage::on_buttonAnalyzeReport_clicked()
{
    // Create and show the analyzereport dialog as modal
    analyzereport *report = new analyzereport(this);
    report->exec();
}
