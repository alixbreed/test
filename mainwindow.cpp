#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QStringList ColumnNames;
    ColumnNames << "Наименование" << "Количество";
    ui->treeWidget->setHeaderLabels(ColumnNames);
    ui->treeWidget_2->setHeaderLabels(ColumnNames);
    ew = new EditWindow(this);
}

MainWindow::~MainWindow()
{
    ew->close();
    delete ew;
    delete ui;
}

void MainWindow::on_pbClear_clicked()
{
    ui->treeWidget->clear();
    ui->treeWidget_2->clear();
}

void MainWindow::on_action_exit_triggered()
{
    close();
}

void MainWindow::on_action_edit_triggered()
{
    ew->show();
}

void MainWindow::on_lineEdit_returnPressed()
{
    processTreeWidget(ui->treeWidget, ui->treeWidget_2, ui->lineEdit);
    ui->lineEdit->clear();
}

void MainWindow::on_lineEdit_2_returnPressed()
{
    processTreeWidget(ui->treeWidget_2, ui->treeWidget, ui->lineEdit_2);
    ui->lineEdit_2->clear();
}

void MainWindow::processTreeWidget(QTreeWidget* addTree, QTreeWidget* subTree, QLineEdit* line)
{
    XMLOperator xml;
    QStringList input(line->text().split(' '));
    QMap<QString, QString> mapItems;
    QList<QTreeWidgetItem*> listItems;
    QMessageBox msg;

    for(int i=0; i<input.size(); i++)
    {
        QString val = xml.getNameByID(input.at(i).toUpper());
        if (!xml.isHexId(input.at(i).toUpper()))
        {
            msg.setText(input.at(i).toUpper() + " неправильный идентификатор");
            msg.exec();
            continue;
        }
        if (!val.isEmpty())
            mapItems.insert(input.at(i).toUpper(), val);
    }

    QMapIterator<QString, QString> mapItr(mapItems);
    while(mapItr.hasNext())
    {
        mapItr.next();
        QTreeWidgetItem* item = new QTreeWidgetItem();
        QTreeWidgetItem* child = new QTreeWidgetItem();
        listItems = addTree->findItems(mapItr.value(), Qt::MatchFixedString);
        bool isAdded;
        //Добавляем элемент в список или увеличиваем счетчик в списке
        if (listItems.isEmpty())
        {
            item->setText(0,mapItr.value());
            child->setText(0,mapItr.key());
            child->setText(1,QString::number(1));
            item->addChild(child);
            addTree->addTopLevelItem(item);
        }
        else
        {
            int childCount = listItems[0]->childCount();
            for(int i=0; i < childCount; i++)
            {
                if(listItems[0]->child(i)->text(0) == mapItr.key())
                {
                    int count = listItems[0]->child(i)->text(1).toInt();
                    listItems[0]->child(i)->setText(1, QString::number(++count));
                    isAdded = true;
                    break;
                }
            }
            if(!isAdded)
            {
                child->setText(0, mapItr.key());
                child->setText(1, QString::number(1));
                listItems[0]->addChild(child);
            }
        }

        //Уменьшаем счетчик во 2ом списке, если элемент есть
        listItems = subTree->findItems(mapItr.value(), Qt::MatchFixedString);
        if (!listItems.isEmpty())
        {
            for(int i=0; i < listItems[0]->childCount(); i++)
            {
                if ( listItems[0]->child(i)->text(0) == mapItr.key())
                {
                    int count = listItems[0]->child(i)->text(1).toInt();
                    if (count > 1)
                        listItems[0]->child(i)->setText(1, QString::number(--count));
                    else
                        listItems[0]->removeChild(listItems[0]->child(i));
                }
            }
            if (listItems[0]->childCount() == 0)
                delete listItems[0];
        }
    }
}
