#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void Calculation(); //функция для вычисений, закрплена за большой синей кнопкой
    void Del();
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
