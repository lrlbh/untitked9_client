#ifndef MY_TCP_H
#define MY_TCP_H
#include<widget.h>
#include<string>
class QTcpSocket;

class my_tcp:public QObject
{
   Q_OBJECT

public:
    my_tcp();

    void send_data(char *write_buf,int write_len);
private:
    //套接字
    QTcpSocket *cfd;
    //处理黏包
    std::string data;

    //建立tcp连接，同时接受服务器发送回来的数据
    void new_tcp();
};

#endif // MY_TCP_H
