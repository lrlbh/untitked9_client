#ifndef MY_WIDGET_H
#define MY_WIDGET_H

#include <QMainWindow>
#include <QWidget>

class my_widget : public QWidget
{
    Q_OBJECT
public:
    explicit my_widget(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // MY_WIDGET_H
