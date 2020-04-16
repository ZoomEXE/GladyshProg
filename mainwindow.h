#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLayout>
#include <QPushButton>
#include <QLabel>
#include "qdynamicbutton.h"
#include "removedialog.h"
#include <QKeyEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool removeble = false;
    void removeAlert (bool flag);
private slots:
    void on_addItem_triggered();      // СЛОТ-обработчик нажатия кнопки добавления
  //void on_removeItem_triggered(); // СЛОТ-обработчик нажатия кнопки удаления
    void slotGetNumber();           // СЛОТ для получения номера нажатой динамической кнопки

    void on_removeItem_triggered();
    void removeItem();
private:
    Ui::MainWindow *ui;

protected:
    virtual void keyPressEvent(QKeyEvent *event);

};
#endif // MAINWINDOW_H
