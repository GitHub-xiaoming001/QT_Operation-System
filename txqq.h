#ifndef TXQQ_H
#define TXQQ_H

#include <QWidget>

namespace Ui {
class txqq;
}

class txqq : public QWidget
{
    Q_OBJECT

public:
    explicit txqq(QWidget *parent = 0);
    ~txqq();

private:
    Ui::txqq *ui;
};

#endif // TXQQ_H
