#include "txqq.h"
#include "ui_txqq.h"

txqq::txqq(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::txqq)
{
    ui->setupUi(this);
}

txqq::~txqq()
{
    delete ui;
}
