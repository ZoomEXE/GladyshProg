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
    redButton = "QDynamicButton {background-color: red}";
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
}

//Постановка на охрану
void QDynamicButton::arm()
{
    QDynamicButton *button = (QDynamicButton*) sender()->parent()->parent();
    button->setStyleSheet(greenButton);
    emit sendLOG("Хранилище \"" + button->text() + "\"" + " поставлено на охрану.");
    alertSound->stop();
}

//Ложное срабатывание
void QDynamicButton::falseAlarm()
{
    QDynamicButton *button = (QDynamicButton*) sender()->parent()->parent();
    button->setStyleSheet(greenButton);
    emit sendLOG("В хранилище \"" + button->text() + "\"" + " произошло ложное срабатывание.");
    alertSound->stop();
}

//Сбой
void QDynamicButton::failure()
{
    QDynamicButton *button = (QDynamicButton*) sender()->parent()->parent();
    button->setStyleSheet(greenButton);
    emit sendLOG("В хранилище \"" + button->text() + "\"" + " произошел сбой.");
    alertSound->stop();
}

//Пожар
void QDynamicButton::fire()
{
    QDynamicButton *button = (QDynamicButton*) sender()->parent()->parent();
    button->setStyleSheet(greenButton);
    emit sendLOG("В хранилище \"" + button->text() + "\"" + " произошел пожар.");
    alertSound->stop();
}

//Проникновение
void QDynamicButton::penetration()
{
    QDynamicButton *button = (QDynamicButton*) sender()->parent()->parent();
    button->setStyleSheet(greenButton);
    emit sendLOG("В хранилище \"" + button->text() + "\"" + " произошло проникновение.");
    alertSound->stop();
}

//Удаление
void QDynamicButton::removing()
{
    emit sendRemove();
}

//Включение тревоги
void QDynamicButton::alert(int ID)
{
    if(ID == buttonID) {
        this->setStyleSheet(redButton);
        emit sendLOG("В хранилище \"" + this->text() + "\" сработала сигнализация.");
        alertSound->setLoops(1000);
        alertSound->play();
    }
}
