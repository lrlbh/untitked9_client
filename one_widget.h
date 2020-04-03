#ifndef ONE_WIDGET_H
#define ONE_WIDGET_H

#include <QWidget>

class one_widget : public QWidget
{
    Q_OBJECT
public:
    //n是传入参数索引，声明这个创建的第几个页面
    explicit one_widget(int n,QWidget *parent = nullptr);

    //重写鼠标按下
     void mousePressEvent(QMouseEvent *ev);

     //重写鼠标释放
     void mouseReleaseEvent(QMouseEvent *ev);

private:
     //
     int x;
     int y;


signals:

public slots:
};

#endif // ONE_WIDGET_H
