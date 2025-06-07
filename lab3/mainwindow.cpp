#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    clientInt = ClientInterface::getInstance();

}

MainWindow::~MainWindow()
{
    clientInt->deleteLater();
    delete ui;
}

void MainWindow::on_btn_create_clicked()
{
    clientInt->Create();
}


void MainWindow::on_btn_list_clicked()
{
    clientInt->List();
}


void MainWindow::on_btn_get_clicked()
{
    clientInt->Get(ui->in_get->value());
}


void MainWindow::on_btn_delete_clicked()
{
    clientInt->Delete(ui->in_delete->value());

}


void MainWindow::on_btn_update_clicked()
{
    clientInt->Update(ui->in_update->value());
}

