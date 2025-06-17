#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Include the base class for main application windows in Qt
#include <QMainWindow>

// Begin and end namespace macros to avoid naming conflicts
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

// MainWindow class declaration, derived from QMainWindow
class MainWindow : public QMainWindow
{
    Q_OBJECT  // Enables Qt's meta-object features like signals and slots

public:
    // Constructor - creates an instance of MainWindow
    explicit MainWindow(QWidget *parent = nullptr);

    // Destructor - cleans up any resources used by MainWindow
    ~MainWindow();

private:
    // Pointer to the UI class generated from mainwindow.ui by Qt Designer
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
