#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Добавление хранилища
void MainWindow::on_addItem_triggered()
{
    ui->statusbar->showMessage("Добавить хранилище");

    //Отключаем режим удаления
    removeble = false;
    removeAlert(removeble);

    QDynamicButton *button = new QDynamicButton(this);  // Создаем объект динамической кнопки
    /* Устанавливаем текст с номером этой кнопки
     * */
    button->setText("Хранилище #" + QString::number(button->getID()));
    /* Добавляем кнопку в GridLayout
     * */
    ui->gridLayout->addWidget(button, ui->gridLayout->count() / 3, ui->gridLayout->count() % 3);
    /* Подключаем сигнал нажатия кнопки к СЛОТ получения номера кнопки
     * */
    connect(button, SIGNAL(clicked()), this, SLOT(slotGetNumber()));
    connect(button, SIGNAL(clicked()), this, SLOT(removeItem()));
}

//Получение номера и удаление кнопки при активированном режиме удаления
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
            button->setStyleSheet("border-style: solid;"
                                  "border-width: 2px;"
                                  "border-radius: 0px;"
                                  "border-color: red;");

        }
    }
    else
    {
        for(int i = 0; i < ui->gridLayout->count(); i++){

            QDynamicButton *button = qobject_cast<QDynamicButton*>(ui->gridLayout->itemAt(i)->widget());
            //Возвращение нормального вида кнопок
            button->setStyleSheet("");
        }
    }
}

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
