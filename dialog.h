#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QString>
#include <QMessageBox>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT
int x, y;
QString name;
public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private:
    Ui::Dialog *ui;

signals:
    void newItemCharacter(QString name, int x, int y);
private slots:
    void on_tableWidget_cellClicked(int row, int column);
    void on_buttonBox_accepted();
};

#endif // DIALOG_H
