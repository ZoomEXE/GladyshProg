#ifndef QDYNAMICBUTTON_H
#define QDYNAMICBUTTON_H

#include <QPushButton>
#include <QMenu>

class QDynamicButton : public QPushButton
{
    Q_OBJECT
public:
    explicit QDynamicButton(QWidget *parent = 0);
    ~QDynamicButton();
    static int ResID;   // Статическая переменная, счетчик номеров кнопок
    int getID();        // Функция для возврата локального номера кнопки
    QString yellowButton, greenButton, redButton;

public slots:
    // СЛОТЫ для выпадающего меню
    void arm();                                     // СЛОТ для постановки на охрану
    void disarm();                                  // СЛОТ для снятия с охраны
    void falseAlarm();                              // СЛОТ для ложного срабатывания
    void failure();                                 // СЛОТ для сбоя
    void fire();                                    // СЛОТ для пожара
    void penetration();                             // СЛОТ для проникновения
    void removing();                                // СЛОТ для удаления
private:
    int buttonID = 0;   // Локальная переменная, номер кнопки
signals:
    void sendLOG(QString LOG);
    void sendRemove();
};

#endif // QDYNAMICBUTTON_H
