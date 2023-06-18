#include "shijian.h"
#include "ui_shijian.h"

shijian::shijian(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::shijian)
{
    ui->setupUi(this);
}

shijian::~shijian()
{
    delete ui;
}
