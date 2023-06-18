#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include<mycoin.h>
#include "dataconfog.h"
#include "mycoin.h"


class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    //explicit PlayScene(QWidget *parent = nullptr);

    PlayScene(int levelNum);

    int levelIndex;         //记录成员属性

    void paintEvent(QPaintEvent *);

     //二维数组维护每关关卡的具体数据
    int gameArray[4][4];
    MyCoin * coinBtn[4][4];

    //是否胜利的标志
    bool isWin=false;
    //QMediaPlayer *endPlayer;

signals:
    void chooseSceneBack();
};

#endif // PLAYSCENE_H
