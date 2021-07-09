#ifndef MYTODO_H
#define MYTODO_H

#include <QMainWindow>
#include <QMessageBox>
#include <QtSql>
#include <QFileInfo>
#include <QDebug>
#include "editar.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MyTodo; }
QT_END_NAMESPACE

class MyTodo : public QMainWindow{
    Q_OBJECT

public:
    MyTodo(QWidget *parent = nullptr);
    QString home = getenv("HOME");

    void start();
    QString dir=":/mytodo.db";
    QString user = home + "/.config/mytodo.db";

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    QSqlQuery query;
    QString sql = "";
    QString str_todo = "";

    void show_data();

    void clear_table();

    ~MyTodo();

private slots:
    void on_actionSair_triggered();

    void on_actionSobre_MyTodo_triggered();

    void on_btn_add_clicked();

    void on_tb_show_cellClicked(int row, int column);

private:
    Ui::MyTodo *ui;
};
#endif // MYTODO_H
