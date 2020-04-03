#ifndef USER_REGISTER_WIDGET_H
#define USER_REGISTER_WIDGET_H
#include<qwidget.h>
class my_thread;
class QLineEdit;
class user_register_widget : public QWidget
{
    Q_OBJECT
public:
    explicit user_register_widget(QWidget *parent = nullptr);

    //判断密码输入是否符合规范
    bool is_passwd(bool is_text_edited);

private:
    //判断手机号码输入是否正确
    bool is_phone();

    //密码输入和再次输入密码提示框
    QLineEdit* passwd_le;
    QLineEdit* passwd_le_again;
    //手机号码输入文本框
    QLineEdit* phone_lb;
    //判断服务器端是否收到秘钥，没收到不允许注册
    bool register_is_pub_key =false;
    //重写窗口关闭事件
    void closeEvent(QCloseEvent *event);

     my_thread* passwd_thr;

signals:

public slots:


};

#endif // USER_REGISTER_WIDGET_H
