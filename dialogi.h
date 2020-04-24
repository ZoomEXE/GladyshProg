#ifndef DIALOGI_H
#define DIALOGI_H

#include <QDialog>

namespace Ui {
class Dialogi;
}

class Dialogi : public QDialog
{
    Q_OBJECT

public:
    explicit Dialogi(QWidget *parent = nullptr);
    ~Dialogi();

private:
    Ui::Dialogi *ui;

signals:
    void sendName(QString name);
private slots:
    void on_buttonBox_accepted();
};

#endif // DIALOGI_H
