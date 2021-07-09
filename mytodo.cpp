#include "mytodo.h"
#include "ui_mytodo.h"

MyTodo::MyTodo(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MyTodo){
    ui->setupUi(this);

    start();

    db.setDatabaseName(user);

    !db.open() ? qDebug() << "Falha ao abrir " + user :  qDebug() << "Banco de dados " + user + " aberto com sucesso!";

    show_data();
}

MyTodo::~MyTodo(){
    delete ui;
}

void MyTodo::start(){
    QFile quser( user );

    if( !quser.exists() ){
        QFile::copy(dir, user);
        /*QString str_cmd = "chmod 600 " + user;
        system(str_cmd.c_str());*/
        system("chmod 600 ~/.config/mytodo.db");
        qDebug() << "Arquivo mytodo.db copiado para ~/.config/";

    }
}

void MyTodo::show_data(){
    sql = "SELECT * FROM todos";
    query.prepare( sql );

    if(query.exec() ){
        clear_table();
        int column_count = 3;

        ui->tb_show->setColumnCount(column_count); // inserindo colunas

        for(int i = 0; query.next(); i++){
            ui->tb_show->insertRow(i); // insere linha (registro)
            for(int j=0; j < column_count; j++ ){
                ui->tb_show->setItem(i, j, new QTableWidgetItem( query.value(j).toString() ));
            }
        }
        // tb_show Header
        QStringList headers = {"Id", "Tarefa", "Data/Hora"};
        ui->tb_show->setHorizontalHeaderLabels( headers );

        //tb_show Layout
        ui->tb_show->setColumnWidth(0, 60);
        ui->tb_show->setColumnWidth(1, 600);
        ui->tb_show->setColumnWidth(2, 150);
        ui->tb_show->verticalHeader()->setVisible( false );

    } else{
        qDebug() << "Falha ao consultar os dados";
    }
}

void MyTodo::clear_table(){
    for( int i=0; i < ui->tb_show->rowCount(); i++ ){
        ui->tb_show->removeRow( i );
    }
    ui->tb_show->clear(); // limpa tabela
}


void MyTodo::on_btn_add_clicked()
{
    str_todo = ui->field_todo->text();
    if( str_todo == "" ){
        QMessageBox::warning(this, "Aviso", "Preencha o campo da tarefa.");
        return;
    }
    if( ! db.isOpen() ){
        QMessageBox::critical(this, "ERRO!", "<h3>Falha ao conectar ao banco de dados</h3>"
                                             "<p>Contate o desenvolvedor, ou verifique a existência de " + user + "</p>"
                                             "<p>Dica: Na inexistência do Banco de Dados, você pode reinicar o programa.</p>");
        return;
    }

    sql = "INSERT INTO todos ( todos ) VALUES ( '" + str_todo + "' )";
    query.prepare( sql );

    if( query.exec() ){
        ui->statusbar->showMessage("Dados inseridos com sucesso!");
        QTimer::singleShot( 3000, [&](){ ui->statusbar->showMessage(""); } );
        ui->field_todo->clear();
        ui->field_todo->setFocus();
        show_data();
    } else{
        qDebug() << "ERR: Falha ao inserir dados no banco.";
    }
}

void MyTodo::on_tb_show_cellClicked(int row, int column){
    column = 0;
    int id = ui->tb_show->item(row, column)->text().toInt();
    str_todo = ui->tb_show->item(row, 1)->text();
    Editar e(this, id, str_todo);
    e.exec();
    show_data();
}


void MyTodo::on_actionSair_triggered(){
    close();
}

void MyTodo::on_actionSobre_MyTodo_triggered(){
    QMessageBox::about(this, "Sobre esse programa",
                       "<h2>My ToDo 1.0.1</h2>"
                       "<p>Projeto Desenvolvido no Curso de Qt Moderno com C++<br>"
                       "prof. Marcos Oliveira<br>"
                       "Adaptado por Ricardo Pesce</p>"
                       "<p><i>This program is provided AS IS, with NO WARRANTY OF ANY KIND<br>"
                       "INCLUDING THE WARRANTY OF DESIGN, MERCHANTABILITY"
                       "AND FITNESS FOR A PARTICULAR PURPOSE.</i></p>");
}
