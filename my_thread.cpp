#include "my_thread.h"
#include <qdebug.h>
#include<qthread.h>
#include<QMessageBox>
#include<qwidget.h>
#include"ui.h"


my_thread::my_thread(QObject *parent) : QObject(parent)
{
    is_stop =true;
}

void my_thread::test()
{

    ui* my_ui = ui::get_ui();

    if(!my_ui->register_widget->is_passwd(true))
    {
        emit passwd_error();
    }

}


void  my_thread::delete_this()
{
    delete this;
}

my_thread:: ~my_thread()
{

}
