#ifndef MOVIE_H
#define MOVIE_H

#include <QWidget>

namespace Ui {
class movie;
}

class movie : public QWidget
{
    Q_OBJECT

public:
    explicit movie(QWidget *parent = 0);
    ~movie();

private:
    Ui::movie *ui;
};

#endif // MOVIE_H
