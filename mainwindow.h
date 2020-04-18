#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLayout>
#include <QPushButton>
#include <QLabel>
#include "qdynamicbutton.h"
#include <QKeyEvent>
#include <QStyle>

#include <dialog.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QString greenButton, redButton, removeButton;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool removeble = false;
    void removeAlert (bool flag);
private slots:
    void on_addItem_triggered();                    // СЛОТ-обработчик нажатия кнопки добавления
    void slotGetNumber();                           // СЛОТ для получения номера нажатой динамической кнопки

    void on_removeItem_triggered();                 //СЛОТ для активации режима удаления
    void removeItem();                              //СЛОТ для удаления элемента
private:
    Ui::MainWindow *ui;

protected:
    virtual void keyPressEvent(QKeyEvent *event);   //СЛОТ для отлавливания нажатия клавиши Esc
public slots:
    void addItem(QString name, int x, int y);       //СЛОТ для получения данных о новом элементе
};
#endif // MAINWINDOW_H
