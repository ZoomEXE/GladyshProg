#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Стиль удаляемой кнопки
    removeButton = "background-color: green;"
                   "border-style: solid;"
                   "border-width: 2px;"
                   "border-radius: 0px;"
                   "border-color: red;";

    //Стили кнопок в нормальном состоянии, состоянии тревоги и снятом с охраны
    greenButton = "QDynamicButton {background-color: green}";
    redButton = "QDynamicButton {background-color: red}";


    ui->gridLayout->setVerticalSpacing(30);
    ui->gridLayout->setHorizontalSpacing(70);
    //QLabel *title = new QLabel("asdasd");
    //ui->gridLayout->addWidget(title, 0, 0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Добавление хранилища
void MainWindow::addItem(QString name, int x, int y)
{
    //Отключаем режим удаления
    if(removeble) addLOG("Режим удаления деактивирован.");
    removeble = false;
    removeAlert(removeble);

    QDynamicButton *button = new QDynamicButton(this);  // Создаем объект динамической кнопки
    /* Устанавливаем текст с номером этой кнопки
     * */
    button->setText(name);
    button->setStyleSheet(greenButton);
    button->setMinimumSize(120, 50);
    button->setMaximumSize(120, 50);
    connect(button, SIGNAL(sendLOG(QString)), this, SLOT(addLOG(QString)));

    //Создаем выпадающее меню для кнопки
    QMenu *pmenu = new QMenu(button);
    pmenu->addAction("Снять с охраны", button, SLOT(disarm()));
    pmenu->addAction("Поставить на охрану", button, SLOT(arm()));
    QMenu *subMenu = new QMenu("Отмена:", button);
    subMenu->addAction("Ложное срабатывание", button, SLOT(falseAlarm()));
    subMenu->addAction("Сбой", button, SLOT(failure()));
    subMenu->addAction("Пожар", button, SLOT(fire()));
    subMenu->addAction("Проникновение", button, SLOT(penetration()));
    pmenu->addMenu(subMenu);
    pmenu->addAction("Удалить", button, SLOT(removing()));

    connect(button, SIGNAL(sendRemove()), this, SLOT(removeItem()));
    connect(this, SIGNAL(sendAlert(int)), button, SLOT(alert(int)));
    connect(this, SIGNAL(sendFireAlert(int)), button, SLOT(fireAlert(int)));
    connect(this, SIGNAL(sendArm()), button, SLOT(arm()));
    connect(this, SIGNAL(sendDisarm()), button, SLOT(disarm()));
    connect(button, SIGNAL(sendStop()), this, SLOT(eraseLabel()));
    button->setMenu(pmenu);

    /* Добавляем кнопку в GridLayout
     * */
    ui->gridLayout->addWidget(button, y, x);
    QPair<QString, QPair<int, int>> temp;
    temp.second.first = x;
    temp.second.second = y;
    temp.first = name;
    items.push_back(temp);
    itemsID.push_back(button->getID());
    addLOG("Добавлено хранилище \"" + name + "\".");
}

//Открытие диалогового окна для добавления хранилища
void MainWindow::on_addItem_triggered()
{
    ui->statusbar->showMessage("Добавить хранилище");
    Dialog *add = new Dialog();
    add->setModal(true);
    connect(this, SIGNAL(sendItems(QVector<QPair<QString, QPair<int, int>>>)),
            add, SLOT(getItems(QVector<QPair<QString, QPair<int, int>>>)));

    connect(add, SIGNAL(newItemCharacter(QString, int, int)),
            this, SLOT(addItem(QString, int, int)));

    emit sendItems(items);
    add->show();

}

//Получение номера кнопки
void MainWindow::slotGetNumber()
{
    /*if(removeble)
    {
    // Определяем объект, который вызвал сигнал
        QDynamicButton *button = (QDynamicButton*) sender();
    }*/
}

//По нажатию клавиши Esc деактивируется режим удаления
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(removeble && event->key() == Qt::Key_Escape)
    {
        removeble = false;
        removeAlert(removeble); //Функция для оповещения об активации режима удаления
        addLOG("Режим удаления деактивирован.");
    }

    if(event->key() == Qt::Key_Shift)
    {
        if(!items.empty())
        {
            removeble = false;
            removeAlert(removeble);
            addLOG("Режим удаления деактивирован.");
            int ID = QTime::currentTime().second() % itemsID.size();
            sendAlert(itemsID[ID]);
            ui->label->setText("В хранилище \"" + items[ID].first + "\" сработала охранная сигнализация!");
        }
    }

    if(event->key() == Qt::Key_Control)
    {
        if(!items.empty())
        {
            removeble = false;
            removeAlert(removeble);
            addLOG("Режим удаления деактивирован.");
            int ID = QTime::currentTime().second() % itemsID.size();
            sendFireAlert(itemsID[ID]);
            ui->label->setText("В хранилище \"" + items[ID].first + "\" сработала пожарная сигнализация!");
        }
    }
}

//Очистка Label
void MainWindow::eraseLabel()
{
    ui->label->clear();
}
// Активация/деактивация режима удаления
void MainWindow::on_removeItem_triggered()
{
    ui->statusbar->showMessage("Нажмите на хранилище для его удаления / Нажмите Esc для отключения режима удаления");
    if(removeble)
    {
        removeble = false;
        removeAlert(removeble);
        addLOG("Режим удаления деактивирован.");
    }
    else
    {
        removeble = true;
        removeAlert(removeble);
        addLOG("Режим удаления активирован.");
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
        for(int i = 0; i < ui->gridLayout->count(); i++)
        {
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
        // Удаляем элемент
        for(int i = 0; i < itemsID.size(); ++i)
        {
            if(button->getID() == itemsID[i])
            {
                items.remove(i);
                itemsID.remove(i);
                break;
            }
        }

        addLOG("Удалено хранилище \"" + button->text() + "\".");
        button->hide();
        //delete button;
        if(items.size() == 0)
        {
            removeble = false;
             addLOG("Режим удаления деактивирован.");
        }
    }
    else
    {
        ui->statusbar->showMessage("Включите режим удаления: Конструктор->Удалить");
    }
}

//Логирование событий
void MainWindow::addLOG(QString message)
{
    QString time = QTime::currentTime().toString() + " ";
    ui->textBrowser->append(time + message);
}

//Сохранить конфигурацию
void MainWindow::on_save_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Сохранить конфигурацию"), "",
        tr("Файлы конфигурации ТСО (*.tso);;"));
    if(fileName != "")
    {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
                    // error message
        }
        else
        {
            QTextStream stream(&file);
            stream << ui->title->text() << endl;
            for(int i = 0; i < items.size(); ++i)
            {
                stream << items[i].first << " $ " << items[i].second.first << " $ "
                       << items[i].second.second << " $ " << itemsID[i] << endl;
            }
            addLOG("Конфигурация сохранена в файл \"" + fileName + "\".");
            file.close();
        }
    }

}

//Загрузить конфигурацию ТСО
void MainWindow::on_load_triggered()
{
    for(int i = 0; i < ui->gridLayout->count(); i++)
    {
        QDynamicButton *button = qobject_cast<QDynamicButton*>(ui->gridLayout->itemAt(i)->widget());
        //Возвращение нормального вида кнопок
        button->hide();
    }
    items.clear();
    itemsID.clear();
    QVector <QPair <QString, QPair <int, int>>> tempItems;
    QVector <int> tempItemsID;
    QString fileName = QFileDialog::getOpenFileName(this, tr("Загрузить конфигурацию"), "",
        tr("Файлы конфигурации ТСО (*.tso);;"));
    if(fileName != "")
    {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
                    // error message
        }
        else
        {
            QTextStream stream(&file);
            QStringList load = stream.readAll().split("\n");
            ui->title->setText(load[0]);
            for(int i = 1; i < load.size() - 1; ++i)
            {
                QStringList loadElement = load[i].split(" $ ");
                QPair <QString, QPair <int, int>> temp;
                temp.first = loadElement[0];
                temp.second.first = loadElement[1].toInt();
                temp.second.second = loadElement[2].toInt();
                tempItems.push_back(temp);
                tempItemsID.push_back(loadElement[3].toInt());

                QString name = temp.first;
                int x = temp.second.first, y = temp.second.second;
                addItem(name, x, y);
            }
            addLOG("Конфигурация загружена из файла \"" + fileName + "\".");
            file.close();
        }
    }
}

void MainWindow::on_rename_triggered()
{
    Dialogi *rename = new Dialogi();
    rename->setModal(true);
    rename->show();
    connect(rename, SIGNAL(sendName(QString)), this, SLOT(rename(QString)));
}

void MainWindow::rename(QString name)
{
    ui->title->setText(name);
}
