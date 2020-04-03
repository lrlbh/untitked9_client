#include "ui.h"
#include<QDebug>
#include<qscreen.h>
#include<QGuiApplication>
#include<QTcpSocket>
#include<QHostAddress>


ui *ui::get_ui()
{
    return myui;
}



void ui::init_ui_size()
{



}

ui::ui()
{
    this->register_widget =Q_NULLPTR;
    this->rsa = Q_NULLPTR;
    this->my_user_long_in =Q_NULLPTR;
    this->aes =Q_NULLPTR;

}
ui* ui::myui =new ui;



