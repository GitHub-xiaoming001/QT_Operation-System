#include "mainscene.h"
#include "ui_mainscene.h"
#include<QPainter>
#include<mypushbutton.h>
#include<QDebug>
#include<chooselevelscene.h>
#include<QTimer>
#include<QSound>
#include<QAction>

mainscene::mainscene(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainscene)
{
    ui->setupUi(this);
    //主场景 主窗口
       setFixedSize(320,500);
       setWindowTitle("翻金币  By--ssssssss");
       setWindowIcon(QIcon(":/image/coin.gif"));

       connect(ui->actionQuit, &QAction::triggered,[=](){
           this->close();
       });

       //准备开始按钮的音效
       QSound* startSound=new QSound(":/image/BackButtonSound.wav",this);
       //startSound->setLoops(-1);   //设置循环背景音乐
       startSound->play();

       //开始按钮
       MyPushButton * startbtn = new MyPushButton(":/image/startbtn.png");
       startbtn->setParent(this);


       startbtn->move(this->width() * 0.5 - startbtn->width() *0.5, this->height() * 0.5);
       // 实例化选择关卡场景
       chooseScene = new ChooseLevelScene;     //实例化窗口

       /*监听选择关卡的返回按钮的信号*/
       connect(chooseScene, &ChooseLevelScene::chooseSceneBack, [=](){
           this->setGeometry(chooseScene->geometry());
           chooseScene->hide();
           this->show();
       });

       connect(startbtn, &QPushButton::clicked,[=](){
           qDebug() << "点击了开始";

           //播放开始音效
           startSound->play();
           //弹起特效
           startbtn->zoom1();
           startbtn->zoom2();

           //进入+延时
           QTimer::singleShot(500,this,[=](){
               //设置chooseScene场景位置
               chooseScene->setGeometry(this->geometry());
               //自身隐藏
               this->hide();
               chooseScene->show();
            });

       });
   }

   void mainscene::paintEvent(QPaintEvent *)  //背景图
   {
       QPainter painter(this);         //画背景
       QPixmap pix;
       pix.load(":/image/bj.png");
       painter.drawPixmap(0,0,this->width(),this->height(),pix);

       pix.load(":/image/title.png");      //画背景图标
       pix = pix.scaled(pix.width() * 0.25, pix.height() * 0.25);
       painter.drawPixmap(10,40,pix);

   }

mainscene::~mainscene()
{
    delete ui;
}
