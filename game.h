#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QApplication>
#include <QDesktopWidget>
#include <QFile>
#include <QtGui>
#include "gamewidget.h"

namespace Ui {
class game;
}

class game : public QWidget
{
    Q_OBJECT

public:
    explicit game(QWidget *parent = 0);
    ~game();

private:
    Ui::game *ui;
    QPushButton *restartBtn;
       QPushButton *closeBtn;
       QLabel *titleLabel;
       QLabel *tipsLabel;
       QLabel *scoreLbl;
       QLabel *highScoreLbl;
       gamewidget *gameWidget;
       // 宽度和高度的缩放比例 用来使窗口部件随主窗口的尺寸改变而改变位置与尺寸
       qreal ratioW, ratioH;
       int highScore;
       QPoint dragPosition;
       bool bPressFlag;
protected:
    void resizeEvent(QResizeEvent *);
    void keyPressEvent(QKeyEvent * event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

public slots:
    void onScoreInc(int);
    void onGameOver();
};

#endif // GAME_H
