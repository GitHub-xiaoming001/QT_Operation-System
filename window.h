#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include "login.h"
#include "diannao.h"
#include "ui_diannao.h"
#include "shijian.h"
#include "ui_shijian.h"
#include "movie.h"
#include "ui_movie.h"
#include "txqq.h"
#include "ui_txqq.h"
#include "weixin.h"
#include "ui_weixin.h"
#include"game.h"
#include "ui_game.h"
#include "gamewidget.h"
#include "ui_gamewidget.h"


namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_pb_diannao_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pb_movie_clicked();

    void on_toolButton_3_triggered(QAction *arg1);

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

private:
    Ui::Widget *ui;
    login *log;
};

#endif // WINDOW_H
