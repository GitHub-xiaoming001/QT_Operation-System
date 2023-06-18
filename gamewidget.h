#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QEventLoop>
#include <QTimer>
#include <QPainter>
#include <QList>

namespace Ui {
class gamewidget;
}
enum GestureDirect
{
    LEFT = 0,
    RIGHT = 1,
    UP = 2,
    DOWN = 3
};

// 定义动画的类型
enum AnimationType
{
    MOVE = 0,       // 方格移动动画
    APPEARANCE = 1  // 方格出现动画
};

// 动画结构体
struct Animation
{
    AnimationType type;     // 动画类型
    GestureDirect direct;   // 方向
    QPointF startPos;       // 起始点坐标 出现动画仅仅使用这个坐标
    QPointF endPos;         // 终止点坐标 移动动画的终点坐标
    int digit;              // 数码
    int digit2;             // 第二数码 数码可能被合并
};

class gamewidget : public QWidget
{
    Q_OBJECT

public:
    explicit gamewidget(QWidget *parent = 0);
    ~gamewidget();

protected:
    void keyPressEvent(QKeyEvent * event);

private:
    Ui::gamewidget *ui;
    int board[4][4];
       int digitCount;
       int score;
       QPoint startPos;
       QList<Animation> animationList;
       qreal w, h;
       QImage *cacheImg;
       bool isAnimating;
       bool checkGameOver();
       int getBitCount(int);
       bool playAnimation(Animation&, QPainter&);
       void paintEvent(QPaintEvent *);

   signals:
       void GestureMove(GestureDirect);
       void ScoreInc(int);
       void GameOver();
   public slots:
       void onGestureMove(GestureDirect);
       void restart();
};

#endif // GAMEWIDGET_H
