#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "clientinterface.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    ClientInterface *clientInt = nullptr;

private slots:
    void on_btn_create_clicked();

    void on_btn_list_clicked();

    void on_btn_get_clicked();

    void on_btn_delete_clicked();

    void on_btn_update_clicked();

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager * m_client = nullptr;

};

#endif // MAINWINDOW_H
