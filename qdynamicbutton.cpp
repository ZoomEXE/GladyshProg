#include "qdynamicbutton.h"

QDynamicButton::QDynamicButton(QWidget *parent) :
    QPushButton(parent)
{
    ResID++;            // Увеличение счетчика на единицу
    buttonID = ResID;   /* Присвоение кнопке номера, по которому будет производиться
                         * дальнейшая работа с кнопок
                         * */
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
}

//Постановка на охрану
void QDynamicButton::arm()
{
    QDynamicButton *button = (QDynamicButton*) sender()->parent()->parent();
    button->setStyleSheet(greenButton);
    emit sendLOG("Хранилище \"" + button->text() + "\"" + " поставлено на охрану.");
}

//Ложное срабатывание
void QDynamicButton::falseAlarm()
{
    QDynamicButton *button = (QDynamicButton*) sender()->parent()->parent();
    button->setStyleSheet(greenButton);
    emit sendLOG("В хранилище \"" + button->text() + "\"" + " произошло ложное срабатывание.");
}

//Сбой
void QDynamicButton::failure()
{
    QDynamicButton *button = (QDynamicButton*) sender()->parent()->parent();
    button->setStyleSheet(greenButton);
    emit sendLOG("В хранилище \"" + button->text() + "\"" + " произошел сбой.");
}

//Пожар
void QDynamicButton::fire()
{
    QDynamicButton *button = (QDynamicButton*) sender()->parent()->parent();
    button->setStyleSheet(greenButton);
    emit sendLOG("В хранилище \"" + button->text() + "\"" + " произошел пожар.");
}

//Проникновение
void QDynamicButton::penetration()
{
    QDynamicButton *button = (QDynamicButton*) sender()->parent()->parent();
    button->setStyleSheet(greenButton);
    emit sendLOG("В хранилище \"" + button->text() + "\"" + " произошло проникновение.");
}

//Удаление
void QDynamicButton::removing()
{
    emit sendRemove();
}
