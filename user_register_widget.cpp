#include "user_register_widget.h"
#include "ui.h"
#include <qlabel.h>
#include<qpushbutton.h>
#include<QLineEdit>
#include<qtcpsocket.h>
#include<QHostAddress>
#include<qstring.h>
#include<string>
#include<qdebug.h>
#include"gua_info.pb.h"
#include<QMessageBox>
#include"my_rsa.h"
#include"my_tcp.h"
#include"my_aes.h"
#include<QThread>
#include"my_thread.h"
#include<QDialog>
//注册页面


//判断是否是手机号码
bool user_register_widget::is_phone()
{
    QString phone = this->phone_lb->text();
    if(phone.toUtf8().data()[0] == 0B00110001&&phone.toUtf8().length() ==11)
    {
        for (int i=0;i<phone.toUtf8().length();i++)
        {
            if(phone.toUtf8().data()[i] >= 0B00110000 && phone.toUtf8().data()[i]<= 0B00111001)
            {
                continue;
            }
            goto error_false;

        }
        return true;
    }
error_false:
    return false;
}

bool  user_register_widget::is_passwd(bool is_text_edited)
{

    QString passwd = this->passwd_le->text();
    int passwd_len = passwd.toUtf8().length();

    //判断是检测密码输入框还是，文本发生变化
    if(!(is_text_edited == true))
    {
        //只允许8-16个字符的密码
        if(!(passwd_len>=8 && passwd_len<=16))
            return false;
    }



    //循环判断每一个字符,是否符合规范
    for (int i=0;i<passwd_len+1;i++)
    {
        int x=0;
        if(i == passwd_len)
            return true;

        //是否是小写字母
        for (int j=0;j<26;j++)
            if(passwd.toUtf8().data()[i] == 97+j)
            {
                x++;
                break;
            }
        if(x>=1)
            continue;

        //是否是数字
        for (int j=0;j<10;j++)
            if(passwd.toUtf8().data()[i] == 48+j)
            {
                x++;
                break;
            }
        if(x>=1)
            continue;

        //是否是大写字母
        for (int j=0;j<26;j++)
            if(passwd.toUtf8().data()[i] == 65+j)
            {
                x++;
                break;
            }
        if(x>=1)
            continue;

        //是否是其他几个符号 ~ | { }
        for (int j=0;j<4;j++)
            if(passwd.toUtf8().data()[i] == 123+j)
            {
                x++;
                break;
            }
        if(x>=1)
            continue;



        //是否是下划线
        if(passwd.toUtf8().data()[i] == 0B01011111)
            continue;
        else    //有任意字符不符合所有规范
            return false;

    }
    return false;
}

user_register_widget::user_register_widget(QWidget *parent) : QWidget(parent)
{
    ui* my_ui = ui::get_ui();
    this->resize(my_ui->width,my_ui->height);

    //安卓中窗口关闭时应该这样释放资源，
    //不要使用信号自己手动释放，也不要在窗口关闭事件中释放资源，也不要只创建一个窗口对象都会出错
    this->setAttribute(Qt::WA_DeleteOnClose,true);

    //手机号提示
    QLabel* phone_label = new QLabel(this);
    phone_label->setText("手机号:");
    phone_label->setFont(QFont("Timers" , 20 ));
    phone_label->move(my_ui->width*0.10,my_ui->height*0.21);
    //手机号文本框
    phone_lb = new QLineEdit(this);
    phone_lb->resize(my_ui->width*0.6,my_ui->height*0.05);
    phone_lb->setFont(QFont("Timers" , 28 ,  QFont::Bold));
    phone_lb->move(my_ui->width*0.30,my_ui->height*0.2);
    phone_lb->setMaxLength(11);
    //验证码输入框
    QLineEdit* verification_ld =new QLineEdit(this);
    verification_ld->resize(my_ui->width*0.3,my_ui->height*0.05);
    verification_ld->setFont(QFont("Timers" , 28 ,  QFont::Bold));
    verification_ld->move(my_ui->width*0.30,my_ui->height*0.28);
    verification_ld->setMaxLength(4);

    //获取验证码按钮
    QPushButton* verification_pb   = new QPushButton(this);
    verification_pb->setText("获取验证码");
    verification_pb->resize(my_ui->width*0.25,my_ui->height*0.05);
    verification_pb->move(my_ui->width*0.65,my_ui->height*0.28);
    connect(verification_pb,&QPushButton::clicked,this,[=]()
    {
        if(this->is_phone())
        {

            //组织需要发送的数据，手机号码
            std::string write_buf =my_ui->aes->encrypy_aes(phone_lb->text().toStdString());
            write_buf.append("aa");
            write_buf[write_buf.size()-2]=0B00000101;
            write_buf[write_buf.size()-1]='\0';

            //发送数据
            my_ui->cfd_tcp->send_data((char*)write_buf.data(),write_buf.size());

        }
        else
        {
            QMessageBox::critical(this,"手机号码有误！","请输入正确的手机号！");
        }


    });

    //输入密码提示
    QLabel* passwd_lb = new QLabel(this);
    passwd_lb->setText("输入密码:");
    passwd_lb->setFont(QFont("Timers" , 20 ));
    passwd_lb->move(my_ui->width*0.062,my_ui->height*0.39);
    //输入密码文本框
    this->passwd_le = new QLineEdit(this);
    this->passwd_le->resize(my_ui->width*0.6,my_ui->height*0.05);
    this->passwd_le->setFont(QFont("Timers" , 10 ));
    this-> passwd_le->move(my_ui->width*0.30,my_ui->height*0.38);
    this->  passwd_le->setEchoMode(QLineEdit::Password);
    this->  passwd_le->setMaxLength(16);
    //再次输入密码提示
    QLabel* passwd_lb_again = new QLabel(this);
    passwd_lb_again->setText("再次输入:");
    passwd_lb_again->setFont(QFont("Timers" , 20 ));
    passwd_lb_again->move(my_ui->width*0.062,my_ui->height*0.49);

    //再次输入密码文本框
    this->passwd_le_again = new QLineEdit(this);
    this->passwd_le_again->resize(my_ui->width*0.6,my_ui->height*0.05);
    this-> passwd_le_again->setFont(QFont("Timers" , 10 ));
    this-> passwd_le_again->move(my_ui->width*0.30,my_ui->height*0.48);
    this-> passwd_le_again->setEchoMode(QLineEdit::Password);
    this-> passwd_le_again->setMaxLength(16);



    //注册的按钮
    QPushButton* register_pb   = new QPushButton(this);
    register_pb->setText("注册");
    register_pb->resize(my_ui->width*0.2,my_ui->height*0.08);
    register_pb->move(my_ui->width*0.35,my_ui->height*0.55);
    connect(register_pb,&QPushButton::clicked,this,[=]()
    {
        if(!this->is_phone())
        {
            QMessageBox::critical(this,"手机号码有误!","请重新输入!");
            return;
        }

        if (this->is_passwd(false))
        {
            if(this->passwd_le->text() == this->passwd_le_again->text())
            {
                //               //把手机号码和密码机密后放入protobuf中
                //                registered rd;
                //                rd.set_phone_number( my_ui->aes->encrypy_aes(this->phone_lb->text().toStdString()));
                //                rd.set_passwd(my_ui->aes->encrypy_aes(this->passwd_le->text().toStdString()));

                //                //序列化
                //                std::string write_buf;
                //                rd.SerializeToString(&write_buf);

                //                qDebug()<<write_buf.size();

                //                //填充两个字节协议
                //                write_buf+=0B00000110;
                //                write_buf+='\0';
                //                 qDebug()<<write_buf.size();

                //注册时候发生验证码过去校验
                Verification v;
                v.set_verification(verification_ld->text().toStdString());

                //序列化
                std::string write_buf;
                v.SerializeToString(&write_buf);

                //填充两个字节协议
                write_buf+=0B00000110;
                write_buf+='\0';

                //发送
                my_ui->cfd_tcp->send_data((char*)write_buf.data(),write_buf.size());

            }
            else
            {
                QMessageBox::critical(this,"请重新检查密码！","两次输入密码不一致!");
            }

        }else
        {
            QMessageBox::critical(this,"密码中有非法字符！",
                                  "密码规则:\n"
                                  "1、8-16位\n"
                                  "2、大小写字母\n"
                                  "3、数字\n"
                                  "4、以下符号\n"
                                  "_ { } ~ |");
            this->passwd_le->setText("");
            this->passwd_le_again->setText("");
        }
    });

    //返回的按钮
    QPushButton* my_return = new QPushButton(this);
    my_return->setText("返回");
    my_return->resize(my_ui->width*0.2,my_ui->height*0.08);
    my_return->move(my_ui->width*0.60,my_ui->height*0.55);
    connect(my_return,&QPushButton::clicked,this,[&](){
        this->close();
    });





    //绑定文本框变化的信号
    connect(this->passwd_le,&QLineEdit::textEdited,this,[=]()
    {
        //创建线程容器
        my_ui->thr =new QThread;
        //创建自己的线程对象
        this->passwd_thr= new my_thread;
        //绑定线程容器的 start 函数发出的信号到，自己的线程对象中的槽函数
        connect(my_ui->thr,&QThread::started,this->passwd_thr,&my_thread::test);
        //回收 QThread 对象的资源
        connect(my_ui->thr,&QThread::finished,my_ui->thr,&QThread::deleteLater);
        //回收 自己写的类 对象资源
        connect(my_ui->thr,&QThread::finished,this->passwd_thr,&my_thread::delete_this);
        //把自己创建的线程对象移动到线程容器中
        this->passwd_thr->moveToThread(my_ui->thr);

        //开启线程槽函数
        my_ui->thr->start();

        //槽函数代码执行完毕后，退出线程
        my_ui->thr->quit();
        my_ui->thr->exit();


        //打印线程id的方法
        //qDebug()<<"主线程id="<<QThread::currentThreadId();

        //自己的线程对象发出信号创建警告窗口
        connect(this->passwd_thr,&my_thread::passwd_error,this,[=]()
        {
            QMessageBox::critical(this,"密码中有非法字符！",
                                  "密码规则:\n"
                                  "1、8-16位\n"
                                  "2、大小写字母\n"
                                  "3、数字\n"
                                  "4、以下符号\n"
                                  " _ { } ~ |");
            this->passwd_le->setText("");
        });


    });








}

void user_register_widget::closeEvent(QCloseEvent *event)
{
    //窗口关闭把保存当前窗口的指针设置为NULL，下次创建时如果窗口指针不为BULL，不允许创建
    ui* my_ui = ui::get_ui();
    my_ui->register_widget =Q_NULLPTR;

}







