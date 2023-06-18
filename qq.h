#ifndef QQ_H
#define QQ_H

#include <QWidget>

namespace Ui {
class QQ;
}

class QQ : public QWidget
{
    Q_OBJECT

public:
    explicit QQ(QWidget *parent = 0);
    ~QQ();

private:
    Ui::QQ *ui;
};

#endif // QQ_H
