#include "dialogi.h"
#include "ui_dialogi.h"

Dialogi::Dialogi(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialogi)
{
    ui->setupUi(this);
}

Dialogi::~Dialogi()
{
    delete ui;
}

void Dialogi::on_buttonBox_accepted()
{
    emit sendName(ui->textEdit->toPlainText().trimmed());
}
