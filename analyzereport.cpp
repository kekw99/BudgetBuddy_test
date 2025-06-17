#include "analyzereport.h"
#include "ui_analyzereport.h"

// Qt Charts module includes for pie chart visualization
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>

// Qt includes for layout, database, date, and debugging
#include <QVBoxLayout>
#include <QSqlQuery>
#include <QSqlError>
#include <QDate>
#include <QDebug>

// Constructor - sets up the UI and connects button signals to their respective slots
analyzereport::analyzereport(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::analyzereport)
{
    ui->setupUi(this);  // Set up UI components from the .ui file

    // Populate the month dropdown with month names
    QStringList months = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };
    ui->comboBoxMonth->addItems(months);

    // Set the year spinner to a valid range and default to the current year
    ui->spinBoxYear->setRange(2000, 2100);
    ui->spinBoxYear->setValue(QDate::currentDate().year());

    // Connect button signals to corresponding slots
    connect(ui->buttonBack, &QPushButton::clicked, this, &analyzereport::onBackButtonClicked);
    connect(ui->buttonFilter, &QPushButton::clicked, this, &analyzereport::onFilterClicked);

    // Generate the default chart on initialization
    onFilterClicked();
}

// Destructor - cleans up the UI
analyzereport::~analyzereport()
{
    delete ui;
}

// Slot to handle "Back" button click - closes the dialog
void analyzereport::onBackButtonClicked()
{
    this->close();
}

// Slot to handle "Filter" button click - generates a pie chart based on selected month and year
void analyzereport::onFilterClicked()
{
    QString month = ui->comboBoxMonth->currentText();   // Get selected month
    int year = ui->spinBoxYear->value();                // Get selected year
    generatePieChart(month, year);                      // Generate chart
}

// Function to generate a pie chart of expenses by category for a given month and year
void analyzereport::generatePieChart(const QString &month, int year)
{
    int monthIndex = ui->comboBoxMonth->currentIndex() + 1;  // Month index starts at 1
    QString formattedMonth = QString("%1").arg(monthIndex, 2, 10, QChar('0'));  // Format to "MM"

    QPieSeries *series = new QPieSeries();  // Create a new pie chart series

    QSqlQuery query;
    // Prepare SQL query to fetch total expense amount grouped by category
    query.prepare(R"(
        SELECT category, SUM(amount)
        FROM transactions
        WHERE type = 'Expense'
          AND strftime('%m', date) = :month
          AND strftime('%Y', date) = :year
        GROUP BY category
    )");

    // Bind values to the SQL query placeholders
    query.bindValue(":month", formattedMonth);
    query.bindValue(":year", QString::number(year));

    // Execute the query and check for errors
    if (!query.exec()) {
        qDebug() << "Chart query failed:" << query.lastError().text();
        return;
    }

    // Append each category and its total amount to the pie chart series
    while (query.next()) {
        QString category = query.value(0).toString();
        double amount = query.value(1).toDouble();
        series->append(category, amount);
    }

    // Create the chart and set its properties
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Expenses in " + month + " " + QString::number(year));
    chart->legend()->setAlignment(Qt::AlignRight);  // Legend on the right

    // Create a chart view to display the chart
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);  // Smooth rendering

    // Clear any existing layout or chart from the chart widget
    QLayout *oldLayout = ui->chartWidget->layout();
    if (oldLayout) {
        QLayoutItem *item;
        while ((item = oldLayout->takeAt(0)) != nullptr) {
            delete item->widget();  // Delete each widget in the layout
            delete item;
        }
        delete oldLayout;  // Delete the old layout itself
    }

    // Create and set a new layout to hold the updated chart
    QVBoxLayout *layout = new QVBoxLayout(ui->chartWidget);
    layout->addWidget(chartView);
}
