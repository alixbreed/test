#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidget>
#include <QLineEdit>
#include "editwindow.h"
#include "xmloperator.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void processTreeWidget(QTreeWidget* addTree, QTreeWidget* subTree, QLineEdit* line);
    
private slots:
    void on_pbClear_clicked();

    void on_action_exit_triggered();

    void on_action_edit_triggered();

    void on_lineEdit_returnPressed();

    void on_lineEdit_2_returnPressed();

private:
    Ui::MainWindow *ui;
    EditWindow* ew;
};

#endif // MAINWINDOW_H
