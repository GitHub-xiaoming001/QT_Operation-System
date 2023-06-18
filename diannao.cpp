#include "diannao.h"
#include "ui_diannao.h"

diannao::diannao(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::diannao)
{
    ui->setupUi(this);
}

diannao::~diannao()
{
    delete ui;
}
