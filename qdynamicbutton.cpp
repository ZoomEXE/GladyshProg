#include "qdynamicbutton.h"

QDynamicButton::QDynamicButton(QWidget *parent) :
    QPushButton(parent)
{
    ResID++;            // Увеличение счетчика на единицу
    buttonID = ResID;   /* Присвоение кнопке номера, по которому будет производиться
                         * дальнейшая работа с кнопок
                         * */
    alertSound = new QSound(":/audio/Overspeed Warning.wav");
    greenButton = "QDynamicButton {background-color: green}";
    redButton = "QDynamicButton {background-color: rgb(255, 0, 0)}";
    yellowButton = "QDynamicButton {background-color: yellow}";
}

QDynamicButton::~QDynamicButton()
{

}

/* Метод для возврата значения номера кнопки
 * */
int QDynamicButton::getID()
{
    return buttonID;
}

/* Инициализация статической переменной класса.
 * Статическая переменная класса должна инициализироваться в обязательном порядке
 * */
int QDynamicButton::ResID = 0;

//Снятие с охраны
void QDynamicButton::disarm()
{
    QDynamicButton *button = (QDynamicButton*) sender()->parent()->parent();
    button->setStyleSheet(yellowButton);
    emit sendLOG("Хранилище \"" + button->text() + "\"" + " снято с охраны.");
    alertSound->stop();
    isArmed = false;
}

//Постановка на охрану
void QDynamicButton::arm()
{
    QDynamicButton *button = (QDynamicButton*) sender()->parent()->parent();
    button->setStyleSheet(greenButton);
    emit sendLOG("Хранилище \"" + button->text() + "\"" + " поставлено на охрану.");
    alertSound->stop();
    isArmed = true;
}

//Ложное срабатывание
void QDynamicButton::falseAlarm()
{
    QDynamicButton *button = (QDynamicButton*) sender()->parent()->parent();
    button->setStyleSheet(greenButton);
    emit sendLOG("В хранилище \"" + button->text() + "\"" + " произошло ложное срабатывание.");
    alertSound->stop();
    isArmed = true;
}

//Сбой
void QDynamicButton::failure()
{
    QDynamicButton *button = (QDynamicButton*) sender()->parent()->parent();
    button->setStyleSheet(greenButton);
    emit sendLOG("В хранилище \"" + button->text() + "\"" + " произошел сбой.");
    alertSound->stop();
    isArmed = true;
}

//Пожар
void QDynamicButton::fire()
{
    QDynamicButton *button = (QDynamicButton*) sender()->parent()->parent();
    button->setStyleSheet(greenButton);
    emit sendLOG("В хранилище \"" + button->text() + "\"" + " произошел пожар.");
    alertSound->stop();
    isArmed = true;
}

//Проникновение
void QDynamicButton::penetration()
{
    QDynamicButton *button = (QDynamicButton*) sender()->parent()->parent();
    button->setStyleSheet(greenButton);
    emit sendLOG("В хранилище \"" + button->text() + "\"" + " произошло проникновение.");
    alertSound->stop();
    isArmed = true;
}

//Удаление
void QDynamicButton::removing()
{
    emit sendRemove();
}

//Включение охранной тревоги
void QDynamicButton::alert(int ID)
{
    if(ID == buttonID && isArmed) {
        this->setStyleSheet(redButton);
        emit sendLOG("В хранилище \"" + this->text() + "\" сработала охранная сигнализация.");
        alertSound->setLoops(1000);
        alertSound->play();
    }
}

//Включение пожарной тревоги
void QDynamicButton::fireAlert(int ID)
{
    if(ID == buttonID && isArmed) {
        this->setStyleSheet(redButton);
        emit sendLOG("В хранилище \"" + this->text() + "\" сработала пожарная сигнализация.");
        alertSound->setLoops(1000);
        alertSound->play();
    }
}
