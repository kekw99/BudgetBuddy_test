#include "transactions.h"
#include "ui_transactions.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDoubleValidator>

// Constructor: setup UI and initialize validators and controls
transactions::transactions(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::transactions)
{
    ui->setupUi(this);

    // Validator to ensure amount is a positive decimal with max 2 decimals
    QDoubleValidator *validator = new QDoubleValidator(0.01, 1000000.00, 2, this);
    validator->setNotation(QDoubleValidator::StandardNotation);
    ui->lineEditAmount->setValidator(validator);

    // Populate category combo box with common categories
    ui->comboBoxCategory->addItems({"Food", "Fuel", "Rent", "Shopping", "Salary", "Misc"});
    
    // Populate type combo box with Income or Expense options
    ui->comboBoxType->addItems({"Income", "Expense"});

    // Enable calendar popup for date selection and set default to today
    ui->dateEdit->setCalendarPopup(true);
    ui->dateEdit->setDate(QDate::currentDate());
}

// Destructor: free UI resources
transactions::~transactions()
{
    delete ui;
}

// Utility function to show an information message box with a title
void transactions::showMessage(const QString &msg)
{
    QMessageBox::information(this, "Transaction", msg);
}

// Slot called when Submit button clicked to insert transaction record
void transactions::on_buttonSubmit_clicked()
{
    QString amountText = ui->lineEditAmount->text();
    QString category = ui->comboBoxCategory->currentText();
    QString type = ui->comboBoxType->currentText();
    QString date = ui->dateEdit->date().toString("yyyy-MM-dd");

    // Validate that amount is not empty
    if (amountText.isEmpty()) {
        showMessage("Please enter an amount.");
        return;
    }

    // Convert amount string to double and validate positive
    double amount = amountText.toDouble();
    if (amount <= 0.0) {
        showMessage("Amount must be greater than zero.");
        return;
    }

    // Prepare SQL query to insert transaction into database
    QSqlQuery query;
    query.prepare("INSERT INTO transactions (user_id, type, category, amount, date) "
                  "VALUES (:user_id, :type, :category, :amount, :date)");

    // Bind values (user_id is hardcoded here; replace with actual user context)
    query.bindValue(":user_id", 1);
    query.bindValue(":type", type);
    query.bindValue(":category", category);
    query.bindValue(":amount", amount);
    query.bindValue(":date", date);

    // Execute query and handle success or failure
    if (query.exec()) {
        showMessage("Transaction added successfully!");
        this->close(); // Close dialog after success
    } else {
        showMessage("Failed to add transaction: " + query.lastError().text());
    }
}
