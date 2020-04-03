#include "one_widget.h"
#include "ui.h"
#include<qlabel.h>
#include<qdebug.h>
#include<QMouseEvent>
#include<qstackedwidget.h>
#include<QTabWidget>
one_widget::one_widget(int n,QWidget *parent) : QWidget(parent)
{
    ui* my_ui =ui::get_ui();

    //创建控件
    my_ui->stacked_tab_widget_label[n][0]= new QLabel(this);
    //控件位置
    my_ui->stacked_tab_widget_label[n][0]->move(my_ui->width*0.05,my_ui->height*0.05);
    //控件大小
    my_ui->stacked_tab_widget_label[n][0]->resize(my_ui->width*0.4,my_ui->height*0.2);
    //边框
    my_ui->stacked_tab_widget_label[n][0]->setFrameShape(QFrame::Box);
    //文本内容
    my_ui->stacked_tab_widget_label[n][0]->setText("卦名");
    //自动换行
    my_ui->stacked_tab_widget_label[n][0]->setWordWrap(true);
    //居中显示
    my_ui->stacked_tab_widget_label[n][0]->setAlignment(Qt::AlignCenter);
    //字体，大小，加粗
    my_ui->stacked_tab_widget_label[n][0]->setFont(QFont ( "Microsoft YaHei", 15, 75));



    my_ui->stacked_tab_widget_label[n][1] = new QLabel(this);
    my_ui->stacked_tab_widget_label[n][1]->move(my_ui->width*0.55, my_ui->height*0.05);
    my_ui->stacked_tab_widget_label[n][1]->resize(my_ui->width*0.4,my_ui->height*0.2);
    my_ui->stacked_tab_widget_label[n][1]->setFrameShape(QFrame::Box);
    my_ui->stacked_tab_widget_label[n][1]->setText("---------\n---------\n---------\n---------\n---------\n---------\n");
    my_ui->stacked_tab_widget_label[n][1]->setWordWrap(true);
    my_ui->stacked_tab_widget_label[n][1]->setAlignment(Qt::AlignCenter);
    my_ui->stacked_tab_widget_label[n][1]->setFont(QFont ( "Microsoft YaHei", 15, 75));


    my_ui->stacked_tab_widget_label[n][2] = new QLabel(this);
    my_ui->stacked_tab_widget_label[n][2]->move((my_ui->width*0.05), (my_ui->height*0.05)*2+(my_ui->height*0.2));
    my_ui->stacked_tab_widget_label[n][2]->resize(my_ui->width - (0+my_ui->width*0.05)*2,my_ui->height*0.4);
    my_ui->stacked_tab_widget_label[n][2]->setFrameShape(QFrame::Box);
    my_ui->stacked_tab_widget_label[n][2]->setText("大衍之数五十，其用四十有九。分而为二以象两，挂一以象三，揲之以 四以象四时，归奇于扐以象闰，五岁再闰，故再扐而后挂。");
    my_ui->stacked_tab_widget_label[n][2]->setFont(QFont ( "Microsoft YaHei", 14, 75));
    my_ui->stacked_tab_widget_label[n][2]->setWordWrap(true);


}



void one_widget::mousePressEvent(QMouseEvent *ev)
{
    this->x= ev->globalX();
    this->y = ev->globalY();

}

void one_widget::mouseReleaseEvent(QMouseEvent *ev)
{
    ui* my_ui = ui::get_ui();
    if( this->x -ev->globalX() >= my_ui->width*0.2 )
    {
        if(this->y -ev->globalY() <= my_ui->height*0.2)
        {

            if( my_ui->stacked_tab->currentIndex()  >= SHOW_GUA_WIDGET_NUM-1)
            {
                my_ui->stacked_tab->setCurrentIndex(0);
            }
            else
            {
                my_ui->stacked_tab->setCurrentIndex(my_ui->stacked_tab->currentIndex()+1);
            }


        }

    }


    if(ev->globalX() - this->x  >= my_ui->width*0.2 )
    {
        if(ev->globalY()-this->y  <= my_ui->height*0.2)
        {

            if( my_ui->stacked_tab->currentIndex()  == 0)
            {
                my_ui->stacked_tab->setCurrentIndex(SHOW_GUA_WIDGET_NUM-1);
            }
            else
            {
                my_ui->stacked_tab->setCurrentIndex(my_ui->stacked_tab->currentIndex()-1);
            }


        }

    }


}
