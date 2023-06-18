#ifndef SHIJIAN_H
#define SHIJIAN_H

#include <QWidget>

namespace Ui {
class shijian;
}

class shijian : public QWidget
{
    Q_OBJECT

public:
    explicit shijian(QWidget *parent = 0);
    ~shijian();

private:
    Ui::shijian *ui;
};

#endif // SHIJIAN_H
