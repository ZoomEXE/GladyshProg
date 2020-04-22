#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLayout>
#include <QPushButton>
#include <QLabel>
#include <QKeyEvent>
#include <QStyle>
#include <QTime>
#include <QMenu>
#include <QSound>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>

#include "dialog.h"
#include "qdynamicbutton.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT
    QString greenButton, redButton, yellowButton, removeButton;
    QVector <QPair<QString, QPair<int, int>>> items;
    QVector <int> itemsID;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool removeble = false;
    //QSound *alertSound;
    void removeAlert (bool flag);
    void alert(int ID);

private slots:
    void on_addItem_triggered();                    // СЛОТ-обработчик нажатия кнопки добавления
    void slotGetNumber();                           // СЛОТ для получения номера нажатой динамической кнопки
    void on_removeItem_triggered();                 // СЛОТ для активации режима удаления
    void removeItem();                              // СЛОТ для удаления элемента
    void addLOG(QString message);                   // СЛОТ для логирования событий
    void eraseLabel();                              // СЛОТ для очистки текстовой строки
    void on_save_triggered();
    void on_load_triggered();

private:
    Ui::MainWindow *ui;

protected:
    virtual void keyPressEvent(QKeyEvent *event);   // СЛОТ для отлавливания нажатия клавиши Esc
public slots:
    void addItem(QString name, int x, int y);       // СЛОТ для получения данных о новом элементе
    //void stopAlert();                               // СЛОТ для отключения тревоги
signals:
    void sendItems(QVector<QPair<QString, QPair<int, int>>> items);
    void sendAlert(int ID);
    void sendFireAlert(int ID);
    void sendArm();
    void sendDisarm();
};
#endif // MAINWINDOW_H
