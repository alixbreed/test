#include "editwindow.h"
#include "ui_editwindow.h"

EditWindow::EditWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EditWindow)
{
    ui->setupUi(this);
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
}

EditWindow::~EditWindow()
{
    delete ui;
}

void EditWindow::on_pbCancel_clicked()
{
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    this->close();
}


void EditWindow::on_pbSave_clicked()
{
    if(!ui->lineEdit->text().isEmpty()
            && !ui->lineEdit_2->text().isEmpty())
    {
        XMLOperator xml;
        if (xml.isHexId(ui->lineEdit->text().toUpper()))
        {
            xml.addItem(ui->lineEdit->text().toUpper(), ui->lineEdit_2->text());
            ui->lineEdit->clear();
            ui->lineEdit_2->clear();
            this->close();
        }
        else
        {
            QMessageBox msg;
            msg.setText(ui->lineEdit->text().toUpper() +
                        " нерпавильный идентификатор");
            msg.exec();
        }
    }

}

void EditWindow::on_lineEdit_returnPressed()
{
    XMLOperator xml;
    QString str = xml.getNameByID(ui->lineEdit->text().toUpper());
    if (xml.isHexId(ui->lineEdit->text().toUpper()))
    {
        if (!str.isEmpty())
            ui->lineEdit_2->setText(str);
        ui->lineEdit_2->setFocus();
    }
    else
    {
        QMessageBox msg;
        msg.setText(str + "нерпавильны идентификатор");
        msg.exec();
    }
}
