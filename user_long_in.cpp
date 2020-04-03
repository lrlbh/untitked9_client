#include "user_long_in.h"
#include<qdebug.h>
#include"ui.h"
#include<QLineEdit>
#include<qlabel.h>
#include<qfont.h>
#include<QPushButton>
#include"user_register_widget.h"
#include"my_rsa.h"
#include"my_tcp.h"
#include"gua_info.pb.h"
#include<QMessageBox>



user_long_in::user_long_in(QWidget *parent) : QWidget(parent)
{
    ui* my_ui = ui::get_ui();
    this->resize(my_ui->width,my_ui->height);


    //安卓中窗口关闭时应该这样释放资源，
    //不要使用信号自己手动释放，也不要在窗口关闭事件中释放资源，也不要只创建一个窗口对象都会出错
    this->setAttribute(Qt::WA_DeleteOnClose,true);

    //登陆提示
    my_ui->my_widget_account_label = new QLabel(this);
    my_ui->my_widget_account_label->setText("手机号:");
    my_ui->my_widget_account_label->setFont(QFont("Timers" , 20 ));
    my_ui->my_widget_account_label->move(my_ui->width*0.05,my_ui->height*0.21);
    //登陆文本框
    my_ui->my_widget_account = new QLineEdit(this);
    my_ui->my_widget_account->resize(my_ui->width*0.6,my_ui->height*0.05);
    my_ui->my_widget_account->setFont(QFont("Timers" , 28 ,  QFont::Bold));
    my_ui->my_widget_account->move(my_ui->width*0.25,my_ui->height*0.2);

    //登陆密码提示
    my_ui->my_widget_account_label = new QLabel(this);
    my_ui->my_widget_account_label->setText("密码:");
    my_ui->my_widget_account_label->setFont(QFont("Timers" , 20 ));
    my_ui->my_widget_account_label->move(my_ui->width*0.10,my_ui->height*0.29);
    //登陆密码文本框
    my_ui->my_widget_account = new QLineEdit(this);
    my_ui->my_widget_account->resize(my_ui->width*0.6,my_ui->height*0.05);
    my_ui->my_widget_account->setFont(QFont("Timers" , 28 ,  QFont::Bold));
    my_ui->my_widget_account->move(my_ui->width*0.25,my_ui->height*0.28);
    my_ui->my_widget_account->setEchoMode(QLineEdit::Password);

    //登陆的按钮
    my_ui->my_widget_pb_user_log_in = new QPushButton(this);
    my_ui->my_widget_pb_user_log_in->setText("登陆");
    my_ui->my_widget_pb_user_log_in->resize(my_ui->width*0.2,my_ui->height*0.08);
    my_ui->my_widget_pb_user_log_in->move(my_ui->width*0.28,my_ui->height*0.35);
    connect(my_ui->my_widget_pb_user_log_in,&QPushButton::clicked,this,[&](){

    });


    //注册的按钮
    my_ui->my_widget_pb_user_sign_in = new QPushButton(this);
    my_ui->my_widget_pb_user_sign_in->setText("注册");
    my_ui->my_widget_pb_user_sign_in->resize(my_ui->width*0.2,my_ui->height*0.08);
    my_ui->my_widget_pb_user_sign_in->move(my_ui->width*0.53,my_ui->height*0.35);

    //这里需要使用值传递，使用引用传递会出错
    connect(my_ui->my_widget_pb_user_sign_in,&QPushButton::clicked,this,[=]()
    {
        //只允许拥有一个注册窗口
        if(my_ui->register_widget == Q_NULLPTR )
        {

            //创建注册页面
            //该对象在窗口已经被设置为窗口关闭后自动释放资源
            my_ui->register_widget = new user_register_widget;
            my_ui->register_widget->show();


        }
        else
        {
            QMessageBox::critical(this,"注册窗口已打开","只能打开一个注册窗口！");
        }





    });

    //返回的按钮
    my_ui->my_widget_pb_return = new QPushButton(this);
    my_ui->my_widget_pb_return->setText("返回");
    my_ui->my_widget_pb_return->resize(my_ui->width*0.4,my_ui->height*0.16);
    my_ui->my_widget_pb_return->move(my_ui->width*0.3,my_ui->height*0.55);
    connect(my_ui->my_widget_pb_return,&QPushButton::clicked,this,[&](){
        this->close();
    });
}

user_long_in::~user_long_in()
{
    ui * my_ui = ui::get_ui();

    if(my_ui->rsa != Q_NULLPTR)
    {
        delete my_ui->rsa;
        my_ui->rsa =Q_NULLPTR;
        my_ui->pub_is_ok =false;
    }

    if(my_ui->aes != Q_NULLPTR)
    {
        delete my_ui->aes;
        my_ui->aes =Q_NULLPTR;
        my_ui->pub_is_ok =false;
    }

    my_ui->my_user_long_in =Q_NULLPTR;
}

//窗口关闭事件，释放窗口对象
//void user_long_in::closeEvent(QCloseEvent *event)
//{
//    emit this->close_widget();
//    qDebug()<<"对象是否被释放";
//    qDebug()<<"对象是否被释放";

////    delete this;
//}
