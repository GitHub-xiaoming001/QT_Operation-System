#include "login.h"
#include "ui_login.h"

login::login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}

void login::on_pb1_clicked()
{
  emit log_success();
    this->close();
}

void login::on_pb2_clicked()
{
      this->close();
}
