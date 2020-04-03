 #include "widget.h"
#include "ui.h"
#include"one_widget.h"
#include<QStackedWidget>
#include <widget.h>
#include<qpushbutton.h>
#include<qstring.h>
#include<qdebug.h>
#include<QGuiApplication>
#include<QRect>
#include<QScreen>
#include<qtabwidget.h>
#include"laozi_widget.h"
#include<QHostAddress>
#include<qtcpsocket.h>
#include<QThread>
#include"gua_info.pb.h"
#include<qlabel.h>
#include"protocol_zhouyi.h"
#include<string>
#include<queue>
#include"protocol_laozi.h"
#include"my_widget.h"
#include"user_account_widget.h"
#include"user_long_in.h"
#include<QDialog>
#include<openssl/aes.h>
#include"my_tcp.h"
#include"my_rsa.h"
#include"QMessageBox"




static ui* my_ui;

//初始化界面宽高属性
void init_width_height()
{
    //获取当前屏幕分辨率
    QScreen *screen=QGuiApplication::primaryScreen ();
    QRect mm=screen->availableGeometry() ;

#ifdef ANDROID
    my_ui->width = mm.width();
    my_ui->height = mm.height();
    my_ui->main_pb_height = my_ui->height * (1-Up_DOWN_SIZE);
    return;
#endif

    my_ui->width = mm.height()/2;
    my_ui->height =  mm.width()/2 - (int)(mm.width()/2*0.2);
    my_ui->main_pb_height = my_ui->height * (1-Up_DOWN_SIZE);
}

//初始化导航菜单项
void init_main_pd(Widget* my_this)
{
    QString pb_name[MAIN_PB_NUM]={"周易速记","老子体会","账户管理","我的"};

    //创建导航菜单项
    for(int i=0;i<MAIN_PB_NUM;i++)
    {
        //创建按钮
        my_ui->main_pd[i] = new QPushButton(my_this);
        //设置文本
        my_ui->main_pd[i]->setText(pb_name[i]);
        //设置大小
        my_ui->main_pd[i]->resize(my_ui->width/MAIN_PB_NUM,my_ui->main_pb_height);
        //设置位置
        my_ui->main_pd[i]->move(i*(my_ui->width/MAIN_PB_NUM),my_ui->height- my_ui->main_pb_height);
    }

}

//初始化一个页面
void init_stacked_one()
{
    //创建多个页面容器
    my_ui->stacked_tab = new QTabWidget(my_ui->stacked);

    //添加页面按钮 起卦
    my_ui->stacked_tab_widget_pb = new QPushButton("速记",my_ui->stacked_tab);
    //按钮大小
    my_ui->stacked_tab_widget_pb->resize(my_ui->width*0.4,my_ui->width*0.2);
    //按钮位置
#ifndef ANDROID
    my_ui->stacked_tab_widget_pb->move(my_ui->width*0.3,my_ui->height*0.3*2+my_ui->height*0.05*3);
#endif
#ifdef ANDROID
    my_ui->stacked_tab_widget_pb->move(my_ui->width*0.3,my_ui->height*0.3*2+my_ui->height*0.05*3.5);
#endif

    //添加多个页面
    QString web_name[SHOW_GUA_WIDGET_NUM]= {"本卦","变卦","解卦"};
    for(int i=0;i<SHOW_GUA_WIDGET_NUM;i++)
    {
        my_ui->stacked_tab_widget[i] = new one_widget(i,my_ui->stacked_tab);
        my_ui->stacked_tab->addTab(my_ui->stacked_tab_widget[i],web_name[i]);
    }

    my_ui->stacked->addWidget(my_ui->stacked_tab);
}

//创建栈容器添加多个界面
void init_stacked(Widget* my_this)
{
    //创建栈容器
    my_ui->stacked = new QStackedWidget(my_this);
    my_ui->stacked->move(0,0);
    my_ui->stacked->resize(my_ui->width,my_ui->height - my_ui->main_pb_height);

    //添加栈容器第一个页面
    init_stacked_one();

    //添加栈容器第二个页面
    my_ui->laozi_widget = new laozi_widget(my_this);
    my_ui->stacked->addWidget(my_ui->laozi_widget);


    //添加栈容器第三个页面
    my_ui->user_account = new user_account_widget(my_this);
    my_ui->stacked->addWidget(my_ui->user_account);

    //添加栈容器第四个页面
    my_ui->my_widget = new my_widget(my_this);
    my_ui->stacked->addWidget(my_ui->my_widget);


}

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    //粘包处理使用
    static std::string data;

    my_ui =ui::get_ui();


    // 初始化 APP 界面
    init_width_height();
    this->resize(my_ui->width,my_ui->height);

    //初始化导航菜单项
    init_main_pd(this);

    //初始化栈容器
    init_stacked(this);

    //导航按钮绑定栈容器
    for (int i= 0;i<MAIN_PB_NUM;i++)
    {
        connect(my_ui->main_pd[i],&QPushButton::clicked,this,[=](){
            my_ui->stacked->setCurrentIndex(i);

        });
    }

    //创建tcp通信套接字
    my_ui->cfd_tcp =new my_tcp;

    //请求一挂
    connect(my_ui->stacked_tab_widget_pb,&QPushButton::clicked,this,[&]()
    {
        //发送请求
        char write_buf[2]={0};
        write_buf[0] = 0B00000001;
        write_buf[1] = 0B00000000;
        my_ui->cfd_tcp->send_data(write_buf,2);

        //QThread::sleep(4);
    });

    //请求一章道德经
    connect(my_ui->laozi_widget_pb,&QPushButton::clicked,this,[&]()
    {
        //发送请求
        char write_buf[2]={0};
        write_buf[0] = 0B00000011;
        write_buf[1] = 0B00000000;
        my_ui->cfd_tcp->send_data(write_buf,2);
    });




    //登陆注册按钮
    connect(my_ui->my_widget_pb_log_in,&QPushButton::clicked,this,[=](){

        if(my_ui->my_user_long_in == Q_NULLPTR)
        {
            //在构造中已经设置窗口关闭，自动释放对象，此方法兼容andorid
            my_ui->my_user_long_in = new user_long_in;
            my_ui->my_user_long_in->show();

            //创建rsa加密对象
            my_ui->rsa = new my_rsa();
            //生成一对秘钥
            my_ui->rsa->generate_key_pair();
            //获取公钥的base64字符流编码，和长度
            std::string key;
            int key_len=0;
            my_ui->rsa->get_pub_key_str_base64(key,key_len);


            //protoc组织需要发送的数据
            send_pub_key spk;
            spk.set_pub_key(key);
            spk.set_pub_key_len(key_len);
            std::string write_data;
            spk.SerializeToString(&write_data);
            write_data.append("aa");
            write_data+= 0B00000100;
            write_data+= '\0';

            //发送数据
            my_ui->cfd_tcp->send_data((char*)write_data.data(),write_data.size());

        }
        else
        {
            QMessageBox::critical(this,"登陆窗口已打开！","登陆窗口已打开！");
        }


    });



}


//读取通信协议分发给不同的类处理
//收到一次数据，调用一次，需要确保数据读完，类似epoll里面的ET模式
//connect(my_ui->cfd,&QTcpSocket::readyRead,this,[&]()
//{

//    char read_buf[1400]={0};
//    qint64 ret_read_buf=0;
//    //while确保数据被读完
//    while((ret_read_buf= my_ui->cfd->read(read_buf,qint64(sizeof(read_buf))))!=0)
//    {
//        //检查接收到到的数据
//        for(int i=0;i<ret_read_buf;i++)
//        {

//            //读取到一条完整的协议就处理
//            if(read_buf[i] == '\0')
//            {

//                memset(read_buf,0,sizeof(read_buf));
//                //对应协议调用对应类
//                if(data[data.size()-1] == 0B00000001)
//                {
//                    data[data.size()-1]='\0';

//                    protocol_zhouyi pz(data);
//                    data ="";
//                }
//                //对应协议调用对应类
//                else if(data[data.size()-1] == 0B00000010)
//                {
//                    data[data.size()-1]='\0';
//                    protocol_laozi laozi(data);
//                    data ="";
//                }
//                //对应协议调用对应类
//                else
//                {
//                    data ="";
//                }

//            }
//            //正常数据拷贝到string中
//            else
//            {
//                data += read_buf[i];
//            }

//            //每次循环结束，初始化一下read_buf
//            if((i+1)==ret_read_buf)
//            {
//                memset(read_buf,0,sizeof(read_buf));
//            }

//        }

//    }
//});

#ifdef asd

//使用qt连接mysql数据，windows下的程序32位和64位编译了对应的库后，可以使用。
//但是找不到androdi的库，使用linux的库也不行，可能没有
//可能需要编译，mysql源码，然后在编驱动
void sql_error(Widget* my_this)
{
    //打印数据库驱动
    //qDebug()<<QSqlDatabase::drivers();

    //连接数据库
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("192.168.10.131");
    db.setPort(3306);
    db.setUserName("root");
    db.setPassword("go123");
    db.setDatabaseName("sjs");
    if(db.open()==false)
    {
        QMessageBox::warning(my_this,"warning",db.lastError().text());
        qDebug()<<"测试"<<db.lastError().text();
    }

    QSqlQuery sql;
    QString sql_str = "select * from gua_64";
    sql.exec(sql_str);

    while (sql.next())
    {

        qDebug()<<sql.value(0).toInt()
               <<sql.value(1).toString()
              <<sql.value(2).toString();
    }


}
#endif


Widget::~Widget()
{

}
