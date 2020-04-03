#include "laozi_widget.h"
#include<qlabel.h>
#include<qpushbutton.h>
#include"ui.h"
#include"qdebug.h"
#include<QMouseEvent>
laozi_widget::laozi_widget(QWidget *parent) : QWidget(parent)
{
    ui * my_ui=ui::get_ui();
    QString qs("玄之又玄，众妙之门");
    my_ui->laozi_wideget_label = new QLabel(this);
    my_ui->laozi_wideget_label->move(my_ui->width*0.02, my_ui->height*0.02);
    my_ui->laozi_wideget_label->resize(my_ui->width*0.96,my_ui->height*0.7);
    my_ui->laozi_wideget_label->setFrameShape(QFrame::Box);
    my_ui->laozi_wideget_label->setText(qs);
    my_ui->laozi_wideget_label->setWordWrap(true);
    my_ui->laozi_wideget_label->setAlignment(Qt::AlignCenter);
    my_ui->laozi_wideget_label->setFont(QFont ( "Microsoft YaHei", 20, 75));


    my_ui->laozi_widget_pb = new QPushButton(this);
    my_ui->laozi_widget_pb->resize(my_ui->width*0.4,my_ui->height*0.1);
    my_ui->laozi_widget_pb->setText("体会");
    my_ui->laozi_widget_pb->move(my_ui->width*0.3,my_ui->height*0.77);


}

//重写鼠标释放
void laozi_widget::mouseReleaseEvent(QMouseEvent *ev)
{
    ui * my_ui=ui::get_ui();
    if(my_ui->laozi_widget->ddj_info.empty()==false)
    {
        my_ui->laozi_wideget_label->setText(my_ui->laozi_wideget_label->text()+ my_ui->laozi_widget->ddj_info.front());
        my_ui->laozi_widget->ddj_info.pop_front();

    }



}
