#ifndef UI_H
#define UI_H

#define MAIN_PB_NUM 4   //多少个导航菜单项
#define SHOW_GUA_WIDGET_NUM 3   //多少个页面显示一个卦的信息
#define Up_DOWN_SIZE  0.92  //下方导航菜单项和上方显示内容的分配比率
#include"laozi_widget.h"
#include"user_long_in.h"
#include"user_register_widget.h"
class QLineEdit;
class QStackedWidget;
class QPushButton;
class QTabWidget;
class QWidget;
class QLabel;
class QTcpSocket;
class my_widget;
class user_account_widget;
class my_tcp;
class my_rsa;
class my_aes;
//class user_register_widget;

class ui
{
public:
    //宽高分辨率
    int width=0;
    int height=0;
    //导航菜单项的高度
    int main_pb_height=0;

    //导航按钮
    QPushButton *main_pd[MAIN_PB_NUM];

    //导航按钮1的功能，栈容器
    QStackedWidget *stacked = nullptr;
    //分页显示控件
    QTabWidget *stacked_tab;
    //每个页面显示的信息
    QWidget *stacked_tab_widget[SHOW_GUA_WIDGET_NUM];
    //每个页面里面的文本显示
    QLabel *stacked_tab_widget_label[3][3];
    //每个页面里面的按钮
    QPushButton *stacked_tab_widget_pb ;

    //页面二，老子速记
    laozi_widget *laozi_widget;
    //页面二，内容显示
    QLabel * laozi_wideget_label;
    //页面二，按钮
    QPushButton * laozi_widget_pb;

    //页面三，账户信息
     user_account_widget *user_account;
     QLabel *temp_label;

    //页面四，我的
    my_widget *my_widget;
    //更新按钮
    QPushButton * my_widget_pb_up_app;

    //注册登陆按钮
    QPushButton * my_widget_pb_log_in;
    //登陆界面
    user_long_in* my_user_long_in ;
    //输入的账户文本框
    QLabel *my_widget_account_label;
    QLineEdit* my_widget_account ;
    //输入密码的文本框
    QLabel *my_widget_passwd_label;
    QLineEdit* my_widget_passwd ;
    //登陆的按钮
    QPushButton * my_widget_pb_user_log_in ;
    //注册的按钮
    QPushButton * my_widget_pb_user_sign_in ;
    //返回的按钮
    QPushButton * my_widget_pb_return ;
    //注册页面
    user_register_widget * register_widget;


    QPushButton * my_widget_pb_log_out;
    QPushButton * my_widget_pb_set;
    QPushButton * my_widget_pb_message;
    QLabel * my_widget_label_user_ifno;

    //保存临时使用的非对称加密资源
    my_rsa* rsa;
    bool pub_is_ok = false;

    //保存临时使用的对称加密秘钥
    my_aes* aes;

    //保存tcp对象
    my_tcp *cfd_tcp;


    QThread* thr;

    //获取ui对象
    static ui* get_ui();

private:
       ui();
       ui(const ui& u);
       //初始化 设置ui 大小参数
       void init_ui_size();

private:
       static ui* myui;

};

#endif // UI_H
