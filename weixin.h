#ifndef WEIXIN_H
#define WEIXIN_H

#include <QWidget>

namespace Ui {
class weixin;
}

class weixin : public QWidget
{
    Q_OBJECT

public:
    explicit weixin(QWidget *parent = 0);
    ~weixin();

private:
    Ui::weixin *ui;
};

#endif // WEIXIN_H
