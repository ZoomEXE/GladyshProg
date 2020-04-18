#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    removeButton = "background-color: green;"
                   "border-style: solid;"
                   "border-width: 2px;"
                   "border-radius: 0px;"
                   "border-color: red;";

    greenButton = "background-color: green;";
    redButton = "background-color: red";

    ui->gridLayout->setVerticalSpacing(70);
    ui->gridLayout->setHorizontalSpacing(70);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Добавление хранилища
void MainWindow::addItem(QString name, int x, int y)
{
    //Отключаем режим удаления
    removeble = false;
    removeAlert(removeble);

    QDynamicButton *button = new QDynamicButton(this);  // Создаем объект динамической кнопки
    /* Устанавливаем текст с номером этой кнопки
     * */
    button->setText(name);
    button->setStyleSheet(greenButton);
    button->setMinimumSize(120, 120);
    button->setMaximumSize(120, 120);
    /* Добавляем кнопку в GridLayout
     * */
    ui->gridLayout->addWidget(button, y, x);
    /* Подключаем сигнал нажатия кнопки к СЛОТ получения номера кнопки
     * */
    connect(button, SIGNAL(clicked()), this, SLOT(slotGetNumber()));
    connect(button, SIGNAL(clicked()), this, SLOT(removeItem()));
}

void MainWindow::on_addItem_triggered()
{
    ui->statusbar->showMessage("Добавить хранилище");
    Dialog *add = new Dialog();
    connect(add, SIGNAL(newItemCharacter(QString, int, int)), this, SLOT(addItem(QString, int, int)));

    add->show();

}

//Получение номера кнопки
void MainWindow::slotGetNumber()
{
    if(removeble)
    {
    // Определяем объект, который вызвал сигнал
        QDynamicButton *button = (QDynamicButton*) sender();
    }
}

//По нажатию клавиши Esc деактивируется режим удаления
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(removeble && event->key() == Qt::Key_Escape)
    {
        removeble = false;
        removeAlert(removeble); //Функция для оповещения об активации режима удаления
    }
}

// Активация/деактивация режима удаления
void MainWindow::on_removeItem_triggered()
{
    ui->statusbar->showMessage("Нажмите на хранилище для его удаления");
    if(removeble)
    {
        removeble = false;
        removeAlert(removeble);
    }
    else
    {
        removeble = true;
        removeAlert(removeble);
    }
}

//Функция для оповещения об активации режима удаления
void MainWindow::removeAlert(bool flag)
{
    if(flag)
    {
        for(int i = 0; i < ui->gridLayout->count(); i++){
            /* Производим каст элемента слоя в объект динамической кнопки
             * */
            QDynamicButton *button = qobject_cast<QDynamicButton*>(ui->gridLayout->itemAt(i)->widget());
            //Подсветка кнопок красным
            button->setStyleSheet(removeButton);

        }
    }
    else
    {
        for(int i = 0; i < ui->gridLayout->count(); i++){

            QDynamicButton *button = qobject_cast<QDynamicButton*>(ui->gridLayout->itemAt(i)->widget());
            //Возвращение нормального вида кнопок
            button->setStyleSheet(greenButton);
        }
    }
}

//Получение номера и удаление кнопки при активированном режиме удаления
void MainWindow::removeItem()
{
    if(removeble)
    {
    // Определяем объект, который вызвал сигнал
        QDynamicButton *button = (QDynamicButton*) sender();
        button->hide();
        delete button;
        if(ui->gridLayout->count() == 0) removeble = false;
    }
}
