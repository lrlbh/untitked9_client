#include "my_tcp.h"
#include<QTcpSocket>
#include<QHostAddress>
#include"protocol_zhouyi.h"
#include"protocol_laozi.h"
#include<qmessagebox.h>
#include<qwidget.h>
#include "ui.h"
#include"gua_info.pb.h"
#include"my_aes.h"
#include"my_rsa.h"
my_tcp::my_tcp()
{
    new_tcp();
}


void my_tcp::send_data(char *write_buf,int write_len)
{

    //发送数据，如果发送失败重新连接
    if(this->cfd->write(write_buf,write_len)==-1)
    {
        //tcp连接重新建立，释放上个连接的资源
        this->data = "";
        delete this->cfd;

        new_tcp();
        this->cfd->write(write_buf,write_len);
    }
}
void my_tcp::new_tcp()
{
    ui * my_ui = ui::get_ui();
    this->cfd = new QTcpSocket();
    this->cfd->connectToHost(QHostAddress("49.234.181.2"),8000);

    connect( this->cfd,&QTcpSocket::readyRead,this,[=]()
    {

        char read_buf[1400]={0};
        qint64 ret_read_buf=0;
        //while确保数据被读完
        while((ret_read_buf= this->cfd->read(read_buf,qint64(sizeof(read_buf))))!=0)
        {
            //检查接收到到的数据
            for(int i=0;i<ret_read_buf;i++)
            {

                //读取到一条完整的协议就处理
                if(read_buf[i] == '\0')
                {

                    memset(read_buf,0,sizeof(read_buf));
                    //对应协议调用对应类
                    if(this->data[data.size()-1] == 0B00000001)
                    {
                        data[data.size()-1]='\0';

                        protocol_zhouyi pz(data);
                        data ="";
                    }
                    //对应协议调用对应类
                    else if(data[data.size()-1] == 0B00000010)
                    {
                        data[data.size()-1]='\0';
                        protocol_laozi laozi(data);
                        data ="";
                    }
                    else if (data[data.size()-1] == 0B00000100)
                    {

                        data[data.size()-1]='\0';
                        //获取到公钥数据
                        aes_key aes_data;
                        aes_data.ParseFromString(data);
                        if(aes_data.is_pub_key()==true)
                        {
                            my_ui->aes =new my_aes;
                            //获取到服务器回发的aes秘钥
                            qDebug()<<QString(my_ui->rsa->rsa_prikey_decrypt(aes_data.key().data()).data());

                            my_ui->aes->add_base64_key( my_ui->rsa->rsa_prikey_decrypt(aes_data.key().data()));

                            QMessageBox::critical(my_ui->register_widget,"秘钥收到","秘钥收到");
                            //设置秘钥可以使用
                            my_ui->pub_is_ok =true;
                        }
                        data ="";
                    }
                    else if(data[data.size()-1] == 0B000000101)    //获取验证码时服务器回发
                    {
                        data[data.size()-1]='\0';
                        ret_registered_phone rrp;
                        rrp.ParseFromString(data);
                        if(rrp.verification_state() ==0)
                        {
                            qDebug()<<"验证码发送成功";
                        }
                        else if(rrp.verification_state() ==33)
                        {
                            qDebug()<<"每个号码30秒只能发送一次";
                        }
                        else if(rrp.verification_state() ==2)
                        {
                            qDebug()<<"手机号码有误！";
                        }

                        else if(rrp.verification_state() ==22)
                        {
                            qDebug()<<"每个号码一个小时只能发送一次";
                        }

                        data ="";
                    }
                    else if(data[data.size()-1] == 0B000001000)
                    {

                        data[data.size()-1]='\0';

                        is_ok isok;
                        isok.ParseFromString(data);

                        if(isok.is_pub_key() == true)
                        {
                            qDebug()<<"验证码正确";
                        }
                        else
                        {
                             qDebug()<<"验证码错误";
                        }

                        data ="";

                    }
                    //对应协议调用对应类
                    else
                    {
                        data ="";
                    }

                }
                //正常数据拷贝到string中
                else
                {
                    data += read_buf[i];
                }

                //每次循环结束，初始化一下read_buf
                if((i+1)==ret_read_buf)
                {
                    memset(read_buf,0,sizeof(read_buf));
                }

            }

        }



    });

}
