#include "window.h"
#include "ui_window.h"


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    log = new login;
    log->show();
    connect(log,SIGNAL(log_success()),this,SLOT(show()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pb_diannao_clicked()
{
    diannao *configWindow = new diannao;
        configWindow->show();
}

void Widget::on_pushButton_2_clicked()
{
    shijian *configWindow = new shijian;
        configWindow->show();
}

void Widget::on_pushButton_clicked()
{
    this->close();
}

void Widget::on_pb_movie_clicked()
{
    movie *configWindow = new movie;
        configWindow->show();
}



void Widget::on_pushButton_3_clicked()
{
    txqq *configWindow = new txqq;
    configWindow->show();
}

void Widget::on_pushButton_4_clicked()
{
    diannao *configWindow = new diannao;
        configWindow->show();
}

void Widget::on_pushButton_5_clicked()
{
    weixin *configWindow = new weixin;
        configWindow->show();
}

void Widget::on_pushButton_6_clicked()
{
   game *configWindow = new game;
        configWindow->show();
}


