#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "facade.h"
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

private slots:
    void on_btn_choose_file_clicked();
    void on_btn_check_file_clicked();

private:
    Ui::MainWindow *ui;
    Facade facade;
};
#endif // MAINWINDOW_H
