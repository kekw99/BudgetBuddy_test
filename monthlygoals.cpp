#include "monthlygoals.h"
#include "ui_monthlygoals.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDoubleValidator>
#include <QDate>

// Constructor: sets up UI and validators
monthlygoals::monthlygoals(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::monthlygoals)
{
    ui->setupUi(this);

    // Validator to allow only positive numbers with max 2 decimal places for budget input
    QDoubleValidator *validator = new QDoubleValidator(0.01, 1000000.0, 2, this);
    validator->setNotation(QDoubleValidator::StandardNotation);
    ui->lineEditAmount->setValidator(validator);

    // Populate month combo box with all months
    QStringList months = {"January", "February", "March", "April", "May", "June",
                          "July", "August", "September", "October", "November", "December"};
    ui->comboBoxMonth->addItems(months);

    // Configure year spin box to allow years from 2000 to 2100, default to current year
    ui->spinBoxYear->setMinimum(2000);
    ui->spinBoxYear->setMaximum(2100);
    ui->spinBoxYear->setValue(QDate::currentDate().year());
}

// Destructor: clean up UI pointer
monthlygoals::~monthlygoals()
{
    delete ui;
}

// Show informational message box with given message
void monthlygoals::showMessage(const QString &msg)
{
    QMessageBox::information(this, "Monthly Budget", msg);
}

// Slot: called when Submit button is clicked
void monthlygoals::on_buttonSubmit_clicked()
{
    // Get current selections/inputs
    QString month = ui->comboBoxMonth->currentText();
    int year = ui->spinBoxYear->value();
    QString budgetText = ui->lineEditAmount->text();

    // Check if budget input is empty
    if (budgetText.isEmpty()) {
        showMessage("Please enter a budget amount.");
        return;
    }

    // Convert budget text to double and validate it's positive
    double amount = budgetText.toDouble();
    if (amount <= 0.0) {
        showMessage("Budget must be greater than 0.");
        return;
    }

    // Prepare SQL query to insert or update monthly budget for user
    QSqlQuery query;
    query.prepare("INSERT INTO monthly_goals (user_id, month, year, amount) "
                  "VALUES (:user_id, :month, :year, :amount) "
                  "ON CONFLICT(user_id, month, year) "
                  "DO UPDATE SET amount = excluded.amount");

    // For now, using user_id=1 as placeholder
    query.bindValue(":user_id", 1);
    query.bindValue(":month", month);
    query.bindValue(":year", year);
    query.bindValue(":amount", amount);

    // Execute the query once before checking success is a bug; remove duplicate exec
    // query.exec();

    if (query.exec()) {  // Executes and checks success
        showMessage("Monthly budget saved successfully!");
        this->close();  // Close dialog on success
    } else {
        // Show error message if query fails
        showMessage("Error: " + query.lastError().text());
    }
}
