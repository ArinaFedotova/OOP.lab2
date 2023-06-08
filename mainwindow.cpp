#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

#define PIXELS 29;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("JSON file");
    connect(ui->btn_choose_file, &QPushButton::clicked, this, &MainWindow::on_btn_choose_file_clicked);
    connect(ui->btn_check_file, &QPushButton::clicked, this, &MainWindow::on_btn_check_file_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_choose_file_clicked() {
    QString filename = QFileDialog::getOpenFileName(this, "Choose file", "", "*.json");
    if (filename.isEmpty()) {
        ui->lbl_file_name->setText("File was not opened");
    }
    else {
        facade.fp = filename.toStdString();
        ui->lbl_file_name->setText(filename);
        std::string res = facade.read_operation(facade.fp);
        ui->lbl_json->setText(QString::fromStdString(res));

        QLabel *outputForm = ui->lbl_json;
        QWidget *sawc = ui->scrollAreaWidgetContents; //scroll widget contents реализация прокрутки
        int cal = outputForm->text().count("\n") * PIXELS; // длину кторорую нам надо сделать = кол-во строк * кол-во пикселей
        sawc->setMinimumHeight(cal); // изменяем высоту
        outputForm->setGeometry(outputForm->x(), outputForm->y(), outputForm->width(), cal); // меняем высоту у json label
    }
}

void MainWindow::on_btn_check_file_clicked() {
    try {
        std::string res_new = facade.read_operation(facade.fp); // считываем файл и получаем текст
        facade.check_operation(res_new); // выкинет ошибку или ничего не будет
        std::string message = "File is correct!";
        ui->lbl_result->setText(QString::fromStdString(message));
    }  catch (Json_errors& errors) {
        const char* json_error = errors.what();
        ui->lbl_result->setText(json_error);
    } catch (System_errors& errors) {
        const char* system_error = errors.what();
        ui->lbl_result->setText(system_error);
    }
    facade.rollback(); // очистит данные
}
