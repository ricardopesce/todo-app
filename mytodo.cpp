#include "mytodo.h"
#include "ui_mytodo.h"

MyTodo::MyTodo(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MyTodo){
    ui->setupUi(this);
}

MyTodo::~MyTodo(){
    delete ui;
}


void MyTodo::on_actionSair_triggered(){
    close();
}

void MyTodo::on_actionSobre_MyTodo_triggered(){
    QMessageBox::about(this, "Sobre esse programa",
                       "<h2>My ToDo 1.0.0</h2>"
                       "<p>Projeto Desenvolvido para o Curso de Qt Moderno com C++<br>"
                       "prof. Marcos Oliveira<br>"
                       "Adaptado por Ricardo Pesce</p>"
                       "<p><i>This program is provided AS IS, with NO WARRANTY OF ANY KIND<br>"
                       "INCLUDING THE WARRANTY OF DESIGN, MERCHANTABILITY"
                       "AND FITNESS FOR A PARTICULAR PURPOSE.</i></p>");
}
