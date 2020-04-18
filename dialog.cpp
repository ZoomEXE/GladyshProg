#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->tableWidget->horizontalHeader()->hide();
    ui->tableWidget->verticalHeader()->hide();
    for(int i = 0; i < ui->tableWidget->rowCount(); ++i)
    {
        ui->tableWidget->setRowHeight(i, 100);
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
