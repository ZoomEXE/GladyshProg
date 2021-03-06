#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->tableWidget->horizontalHeader()->hide();
    ui->tableWidget->verticalHeader()->hide();
    ui->tableWidget->setRowCount(7);
    ui->tableWidget->setColumnCount(7);
    for(int i = 0; i < ui->tableWidget->rowCount(); ++i)
    {
        ui->tableWidget->setRowHeight(i, 100);
        for(int j = 0; j < ui->tableWidget->columnCount(); ++j)
        {
            ui->tableWidget->item(i, j)->setText("");
            ui->tableWidget->item(i, j)->setTextAlignment(Qt::AlignCenter);
        }
    }
    for(int i = 0; i < ui->tableWidget->columnCount(); ++i)
    {
        ui->tableWidget->setColumnWidth(i, 100);
    }

}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_tableWidget_cellClicked(int row, int column)
{
    //if(ui->tableWidget->item(row, column)->text() == "")
    //{
        y = row;
        x = column;
    //}
    //else
   /* {
        QMessageBox *allert = new QMessageBox();
        allert->setText("На выбранном Вами месте уже установленны ТСО");
        allert->show();
    }*/

}

void Dialog::on_buttonBox_accepted()
{
    if(ui->lineEdit->text() == "")
    {
        QMessageBox *allert = new QMessageBox();
        allert->setText("Введите наименование");
        allert->show();
    }
    else
    {
        name = ui->lineEdit->text();
        emit newItemCharacter(name, x, y);
    }

}

void Dialog::getItems(QVector<QPair<QString, QPair<int, int>>> items)
{
    for(auto i = items.begin(); i < items.end(); ++i)
    {
        ui->tableWidget->item(i->second.second, i->second.first)->setText(i->first);
        ui->tableWidget->item(i->second.second, i->second.first)->setBackground(Qt::green);
    }
}
