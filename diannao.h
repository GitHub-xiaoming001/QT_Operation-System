#ifndef DIANNAO_H
#define DIANNAO_H

#include <QWidget>

namespace Ui {
class diannao;
}

class diannao : public QWidget
{
    Q_OBJECT

public:
    explicit diannao(QWidget *parent = 0);
    ~diannao();

private:
    Ui::diannao *ui;
};

#endif // DIANNAO_H
