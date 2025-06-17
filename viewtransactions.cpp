#include "viewtransactions.h"
#include "ui_viewtransactions.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QTableWidgetItem>
#include <QDebug>

// Slot to handle the back button click event; closes the dialog
void viewtransactions::onBackButtonClicked()
{
    this->close();  // Closes the current dialog window
}

// Constructor: initializes UI and loads transaction data
viewtransactions::viewtransactions(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::viewtransactions)
{
    ui->setupUi(this);

    // Load data from the database into the table widget
    loadTransactionData();
}

// Destructor: deletes the UI to free memory
viewtransactions::~viewtransactions()
{
    delete ui;
}

// Loads transaction and monthly goal data into the table widget
void viewtransactions::loadTransactionData()
{
    // Clear existing rows and set column count to 4
    ui->tableWidgetTransactions->setRowCount(0);
    ui->tableWidgetTransactions->setColumnCount(4);

    // Connect the back button click signal to the onBackButtonClicked slot
    connect(ui->buttonBack, &QPushButton::clicked, this, &viewtransactions::onBackButtonClicked);

    // Set the table headers
    QStringList headers = {"Date", "Category", "Type", "Amount"};
    ui->tableWidgetTransactions->setHorizontalHeaderLabels(headers);

    // SQL query combines transactions and monthly goals into one result set
    // monthly_goals dates are synthesized as '01-month-year' for display purposes
    QString sql = R"(
        SELECT date, category, type, amount FROM transactions
        UNION ALL
        SELECT
            '01-' || month || '-' || year AS date,
            month,
            'MonthlyGoal',
            amount
        FROM monthly_goals
        ORDER BY date DESC
    )";

    QSqlQuery query;

    // Execute the combined SQL query
    if (!query.exec(sql)) {
        qDebug() << "SQL error:" << query.lastError().text();
        return;  // Exit if query fails
    }

    int row = 0;

    // Iterate over each record in the query result
    while (query.next()) {
        // Insert a new row in the table for each record
        ui->tableWidgetTransactions->insertRow(row);

        // Populate each column in the row with query data
        for (int col = 0; col < 4; ++col) {
            ui->tableWidgetTransactions->setItem(row, col,
                new QTableWidgetItem(query.value(col).toString()));
        }
        row++;
    }
}
