#include "protocol_laozi.h"
#include"ui.h"
#include<qlabel.h>
#include"qstring.h"
#include<qdebug.h>
#include"gua_info.pb.h"
#include<qqueue.h>
#include<string>
#include<string.h>
#include<QStringList>
#include<qregexp.h>
#include<stdlib.h>
#include<stdio.h>

protocol_laozi::protocol_laozi(std::string & buf)
{

    ui* my_ui =ui::get_ui();
    //反序列化，获取数据
    dao_de_jing laozi;
    laozi.ParseFromString(buf);

    my_ui->laozi_widget->ddj_info.clear();

    //这一坨循环用于分割字符串，同时保留分割符号
    //目前支持这些符号 ,.:;!?，。：；！、？  可酌情增减
    //支持utf-8编码数据
    char temp[128]={0};
    char temp_data[555]={0};
    strcpy(temp_data,laozi.message().data());
    for (int i=0,j=0;i<strlen(temp_data);i++)
    {
        if(temp_data[i] == 0B00101100
                ||temp_data[i] == 0B00101110
                ||temp_data[i] == 0B00111010
                ||temp_data[i] == 0B00111011
                ||temp_data[i] == 0B00100001
                ||temp_data[i] == 0B00111111
                ||(unsigned char)temp_data[i] == 0B11101111
                ||(unsigned char)temp_data[i] == 0B11100011
                ||(unsigned char)temp_data[i] == 0B11101111
                ||(unsigned char)temp_data[i] == 0B11101111
                ||(unsigned char)temp_data[i] == 0B11101111
                ||(unsigned char)temp_data[i] == 0B11100011
                ||(unsigned char)temp_data[i] == 0B11101111)

        {
            if (temp_data[i] == 0B00101100
                    ||temp_data[i] == 0B00101110
                    ||temp_data[i] == 0B00111010
                    ||temp_data[i] == 0B00111011
                    ||temp_data[i] == 0B00100001
                    ||temp_data[i] == 0B00111111)
            {

                temp[j++]=temp_data[i];
                my_ui->laozi_widget->ddj_info.push_back(temp);
                memset(temp,0,128);
                j=0;
                continue;
            }

            if((unsigned char)temp_data[i] ==   0B10111100
                    ||(unsigned char)temp_data[i+1] == 0B10000000
                    ||(unsigned char)temp_data[i+1] == 0B10111100
                    ||(unsigned char)temp_data[i+1] == 0B10111100
                    ||(unsigned char)temp_data[i+1] == 0B10111100
                    ||(unsigned char)temp_data[i+1] == 0B10000000
                    ||(unsigned char)temp_data[i+1] == 0B10111100)

            {
                if((unsigned char)temp_data[i+2] == 0B10001100
                        ||(unsigned char)temp_data[i+2] == 0B10000010
                        ||(unsigned char)temp_data[i+2] == 0B10000010
                        ||(unsigned char)temp_data[i+2] == 0B10011011
                        ||(unsigned char)temp_data[i+2] == 0B10000001
                        ||(unsigned char)temp_data[i+2] == 0B10000001
                        ||(unsigned char)temp_data[i+2] == 0B10011111)
                {
                    memcpy(temp+j,temp_data+i,3);
                     my_ui->laozi_widget->ddj_info.push_back(temp);
                    i+=2;
                    memset(temp,0,128);
                    j=0;

                }
                else    //第三个的判断
                {
                    temp[j++]=temp_data[i];
                    temp[j++]=temp_data[i+1];
                    if(temp_data[i+2] ==(unsigned char)0B00000000)
                    {
                        break;
                    }


                }


            }
            else    //第二个判断
            {
                temp[j++]=temp_data[i];
                if(temp_data[i+1] ==(unsigned char)0B00000000)
                {
                    break;
                }

            }


        }
        else    //第一个判断
        {

                temp[j++]=temp_data[i];

        }
    }

    //测试分割情况
//    while (my_ui->laozi_widget->ddj_info.empty() ==false) {
//        qDebug()<<my_ui->laozi_widget->ddj_info.front();
//        my_ui->laozi_widget->ddj_info.pop_front();
//    }

    if (my_ui->laozi_widget->ddj_info.empty() ==false)
    {
        my_ui->laozi_wideget_label->setText(my_ui->laozi_widget->ddj_info.front());
        my_ui->laozi_widget->ddj_info.pop_front();
    }

//     my_ui->laozi_wideget_label->setText(temp_data);




}
