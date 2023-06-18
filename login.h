#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>

namespace Ui {
class login;
}

class login : public QWidget
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = 0);
    ~login();
signals:
    // 自定义信号函数
    log_success();

private slots:
    void on_pb1_clicked();

    void on_pb2_clicked();

private:
    Ui::login *ui;
};

#endif // LOGIN_H
