#ifndef MY_THREAD_H
#define MY_THREAD_H
#include<qobject.h>

//这是保存多线程类的文件




//该类用于判断密码是否合法，
class my_thread : public QObject
{
    Q_OBJECT
public:
    explicit my_thread(QObject *parent = nullptr);

    ~my_thread();
signals:
    //如果密码不合法发送这个信号
    void passwd_error();
public slots:
    //判断密码是否合法的槽函数
    void test();
    //释放当前对象的槽函数
    void delete_this();
private:
    //没使用
    bool is_stop;

};

#endif // MY_THREAD_H
