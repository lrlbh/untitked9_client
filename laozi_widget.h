#ifndef LAOZI_WIDGET_H
#define LAOZI_WIDGET_H
#include<qqueue.h>
#include <QWidget>
class QMouseEvent;
class QString;
class laozi_widget : public QWidget
{
    Q_OBJECT
public:
    explicit laozi_widget(QWidget *parent = nullptr);

    void mouseReleaseEvent(QMouseEvent *ev);

    //保存获取到了一章道德经信息
    QQueue<QString> ddj_info;
signals:

public slots:

private:

};

#endif // LAOZI_WIDGET_H
