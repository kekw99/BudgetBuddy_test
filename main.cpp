#include <QApplication>
#include "databasemanager.h"
#include "login.h"

int main(int argc, char *argv[])
{
    // Create the QApplication object to manage application-wide resources
    QApplication a(argc, argv);

    // Attempt to open the database connection via singleton DatabaseManager
    if (!DatabaseManager::instance().openDatabase()) {
        qDebug() << "Database failed to open!";
        return -1;  // Exit application if database cannot open
    }

    // Create and show the login window
    login loginWindow;
    loginWindow.show();

    // Enter the Qt event loop
    return a.exec();
}
