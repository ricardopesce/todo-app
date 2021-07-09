#include "editar.h"
#include "ui_editar.h"

Editar::Editar(QWidget *parent, int id, QString todo) : QDialog(parent), ui(new Ui::Editar){
    ui->setupUi(this);
    ui->label_id->setText( QString::number(id) );
    ui->field_txt->setText( todo );
}

Editar::~Editar()
{
    delete ui;
}

void Editar::on_btn_edit_clicked(){

    QString str_todo = ui->field_txt->text();
    QString id = ui->label_id->text();

    if(str_todo == ""){
        QMessageBox::warning(this, "AVISO", "Campo não pode estar vazio");
        return;
    }

    QSqlQuery query;
    QString sql = "UPDATE todos SET todos='" + str_todo + "' WHERE id=" + id;
    query.prepare( sql );

    if( query.exec() ){
        close();
    } else{
        qDebug() << "Falha ao atualizar registro";
    }
}

void Editar::on_btn_excluir_clicked(){

    //QMessageBox::warning(this, "ATENÇÃO!", "Você tem certeza que deseja excluir este registro permanentemente?");

    QString id = ui->label_id->text();
    QSqlQuery query;
    QString sql = "DELETE FROM todos WHERE id=" + id;
    query.prepare( sql );

    if( query.exec() ){
        close();
    } else{
        qDebug() << "Falha ao deletar registro";
    }
}
