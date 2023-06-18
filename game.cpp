#include "game.h"
#include "ui_game.h"

game::game(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::game)
{
    ui->setupUi(this);
    setAutoFillBackground(true);
        QPalette pal = palette();
        pal.setColor(QPalette::Background, QColor("#808ad2"));
        setPalette(pal);


        titleLabel = new QLabel(tr("2048"), this);
        titleLabel->setStyleSheet("color:#746D65;");
        titleLabel->setFont(QFont("arial", 30, QFont::Black));

        tipsLabel = new QLabel(tr("Join the numbers and get to the 2048 tile!"), this);
        tipsLabel->setStyleSheet("color:#B3AFA7;");
        tipsLabel->setFont(QFont("arial", 8, QFont::Normal));
        highScore = 0;
        QFile file("score.j");
        if (file.open(QIODevice::ReadOnly))
        {
            file.read((char *)&highScore, sizeof(highScore));
            file.close();
        }

        gameWidget = new gamewidget(this);
        gameWidget->setFocus();
        connect(gameWidget, SIGNAL(ScoreInc(int)), this, SLOT(onScoreInc(int)));
        connect(gameWidget, SIGNAL(GameOver()), this, SLOT(onGameOver()));
        connect(gameWidget, SIGNAL(win()), this, SLOT(onWin()));

        QFont font;
        font.setFamily("Arial");
        font.setBold(true);
        font.setPixelSize(15);

        restartBtn = new QPushButton("New Game", this);
        restartBtn->setFont(font);
        restartBtn->setStyleSheet("QPushButton{color:#55285f;background:#a7b7e8;border-style:flat;}");
        restartBtn->setFocusPolicy(Qt::NoFocus);
        connect(restartBtn, SIGNAL(clicked()), gameWidget, SLOT(restart()));

        highScoreLbl = new QLabel(QString("BEST\n%1").arg(highScore),this);
        highScoreLbl->setFont(font);
        highScoreLbl->setAlignment(Qt::AlignCenter);
        highScoreLbl->setStyleSheet("QLabel{color:#ee3b34;background:#ccc3b4}");

        scoreLbl = new QLabel("SCORE\n0", this);
        scoreLbl->setFont(font);
        scoreLbl->setAlignment(Qt::AlignCenter);
        scoreLbl->setStyleSheet("QLabel{color:#fcb43c;background:#7e7764}");

        closeBtn = new QPushButton("x", this);
        closeBtn->setFocusPolicy(Qt::NoFocus);
        closeBtn->setFont(QFont("Arial", 11, QFont::Normal));

        closeBtn->setStyleSheet("QPushButton{border-style:flat;color:#BDAD9F}"
                            "QPushButton:hover{border-style:flat;color:#FF0000}");
        closeBtn->setCursor(Qt::PointingHandCursor);
        closeBtn->setGeometry(400 - 18, 3, 15, 15);
        connect(closeBtn, SIGNAL(clicked()), this, SLOT(close()));

        // 重置窗口大小
        resize(400, 510);
        move((QApplication::desktop()->width() - width())/2,  (QApplication::desktop()->height() - height())/2);

}

game::~game()
{
    delete ui;
    delete restartBtn;
        delete scoreLbl;
        delete highScoreLbl;
        delete gameWidget;
}
void game::onScoreInc(int score)
{
    scoreLbl->setText(QString("Score:\n %1").arg(score));
    if (score > highScore)
    {
        highScore = score;
        highScoreLbl->setText(QString("BEST:\n %1").arg(highScore));

        // 将新的最高分存入文件
        QFile file("score.j");
        file.open(QIODevice::WriteOnly);
        file.write((char *)&highScore, sizeof(highScore));
        file.close();
    }
}

void game::onGameOver()
{
    QMessageBox::information(this, "GameOver", "You lost !");
}

void game::resizeEvent(QResizeEvent *)
{
    // 计算宽度和高度的缩放比例
    ratioW = width() / 400.0f;
    ratioH = height() / 510.0f;
    // 重置子部件大小和位置
    titleLabel->setGeometry(20 * ratioW, 40 * ratioH , 150 * ratioW, 50 * ratioH);
    tipsLabel->setGeometry(20 * ratioW, 100 * ratioH , 300 * ratioW, 20 * ratioH);
    gameWidget->setGeometry(18 * ratioW, 140 * ratioH, 365 * ratioW, 365 * ratioH);
    restartBtn->setGeometry(280 * ratioW, 90 * ratioH, 100 * ratioW, 30 * ratioH);
    highScoreLbl->setGeometry(300 * ratioW, 40 * ratioH, 80 * ratioW, 40 * ratioH);
    scoreLbl->setGeometry(210 * ratioW, 40 * ratioH, 80 * ratioW, 40 * ratioH);

}

void game::keyPressEvent(QKeyEvent *event)
{
    gameWidget->setFocus();
    QWidget::keyPressEvent(event);
}
void game::mousePressEvent ( QMouseEvent * event)
{
    bPressFlag = true;
    dragPosition = event->pos();
    QWidget::mousePressEvent(event);
}

void game::mouseMoveEvent(QMouseEvent *event)
{
    if (bPressFlag) {
        QPoint relaPos(QCursor::pos() - dragPosition);
        move(relaPos);
    }
    QWidget::mouseMoveEvent(event);
}

void game::mouseReleaseEvent(QMouseEvent *event)
{
    bPressFlag = false;
    QWidget::mouseReleaseEvent(event);
}
