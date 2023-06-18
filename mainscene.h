#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QWidget>
#include<chooselevelscene.h>

#include <QMainWindow>

namespace Ui {
class mainscene;
}

QT_BEGIN_NAMESPACE
namespace Ui { class MainScene; }
QT_END_NAMESPACE

class mainscene : public QWidget
{
    Q_OBJECT

public:
    explicit mainscene(QWidget *parent = 0);
    ~mainscene();

    //重写背景图，paintEvent事件
        void paintEvent(QPaintEvent *);
        ChooseLevelScene * chooseScene = NULL;

private:
    Ui::mainscene *ui;
};

#endif // MAINSCENE_H
