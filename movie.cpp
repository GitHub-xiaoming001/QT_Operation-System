#include "movie.h"
#include "ui_movie.h"
#include <QMovie>

movie::movie(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::movie)
{
    ui->setupUi(this);

    //设置label播放 GIF
   QMovie *movie = new QMovie(":/tp2.gif",QByteArray(),this);
   ui->label_movie->setMovie(movie);
   movie->start();

}

movie::~movie()
{
    delete ui;
}
