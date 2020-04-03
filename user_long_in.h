#ifndef USER_LONG_IN_H
#define USER_LONG_IN_H

#include <QWidget>

class user_long_in : public QWidget
{
    Q_OBJECT
public:
    explicit user_long_in(QWidget *parent = nullptr);
    ~user_long_in();
//    void closeEvent(QCloseEvent *event);
//    int aa[1024*1024*50];

signals:
//    void close_widget();
public slots:
};

#endif // USER_LONG_IN_H
