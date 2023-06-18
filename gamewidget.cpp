#include "gamewidget.h"
#include "ui_gamewidget.h"
#include <QDebug>

// 颜色数组 存储每个数字对应的背景色
QColor digitBkg[11] = {QColor::fromRgb(0xEE, 0xE5, 0xDB), QColor::fromRgb(0xEC, 0xE0, 0xC8),
                       QColor::fromRgb(0xF2, 0xAF, 0x78), QColor::fromRgb(0xEE, 0x8A, 0x54),
                       QColor::fromRgb(0xFE, 0x76, 0x5E), QColor::fromRgb(0xE7, 0x58, 0xC),
                       QColor::fromRgb(0xFF, 0x66, 0x66), QColor::fromRgb(0xF1, 0xCF, 0x48),
                       QColor::fromRgb(0xCC, 0x33, 0x33), QColor::fromRgb(0xE3, 0xB9, 0x11),
                       QColor::fromRgb(0xFF, 0x00, 0x00)};

QPointF dPos[5] = {QPointF(-10, 0), QPointF(10, 0), QPointF(0, -10), QPointF(0, 10), QPointF(-2, -2)};


gamewidget::gamewidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gamewidget)
{
    ui->setupUi(this);
    connect(this, SIGNAL(GestureMove(GestureDirect)), SLOT(onGestureMove(GestureDirect)));
        memset(board, 0, sizeof(board));
        board[rand() % 4][rand() % 4] = 2;
        while(true) {
            int x = rand() % 4;
            int y = rand() % 4;
            if (board[x][y] != 0) {
                continue;
            }
            else {
                board[x][y] = 2;
                break;
            }
        }
        score = 0;
        digitCount = 2;
        isAnimating = false;
        cacheImg = NULL;
}

gamewidget::~gamewidget()
{
    delete ui;
}
void gamewidget::keyPressEvent(QKeyEvent *event)
{
    if (isAnimating)
        return;
    switch (event->key()) {
        case Qt::Key_Left:
            emit GestureMove(LEFT);
        break;
        case Qt::Key_Right:
            emit GestureMove(RIGHT);
        break;
        case Qt::Key_Down:
            emit GestureMove(DOWN);
        break;
        case Qt::Key_Up:
            emit GestureMove(UP);
        break;
        default:
        break;
    }
    QWidget::keyPressEvent(event);
}

void gamewidget::onGestureMove(GestureDirect direct)
{
    int i, j, k;
    Animation a;
    bool combine = false;
    switch (direct)
    {
    case LEFT:
        for (i = 0; i < 4; i++)
        {
            j = 0, k = 0, combine = false;
            while (true)
            {
                while (j < 4 && board[i][j] == 0)
                    j++;
                if (j > 3)
                    break;

                qSwap(board[i][k], board[i][j]);
                // 记录动画信息
                a.type = MOVE;
                a.startPos = QPointF(7 + (w + 5) * j, 7 + (h + 5) * i);
                a.endPos = QPointF(7 + (w + 5) * k, 7 + (h + 5) * i);
                a.digit = a.digit2 = board[i][k];
                a.direct = LEFT;
                if (!combine && k > 0 && board[i][k] == board[i][k - 1])
                {
                    board[i][k - 1] <<= 1;
                    board[i][k] = 0;
                    a.digit2 = board[i][k - 1];
                    a.endPos = QPointF(7 + (w + 5) * (k - 1), 7 + (h + 5) * i);
                    score += board[i][k - 1];
                    emit ScoreInc(score);
                    digitCount--;
                    combine = true;
                }
                else
                    k++;
                j++;
                // 添加到动画链表
                animationList.append(a);
            }
        }
        break;
    case RIGHT:
        for (i = 0; i < 4; i++)
        {
            j = 3, k = 3, combine = false;
            while (true)
            {
                while (j > -1 && board[i][j] == 0)
                    j--;
                if (j < 0)
                    break;
                qSwap(board[i][k], board[i][j]);
                a.type = MOVE;
                a.startPos = QPointF(7 + (w + 5) * j, 7 + (h + 5) * i);
                a.endPos = QPointF(7 + (w + 5) * k, 7 + (h + 5) * i);
                a.digit = a.digit2 = board[i][k];
                a.direct = RIGHT;
                if (!combine && k < 3 && board[i][k] == board[i][k + 1])
                {
                    board[i][k + 1] <<= 1;
                    board[i][k] = 0;
                    a.digit2 = board[i][k + 1];
                    a.endPos = QPointF(7 + (w + 5) * (k + 1), 7 + (h + 5) * i);
                    score += board[i][k + 1];
                    emit ScoreInc(score);
                    digitCount--;
                    combine = true;
                }
                else
                    k--;
                j--;
                animationList.append(a);
            }
        }
        break;
    case UP:
        for (i = 0; i < 4; i++)
        {
            j = 0, k = 0, combine = false;
            while (true)
            {
                while (j < 4 && board[j][i] == 0)
                    j++;
                if (j > 3)
                    break;
                qSwap(board[k][i], board[j][i]);
                a.type = MOVE;
                a.startPos = QPointF(7 + (w + 5) * i, 7 + (h + 5) * j);
                a.endPos = QPointF(7 + (w + 5) * i, 7 + (h + 5) * k);
                a.digit = a.digit2 = board[k][i];
                a.direct = UP;
                if (!combine && k > 0 && board[k][i] == board[k - 1][i])
                {
                    board[k - 1][i] <<= 1;
                    board[k][i] = 0;
                    a.digit2 = board[k - 1][i];
                    a.endPos = QPointF(7 + (w + 5) * i, 7 + (h + 5) * (k - 1));
                    score += board[k - 1][i];
                    emit ScoreInc(score);
                    digitCount--;
                    combine = true;
                }
                else
                    k++;
                j++;
                animationList.append(a);
            }
        }
        break;
    case DOWN:
        for (i = 0; i < 4; i++)
        {
            j = 3, k = 3, combine = false;
            while (true)
            {
                while (j > -1 && board[j][i] == 0)
                    j--;
                if (j < 0)
                    break;
                qSwap(board[k][i], board[j][i]);
                a.type = MOVE;
                a.startPos = QPointF(7 + (w + 5) * i, 7 + (h + 5) * j);
                a.endPos = QPointF(7 + (w + 5) * i, 7 + (h + 5) * k);
                a.digit = a.digit2 = board[k][i];
                a.direct = DOWN;
                if (!combine && k < 3 && board[k][i] == board[k + 1][i])
                {
                    board[k + 1][i] <<= 1;
                    board[k][i] = 0;
                    a.digit2 = board[k + 1][i];
                    a.endPos = QPointF(7 + (w + 5) * i, 7 + (h + 5) * (k + 1));
                    score += board[k + 1][i];
                    emit ScoreInc(score);
                    digitCount--;
                    combine = true;
                }
                else
                    k--;
                j--;
                animationList.append(a);
            }
        }
        break;
    }
    bool flag_move = false;
    for(int index = 0; index < animationList.size(); index++) {
        if (animationList.at(index).startPos != animationList.at(index).endPos) {
            flag_move = true;
            break;
        }
    }
    if (digitCount != 16 && flag_move)
    {
        i = rand() % 4, j = rand() % 4;
        while (board[i][j] != 0)
            i = rand() % 4, j = rand() % 4;
        board[i][j] = 2;
        a.type = APPEARANCE;
        a.startPos = a.endPos = QPointF(7 + (w + 5) * j, 7 + (h + 5) * i);
        a.startPos += QPointF(w / 2, h / 2);
        a.digit = board[i][j];
        digitCount++;
    }
    else
    {
        if (checkGameOver())
            emit GameOver();
    }

    // 开始绘制动画效果
    isAnimating = true;
    // 动画列表的迭代器
    QList<Animation>::iterator it;
    // 事件循环 用于延时
    QEventLoop eventLoop;
    if (cacheImg)
        delete cacheImg;
    cacheImg = new QImage(width(), height(), QImage::Format_ARGB32);
    cacheImg->fill(0);
    QPainter painter(cacheImg);
    QFont font;
    font.setFamily("Consolas");
    font.setBold(true);
    font.setPixelSize(40);
    painter.setFont(font);
    // 标识所有方格动画是否都播放完毕
    bool ok = false;
    while (true)
    {
        QBrush brush(QColor::fromRgb(114, 126, 174));
        painter.setBrush(brush);

        // 设置画笔为空笔 目的是使绘制的图形没有描边
        painter.setPen(Qt::NoPen);

        painter.drawRect(2, 2, width() - 4, height() - 4);

        brush.setColor(QColor::fromRgb(141,166,234));
        painter.setBrush(brush);

        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                painter.drawRect(QRectF(7 + (w + 5) * j, 7 + (h + 5) * i, w, h));

        ok = true;

        for (it = animationList.begin(); it != animationList.end(); it++)
            if (!playAnimation(*it, painter))
                ok = false;

        update();

        if (ok)
            break;

        // 延时5ms
        QTimer::singleShot(5, &eventLoop, SLOT(quit()));
        eventLoop.exec();
    }
    // 播放方格出现的动画
    while (!playAnimation(a, painter))
    {
        update();
        QTimer::singleShot(5, &eventLoop, SLOT(quit()));
        eventLoop.exec();
    }
    //清除所有动画
    animationList.clear();
    //刷新当前部件
    isAnimating = false;
    update();
}

bool gamewidget::playAnimation(Animation& a, QPainter& painter)
{
    bool rtn = false;
    QBrush brush(Qt::SolidPattern);

    // 移动方格位置
    if (a.type == MOVE)
    {
        switch (a.direct)
        {
        case LEFT:
            if (a.startPos.x() > a.endPos.x())
                a.startPos += dPos[LEFT];
            else
                a.startPos = a.endPos, rtn = true;
            break;
        case RIGHT:
            if (a.startPos.x() < a.endPos.x())
                a.startPos += dPos[RIGHT];
            else
                a.startPos = a.endPos, rtn = true;
            break;
        case UP:
            if (a.startPos.y() > a.endPos.y())
                a.startPos += dPos[UP];
            else
                a.startPos = a.endPos, rtn = true;
            break;
        case DOWN:
            if (a.startPos.y() < a.endPos.y())
                a.startPos += dPos[DOWN];
            else
                a.startPos = a.endPos, rtn = true;
        }
        // 如果方格移动到终点
        if (!rtn)
        {
            brush.setColor(digitBkg[getBitCount(a.digit)]);
            painter.setBrush(brush);
            painter.drawRect(QRectF(a.startPos.x(), a.startPos.y(), w, h));
            painter.setPen(QColor::fromRgb(0, 0, 0));
            painter.drawText(QRectF(a.startPos.x(), a.startPos.y(), w, h), Qt::AlignCenter,
                             QString::number(a.digit));
        }
        else
        {
            brush.setColor(digitBkg[getBitCount(a.digit2)]);
            painter.setBrush(brush);
            painter.drawRect(QRectF(a.startPos.x(), a.startPos.y(), w, h));
            painter.setPen(QColor::fromRgb(0, 0, 0));
            painter.drawText(QRectF(a.startPos.x(), a.startPos.y(), w, h), Qt::AlignCenter,
                             QString::number(a.digit2));
        }
        painter.setPen(Qt::NoPen);
    }
    else
    {
        // 方格出现的动画效果
        if (a.startPos.x() > a.endPos.x())
            a.startPos += dPos[4];
        else
            a.startPos = a.endPos, rtn = true;
        brush.setColor(digitBkg[getBitCount(a.digit)]);
        painter.setBrush(brush);
        painter.drawRect(QRectF(a.startPos.x(), a.startPos.y(),
                         w - 2 * (a.startPos.x() - a.endPos.x()),
                         h - 2 * (a.startPos.y() - a.endPos.y())));
        painter.setPen(QColor::fromRgb(0, 0, 0));
        painter.drawText(QRectF(a.endPos.x(), a.endPos.y(), w, h),
                         Qt::AlignCenter, QString::number(a.digit));
        painter.setPen(Qt::NoPen);
    }
    return rtn;
}

void gamewidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    // 如果正在播放动画效果则绘制缓存位图
    if (isAnimating)
    {
        painter.drawImage(0, 0, *cacheImg);
        return;
    }

    QBrush brush(QColor::fromRgb(114, 126, 174));
    painter.setBrush(brush);

    // 设置画笔为空笔 目的是使绘制的图形没有描边
    painter.setPen(Qt::NoPen);

    painter.drawRect(2, 2, width() - 4, height() - 4);

    w = width() - 4, h = height() - 4;
    w = (w - 25) / 4, h = (h - 25) / 4;

    QFont font;
    font.setFamily("Consolas");
    font.setBold(true);
    font.setPixelSize(40);
    painter.setFont(font);

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
        {
            if (board[i][j])
            {
                brush.setColor(digitBkg[getBitCount(board[i][j])]);
                painter.setBrush(brush);
                painter.drawRect(QRectF(7 + (w + 5) * j, 7 + (h + 5) * i, w, h));
                painter.setPen(QColor::fromRgb(0, 0, 0));
                painter.drawText(QRectF(7 + (w + 5) * j, 7 + (h + 5) * i, w, h), Qt::AlignCenter,
                                 QString::number(board[i][j]));
                painter.setPen(Qt::NoPen);
            }
            else
            {
                brush.setColor(QColor::fromRgb(141,166,234));
                painter.setBrush(brush);
                painter.drawRect(QRectF(7 + (w + 5) * j, 7 + (h + 5) * i, w, h));
            }
        }
}

void gamewidget::restart()
{
    // 初始化相关变量 同构造函数
    score = 0;
    digitCount = 2;
    memset(board, 0, sizeof(board));
    board[rand() % 4][rand() % 4] = 2;
    while(true) {
        int x = rand() % 4;
        int y = rand() % 4;
        if (board[x][y] != 0) {
            continue;
        }
        else {
            board[x][y] = 2;
            break;
        }
    }
    emit ScoreInc(score);
    update();
}

bool gamewidget::checkGameOver()
{
    // 循环检测是否含有相邻的相同数码
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
        {
            if (j != 3 && board[i][j] == board[i][j + 1])
                return false;
            if (i != 3 && board[i][j] == board[i + 1][j])
                return false;
        }
    return true;
}

int gamewidget::getBitCount(int n)
{
    int c = 0;
    while (n >>= 1)
        c++;
    return c - 1;
}

