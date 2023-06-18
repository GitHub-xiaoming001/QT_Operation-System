#include "playscene.h"
#include<QDebug>
#include<QMenuBar>
#include<QPainter>
#include<mypushbutton.h>
#include<QTimer>
#include<QLabel>
#include<mycoin.h>
#include<dataconfig.h>
#include<QPropertyAnimation>
#include <QSound>

PlayScene::PlayScene(int levelNum)
{
    QString str = QString("进入了第 %1 关").arg(levelNum);
    qDebug() << str;
    this->levelIndex = levelNum;

    this->setFixedSize(320,500);
    this->setWindowIcon(QPixmap(":/image/coin.gif"));
    this->setWindowTitle("翻金币");

    //菜单
    QMenuBar * bar = menuBar();
    setMenuBar(bar);
    QMenu * startMenu = bar->addMenu("开始");
    QAction * quitAction = startMenu->addAction("退出");
    connect(quitAction, &QAction::triggered,[=](){
        this->close();
    });

    //添加音效
    QSound * backSound=new QSound(":/image/BackButtonSound.wav",this);
    QSound *filpSound=new QSound(":/image/ConFlipSound.wav",this);
    QSound *winSound=new QSound(":/image/LevelWinSound.wav",this);


    //返回按钮
    MyPushButton * backbtn = new MyPushButton(":/image/back.png", ":/image/back2.png");
    backbtn->setParent(this);
    backbtn->move(this->width() - backbtn->width(), this->height() - backbtn->height());

    connect(backbtn, &QPushButton::clicked, [=](){
        //返回音效
        backSound->play();

        qDebug() << "点击了返回";
        QTimer::singleShot(500, this, [=](){
            emit this->chooseSceneBack();
        });
    });

    //显示关卡
    QLabel * label = new QLabel;
    label->setParent(this);
    QFont font;
    font.setFamily("宋体");
    font.setPointSize(20);
    QString str1 = QString("Level:%1").arg(this->levelIndex);
    //字体设置到标签控件中
    label->setFont(font);
    label->setText(str1);
    label->setGeometry(30, this->height() - 50 ,120, 50);

    dataConfig config;
    //初始化每个关卡的二维数组
    for(int i = 0 ; i < 4; i++){
        for(int j = 0; j < 4; j++){
            this ->gameArray[i][j] = config.mData[this->levelIndex][i][j];
        }
    }

    //胜利图片的显示
    QLabel *winLabel=new QLabel;
    QPixmap tmpPix;
    tmpPix.load(":/image/succeed.png");
    winLabel->setParent(this);
    winLabel->setGeometry(0,0,tmpPix.width(),tmpPix.height());
    winLabel->setPixmap(tmpPix);
    winLabel->move((this->width()-tmpPix.width())*0.5,  -tmpPix.height());


    //显示金币背景图案
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            QPixmap pix = QPixmap(":/image/qzbg.png");
            QLabel * label = new QLabel;
            pix = pix.scaled(pix.width() * 0.5, pix.height() * 0.5);
            label->setGeometry(0,0,pix.width(),pix.height());
            label->setPixmap(pix);
            label->setParent(this);
            label->move(16  + i * 75 , 140 + j * 75);

            //创建金币
            QString str;
            if (this->gameArray[i][j] == 1){
                //显示金币
                str = ":/image/jb1.png";
            }
            else{
                str = ":/image/jb8.png";
            }
            MyCoin * coin = new MyCoin(str);
            coin->setParent(this);
            coin->move(16  + i * 75 , 141 + j * 75);

            //给金币赋值
            coin->posX = i;
            coin->posY = j;
            coin->flag = this->gameArray[i][j];     //  1正面 2反面

            //将金币放入到金币的二维数组里面 以便于后期的维护
            coinBtn[i][j]=coin;

            //点击金币进行翻转
            connect(coin,&MyCoin::clicked,[=](){
                //金币音效
                filpSound->play();

//                for(int i = 0; i < 4; i ++){
//                    for(int j = 0; j< 4; j++){
//                        this->coinBtn[i][j]->isWin = true;
//                    }
//                }

                coin->changeFlag();

                this->gameArray[i][j]=this->gameArray[i][j]==0?1:0;

                QTimer::singleShot(300,this,[=](){
                    // 翻转周围硬币的操作，延时翻转
                    if(coin->posX+1<=3){// 周围的右侧硬币翻转的条件
                        coinBtn[coin->posX+1][coin->posY]->changeFlag();
                        this->gameArray[coin->posX+1][coin->posY]=this->gameArray[coin->posX+1][coin->posY]==0?1:0;

                    }
                    if(coin->posX-1>=0) // 周围左侧硬币的翻转条件
                    {
                        coinBtn[coin->posX-1][coin->posY]->changeFlag();
                        this->gameArray[coin->posX-1][coin->posY]=this->gameArray[coin->posX-1][coin->posY]==0?1:0;
                    }
                    if(coin->posY+1<=3) // 周围下侧硬币的翻转条件
                    {
                        coinBtn[coin->posX][coin->posY+1]->changeFlag();
                        this->gameArray[coin->posX][coin->posY+1]=this->gameArray[coin->posX][coin->posY+1]==0?1:0;
                    }
                    if(coin->posY-1>=0) // 周围上侧硬币的翻转条件
                    {
                        coinBtn[coin->posX][coin->posY-1]->changeFlag();
                        this->gameArray[coin->posX][coin->posY-1]=this->gameArray[coin->posX][coin->posY-1]==0?1:0;
                    }

                    //判断是否胜利
                    this->isWin=true;
                    for(int i=0;i<4;i++)
                    {
                        for(int j=0;j<4;j++){
                            if(coinBtn[i][j]->flag==false){
                                this->isWin=false;
                                break;
                            }
                        }
                    }

                    if(this->isWin==true){

                        //胜利了
                        qDebug()<<"游戏胜利";
                        winSound->play();

                        //将所有按钮胜利的标志改为 true,如果再次点击按钮直接return
                        for(int i=0;i<4;i++)
                        {
                            for(int j=0;j<4;j++){
                                coinBtn[i][j]->isWin=true;
                            }
                        }

                        //将胜利的图片移动下来
                        QPropertyAnimation *animation=new QPropertyAnimation(winLabel,"geometry");
                        //设置时间间隔
                        animation->setDuration(1000);

                        //设置开始位置
                        animation->setStartValue(QRect(QPoint(winLabel->x(),winLabel->y()),QPoint(winLabel->x()+winLabel->width(),winLabel->height())));
                        //设置结束位置
                        animation->setEndValue(QRect(QPoint(winLabel->x(),winLabel->y()+30),QPoint(winLabel->x()+winLabel->width(),winLabel->height()+120)));

                        //设置缓和曲线
                        animation->setEasingCurve(QEasingCurve::OutBounce);
                        //执行动画
                        animation->start();



                    }



                });

            });

        }
    }





}


void PlayScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);         //画背景
    QPixmap pix;
    pix.load(":/image/bj.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //标题
    pix.load(":/image/title.png");      //画背景图标
    pix = pix.scaled(pix.width() * 0.25, pix.height() * 0.25);
    painter.drawPixmap(10,40,pix);
}
