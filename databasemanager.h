#ifndef DATABASEMANAGER_H // Prevents multiple inclusions of this header file
#define DATABASEMANAGER_H

#include <QObject>         // Includes base Qt object class
#include <QSqlDatabase>    // Includes support for working with SQL databases in Qt

// Declaration of the DatabaseManager class, which handles database operations
class DatabaseManager : public QObject
{
    Q_OBJECT               // Macro that enables Qt's meta-object features (signals, slots, etc.)

public:
    static DatabaseManager& instance(); // Returns the singleton instance of DatabaseManager
    QSqlDatabase getDatabase();         // Returns the QSqlDatabase object
    bool openDatabase();                // Opens the database connection
    void closeDatabase();               // Closes the database connection

private:
    explicit DatabaseManager(QObject *parent = nullptr); // Constructor (explicit to avoid implicit conversions)
    ~DatabaseManager();                                  // Destructor

    DatabaseManager(const DatabaseManager&) = delete;            // Delete copy constructor (no copying allowed)
    DatabaseManager& operator=(const DatabaseManager&) = delete; // Delete copy assignment operator

    QSqlDatabase m_database;      // Member variable to store the database connection
    void initializeTables();      // Initializes database tables if they don’t exist
};

#endif // DATABASEMANAGER_H
