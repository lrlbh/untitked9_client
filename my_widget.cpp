#include "my_widget.h"
#include <qpushbutton.h>
#include"ui.h"
#include<qfont.h>
#include "qlabel.h"
#include"user_long_in.h"
#include<qwidget.h>
#include<qdebug.h>
my_widget::my_widget(QWidget *parent) : QWidget(parent)
{
    ui* my_ui =ui::get_ui();

    my_ui->my_widget_label_user_ifno = new QLabel(this);
    my_ui->my_widget_label_user_ifno->resize(my_ui->width*0.94,my_ui->height*0.2);
    my_ui->my_widget_label_user_ifno->move(my_ui->width*0.03,my_ui->height*0.015);
    my_ui->my_widget_label_user_ifno->setFrameShape(QFrame::Box);
    my_ui->my_widget_label_user_ifno->setText("暂时预留用户信息显示");
    my_ui->my_widget_label_user_ifno->setWordWrap(true);
    my_ui->my_widget_label_user_ifno->setAlignment(Qt::AlignCenter);
    my_ui->my_widget_label_user_ifno->setFont(QFont ( "Microsoft YaHei", 15, 75));

    my_ui->my_widget_pb_log_in= new QPushButton(this);
    my_ui->my_widget_pb_log_in->resize(my_ui->width*0.94,my_ui->height*0.1);
    my_ui->my_widget_pb_log_in->move(my_ui->width*0.03,my_ui->height*0.220);
    my_ui->my_widget_pb_log_in->setText("登陆/注册");
    my_ui->my_widget_pb_log_in->setFont(QFont( "Microsoft YaHei", 24, 75));


    my_ui->my_widget_pb_log_out= new QPushButton(this);
    my_ui->my_widget_pb_log_out->resize(my_ui->width*0.94,my_ui->height*0.1);
    my_ui->my_widget_pb_log_out->move(my_ui->width*0.03,my_ui->height*0.335);
    my_ui->my_widget_pb_log_out->setText("退出登陆");
    my_ui->my_widget_pb_log_out->setFont(QFont( "Microsoft YaHei", 24, 75));

    my_ui->my_widget_pb_up_app= new QPushButton(this);
    my_ui->my_widget_pb_up_app->resize(my_ui->width*0.94,my_ui->height*0.1);
    my_ui->my_widget_pb_up_app->move(my_ui->width*0.03,my_ui->height*0.450);
    my_ui->my_widget_pb_up_app->setText("检测更新");
    my_ui->my_widget_pb_up_app->setFont(QFont( "Microsoft YaHei", 24, 75));

    my_ui->my_widget_pb_set= new QPushButton(this);
    my_ui->my_widget_pb_set->resize(my_ui->width*0.94,my_ui->height*0.1);
    my_ui->my_widget_pb_set->move(my_ui->width*0.03,my_ui->height*0.565);
    my_ui->my_widget_pb_set->setText("设置");
    my_ui->my_widget_pb_set->setFont(QFont( "Microsoft YaHei", 24, 75));

    my_ui->my_widget_pb_message= new QPushButton(this);
    my_ui->my_widget_pb_message->resize(my_ui->width*0.94,my_ui->height*0.1);
    my_ui->my_widget_pb_message->move(my_ui->width*0.03,my_ui->height*0.675);
    my_ui->my_widget_pb_message->setText("产品介绍");
    my_ui->my_widget_pb_message->setFont(QFont( "Microsoft YaHei", 24, 75));
}
