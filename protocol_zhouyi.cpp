#include "protocol_zhouyi.h"
#include"ui.h"
#include<qstring.h>
#include"gua_info.pb.h"
#include<qlabel.h>
protocol_zhouyi::protocol_zhouyi(std::string & buf)
{
    ui* my_ui=ui::get_ui();
    //解析数据
    gua my_gua;
    my_gua.ParseFromString(buf);

    //加载到页面一
    my_ui->stacked_tab_widget_label[0][0]->setText(QString(my_gua.ben_gua_name().data())
                                                   +QString("\n")
                                                   +QString(my_gua.ben_gua_info().data()));
    QString drawing_gua;
    QString yao_info;
    for(int i=5;i>=0;i--)
    {
        if( my_gua.ben_gua_yao_info(i).is_yang() == true)
        {
            drawing_gua+="------------\n";
        }else
        {
            drawing_gua+="----     ----\n";
        }

        yao_info += QString(my_gua.ben_gua_yao_info(i).info().data())+"\n";
    }
    my_ui->stacked_tab_widget_label[0][1]->setText(drawing_gua);
    my_ui->stacked_tab_widget_label[0][2]->setText(yao_info);


    //加载页面二
    my_ui->stacked_tab_widget_label[1][0]->setText(QString(my_gua.bian_gua_name().data())
                                                   +QString("\n")
                                                   +QString(my_gua.bian_gua_info().data()));
    QString drawing_gua_2;
    QString yao_info_2;
    for(int i=5;i>=0;i--)
    {
        if( my_gua.bian_gua_yao_info(i).is_yang() == true)
        {
            drawing_gua_2+="------------\n";
        }else
        {
            drawing_gua_2+="----     ----\n";
        }

        yao_info_2 += QString( my_gua.bian_gua_yao_info(i).info().data())+"\n";
    }
    my_ui->stacked_tab_widget_label[1][1]->setText(drawing_gua_2);
    my_ui->stacked_tab_widget_label[1][2]->setText(yao_info_2);

    //加载页面三
    if(my_gua.bian_yao_count()==1)
    {
        my_ui->stacked_tab_widget_label[2][0]->setText(QString("一爻变者，以本卦变爻的爻辞占。"));
        my_ui->stacked_tab_widget_label[2][1]->setText(drawing_gua);
        for(int i=5;i>=0;i--)
        {
            if(my_gua.ben_gua_yao_info(i).is_yang() != my_gua.bian_gua_yao_info(i).is_yang())
            {
                my_ui->stacked_tab_widget_label[2][2]->setText(my_gua.ben_gua_yao_info(i).info().data());
                break;
            }
        }
    }
    else if(my_gua.bian_yao_count()==2)
    {
        my_ui->stacked_tab_widget_label[2][0]->setText(QString("二爻变者,以本卦二变的爻辞占,以上爻的爻辞为主。"));
        my_ui->stacked_tab_widget_label[2][1]->setText(drawing_gua);
        QString temp_str;
        for(int i=5;i>=0;i--)
        {
            if(my_gua.ben_gua_yao_info(i).is_yang() != my_gua.bian_gua_yao_info(i).is_yang())
            {
                temp_str+=QString(my_gua.ben_gua_yao_info(i).info().data())+"\n";
            }
        }
        my_ui->stacked_tab_widget_label[2][2]->setText(temp_str);
    }
    else if(my_gua.bian_yao_count()==3)
    {
        my_ui->stacked_tab_widget_label[2][0]->setText(QString("三爻变者,以本卦及之卦的卦辞占,以本卦的卦辞为主。"));
        my_ui->stacked_tab_widget_label[2][1]->setText(drawing_gua);
        my_ui->stacked_tab_widget_label[2][2]->setText(QString("本卦：")
                                                       +QString(my_gua.ben_gua_info().data())
                                                       +QString("\n")
                                                       +QString("变卦：")
                                                       +QString(my_gua.bian_gua_info().data()));
    }
    else if(my_gua.bian_yao_count()==4)
    {
        my_ui->stacked_tab_widget_label[2][0]->setText(QString("四爻变者,以之卦中二不变的爻辞占,以下爻的爻辞为主。"));
        my_ui->stacked_tab_widget_label[2][1]->setText(drawing_gua_2);
        QString temp_str;
        for(int i=5;i>=0;i--)
        {
            if(my_gua.ben_gua_yao_info(i).is_yang() == my_gua.bian_gua_yao_info(i).is_yang())
            {
                temp_str+=QString(my_gua.bian_gua_yao_info(i).info().data())+"\n";
            }
        }
        my_ui->stacked_tab_widget_label[2][2]->setText(temp_str);

    }
    else if(my_gua.bian_yao_count()==5)
    {
        my_ui->stacked_tab_widget_label[2][0]->setText(QString("五爻变者,以之卦中不变的爻辞占。"));
        my_ui->stacked_tab_widget_label[2][1]->setText(drawing_gua);
        for(int i=5;i>=0;i--)
        {
            if(my_gua.ben_gua_yao_info(i).is_yang() == my_gua.bian_gua_yao_info(i).is_yang())
            {
                my_ui->stacked_tab_widget_label[2][2]->setText(my_gua.bian_gua_yao_info(i).info().data());
                break;
            }
        }
    }
    else if(my_gua.bian_yao_count()==6)
    {
        my_ui->stacked_tab_widget_label[2][0]->setText(
                    QString("六爻全变者,乾坤两卦以用九和用六的辞占,并参考之卦卦辞。余六十二卦占以之卦卦辞。"));
        if(QString(my_gua.ben_gua_name().data())==QString("乾为天"))
        {
            my_ui->stacked_tab_widget_label[2][1]->setText(drawing_gua);
            my_ui->stacked_tab_widget_label[2][2]->setText(QString("用九：见群龙无首，吉。\n")
                                                           +my_gua.bian_gua_info().data());

        }
        else if(QString(my_gua.ben_gua_name().data())==QString("坤为地"))
        {
            my_ui->stacked_tab_widget_label[2][1]->setText(drawing_gua);
            my_ui->stacked_tab_widget_label[2][2]->setText(QString("用六：利永贞。\n")
                                                           +my_gua.bian_gua_info().data());
        }
        else
        {
            my_ui->stacked_tab_widget_label[2][1]->setText(drawing_gua_2);
            my_ui->stacked_tab_widget_label[2][2]->setText(my_gua.bian_gua_info().data());
        }
    }
    else if(my_gua.bian_yao_count()==0)
    {
         my_ui->stacked_tab_widget_label[2][0]->setText(QString("六爻全不变者,以本卦卦辞占。"));
         my_ui->stacked_tab_widget_label[2][1]->setText(drawing_gua);
         my_ui->stacked_tab_widget_label[2][2]->setText(my_gua.ben_gua_info().data());

    }
    else
    {

    }


}
