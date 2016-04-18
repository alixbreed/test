#ifndef EDITWINDOW_H
#define EDITWINDOW_H

#include <QMainWindow>
#include "xmloperator.h"

namespace Ui {
class EditWindow;
}

class EditWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit EditWindow(QWidget *parent = 0);
    ~EditWindow();

private slots:
    void on_pbCancel_clicked();

    void on_pbSave_clicked();

    void on_lineEdit_returnPressed();

private:
    Ui::EditWindow *ui;
};

#endif // EDITWINDOW_H
