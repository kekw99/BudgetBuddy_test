#include "databasemanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

// Constructor: Initializes the SQLite database connection
DatabaseManager::DatabaseManager(QObject *parent) : QObject(parent)
{
    // Add SQLite database connection
    m_database = QSqlDatabase::addDatabase("QSQLITE");
    // Set the file name for the database
    m_database.setDatabaseName("budgetbuddy.db");
}

// Destructor: Ensures the database is closed when the manager is destroyed
DatabaseManager::~DatabaseManager()
{
    closeDatabase();
}

// Singleton accessor - ensures only one instance of DatabaseManager exists
DatabaseManager& DatabaseManager::instance()
{
    static DatabaseManager instance;
    return instance;
}

// Returns the database object (useful for executing queries in other classes)
QSqlDatabase DatabaseManager::getDatabase()
{
    return m_database;
}

// Opens the database and initializes tables if opening succeeds
bool DatabaseManager::openDatabase()
{
    if (!m_database.open()) {
        // Log error if opening fails
        qDebug() << "Failed to open database:" << m_database.lastError().text();
        return false;
    }

    // Create tables if they do not exist
    initializeTables();
    return true;
}

// Closes the database if it is currently open
void DatabaseManager::closeDatabase()
{
    if (m_database.isOpen())
        m_database.close();
}

// Creates necessary tables if they don't already exist
void DatabaseManager::initializeTables()
{
    QSqlQuery query;

    // Create 'users' table for storing user credentials
    query.exec("CREATE TABLE IF NOT EXISTS users ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT,"
               "username TEXT UNIQUE,"
               "password TEXT)");

    // Create 'transactions' table for income and expenses
    query.exec("CREATE TABLE IF NOT EXISTS transactions ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT,"
               "user_id INTEGER,"
               "type TEXT,"              // e.g., "Income" or "Expense"
               "category TEXT,"          // e.g., "Food", "Rent"
               "amount REAL,"
               "date TEXT,"              // Stored as string in ISO format (YYYY-MM-DD)
               "FOREIGN KEY(user_id) REFERENCES users(id))");

    // Create 'monthly_goals' table to store user's monthly budget goals
    query.exec("CREATE TABLE IF NOT EXISTS monthly_goals ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "user_id INTEGER, "
               "month TEXT, "            // e.g., "January"
               "year INTEGER, "
               "amount REAL, "
               "UNIQUE(user_id, month, year))");  // Prevent duplicate goals per user/month/year

    // Create 'alerts' table for warning messages like exceeding budget
    query.exec("CREATE TABLE IF NOT EXISTS alerts ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT,"
               "user_id INTEGER,"
               "message TEXT,"
               "created_at TEXT,"        // Timestamp for when alert was created
               "FOREIGN KEY(user_id) REFERENCES users(id))");
}
