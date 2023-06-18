#include "weixin.h"
#include "ui_weixin.h"

weixin::weixin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::weixin)
{
    ui->setupUi(this);
}

weixin::~weixin()
{
    delete ui;
}
