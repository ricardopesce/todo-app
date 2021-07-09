#include "editar.h"
#include "ui_editar.h"

Editar::Editar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Editar)
{
    ui->setupUi(this);
}

Editar::~Editar()
{
    delete ui;
}
