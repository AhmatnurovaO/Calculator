#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include <QtCore/qmath.h>
#include <QtCore>
#include <QKeyEvent>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->btn,&QPushButton::clicked,
            this,&MainWindow::Calculation); //связь кнопки и функции
    connect(ui->btn_2,&QPushButton::clicked,
            this,&MainWindow::Del);
}
int nod(int a, int b) { //вычисление НОД для сокращения дробей
    while (b > 0) {
        int c = a % b;
        a = b;
        b = c;
    }
    return a;
}
void MainWindow::Calculation()
{
    if (ui->tabWidget->currentIndex()==0) //если открыта первая вкладка
    {
        int a=ui->lineEdit_1->text().toInt(); //получаем данные с полей ввода
        int b=ui->lineEdit_2->text().toInt();
        int c=ui->lineEdit_3->text().toInt();
        int d=ui->lineEdit_4->text().toInt();
        if (QString::number(a)!=ui->lineEdit_1->text())
        {
            QMessageBox::critical(this, "Ошибка","некорректный ввод");
            return;
        }
        if (QString::number(b)!=ui->lineEdit_2->text())
        {
            QMessageBox::critical(this, "Ошибка","некорректный ввод");
            return;
        }
        if (QString::number(c)!=ui->lineEdit_3->text())
        {
            QMessageBox::critical(this, "Ошибка","некорректный ввод");
            return;
        }
        if (QString::number(d)!=ui->lineEdit_4->text())
        {
            QMessageBox::critical(this, "Ошибка","некорректный ввод");
            return;
        }
        if (b==0 || d==0 || (c==0 && ui->comboBox->currentIndex()==3))
        {   //если знаменатели нули или если делим на нулевую дробь, то ошибка
            QMessageBox::critical(this, "Ошибка","некорректный ввод. деление на нуль");
            return;
        }
        int res1,res2,del;//числитель ответа, его знаменатель и вспомогательная переменная
        switch (ui->comboBox->currentIndex())  //+-×÷
        { //вычисляем
            case 0:
                res1=a*d+c*b;
                res2=b*d;
                break;
            case 1:
                res1=a*d-c*b;
                res2=b*d;
                break;
            case 2:
                res1=a*c;
                res2=b*d;
                break;
            case 3:
                res1=a*d;
                res2=b*c;
                break;
        }
        del=nod(abs(res1),abs(res2));//получаем НОД
        res1/=del;//делим числитель и знаменатель на него
        res2/=del;
        ui->lineEdit_5->setText(QString::number(res1));//пишем ответ
        ui->lineEdit_6->setText(QString::number(res2));
    }
    else if (ui->tabWidget->currentIndex()==1)//если открыта вторая вкладка
    {
        double a=ui->lineEdit_7->text().toDouble();
        double b=ui->lineEdit_8->text().toDouble();
        if (QString::number(a)!=ui->lineEdit_7->text())
        {
            QMessageBox::critical(this, "Ошибка","некорректный ввод");
            return;
        }
        if (QString::number(b)!=ui->lineEdit_8->text())
        {
            QMessageBox::critical(this, "Ошибка","некорректный ввод");
            return;
        }
        double res;
        if (b==0 && ui->comboBox_2->currentIndex()==3)
        {
            QMessageBox::critical(this, "Ошибка","некорректный ввод. деление на нуль");
            return;
        }
        switch (ui->comboBox_2->currentIndex())  //+-×÷
        {
            case 0:
                res=a+b;
                break;
            case 1:
                res=a-b;
                break;
            case 2:
                res=a*b;
                break;
            case 3:
                res=a/b;
                break;
        }
        ui->lineEdit_9->setText(QString::number(res));
    }
    else if (ui->tabWidget->currentIndex()==2)//если открыта третья вкладка
    {

        if (ui->lineEdit_10->text().size()==0 && ui->lineEdit_11->text().size()==0 &&
            ui->lineEdit_12->text().size()!=0)//если поле ввода обычной дроби пусто, а
            //поле десятичной заполнено
        {
            int res1,res2,del;
            double c=ui->lineEdit_12->text().toDouble();
            if (QString::number(c)!=ui->lineEdit_12->text())
            {
                QMessageBox::critical(this, "Ошибка","некорректный ввод");
                return;
            }
            int k;
            if (qCeil(c)==c) k=1;
            else k=qPow(10,ui->lineEdit_12->text().split(".")[1].size());//берем 10 в такой степени, сколько знаков стоит после запятой
            //1.2*10=12 3.45*100=345 ...
            res1=c*k;
            res2=k;
            del=nod(abs(res1),abs(res2));
            res1/=del;
            res2/=del;
            ui->lineEdit_10->setText(QString::number(res1));
            ui->lineEdit_11->setText(QString::number(res2));
        }
        else if (ui->lineEdit_10->text().size()!=0 && ui->lineEdit_11->text().size()!=0 &&
                 ui->lineEdit_12->text().size()==0)
            //если поля заполнены наоборот
        {
            int a=ui->lineEdit_10->text().toInt();
            int b=ui->lineEdit_11->text().toInt();
            if (QString::number(a)!=ui->lineEdit_10->text())
            {
                QMessageBox::critical(this, "Ошибка","некорректный ввод");
                return;
            }
            if (QString::number(b)!=ui->lineEdit_11->text())
            {
                QMessageBox::critical(this, "Ошибка","некорректный ввод");
                return;
            }
            if (b==0)
            {
                QMessageBox::critical(this, "Ошибка","некорректный ввод. деление на нуль");
                return;
            }
            ui->lineEdit_12->setText(QString::number(1.0*a/b));//просто делим числитель на знаменатель и умножаем на 1.0 чтоб компьютер опознал это как дробное число
        }
        else//если оба поля ввода пусты или оба заполнены, то нельзя понять чего хочет пользователь
        {
            QMessageBox::critical(this, "Ошибка","некорректный ввод\nтолько одна из областей ввода должна быть пустой");
            return;
        }
    }
}
void MainWindow::Del()
{
    ui->lineEdit_1->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->lineEdit_6->clear();
    ui->lineEdit_7->clear();
    ui->lineEdit_8->clear();
    ui->lineEdit_9->clear();
    ui->lineEdit_10->clear();
    ui->lineEdit_11->clear();
    ui->lineEdit_12->clear();
}
MainWindow::~MainWindow()
{
    delete ui;
}

