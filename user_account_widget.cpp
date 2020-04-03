#include "user_account_widget.h"
#include "ui.h"
#include<qlabel.h>
user_account_widget::user_account_widget(QWidget *parent) : QWidget(parent)
{
    ui * my_ui=ui::get_ui();
    QString qs("账户太多，记不过来，写个程序管理");
    my_ui->temp_label = new QLabel(this);
    my_ui->temp_label->move(my_ui->width*0.02, my_ui->height*0.02);
    my_ui->temp_label->resize(my_ui->width*0.96,my_ui->height*0.8);
    my_ui->temp_label->setFrameShape(QFrame::Box);
    my_ui->temp_label->setText(qs);
    my_ui->temp_label->setWordWrap(true);
    my_ui->temp_label->setAlignment(Qt::AlignCenter);
    my_ui->temp_label->setFont(QFont ( "Microsoft YaHei", 20, 75));



}
