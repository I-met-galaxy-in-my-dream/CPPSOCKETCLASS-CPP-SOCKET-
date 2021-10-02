#pragma once
#ifndef SOCKETCLASS_H
#define SOCKETCLASS_H
#include <WinSock2.h>
#define BUFSIZE 2049
class SOCKETCLASS
{
public:
	//构造函数
	SOCKETCLASS(int af, int type, int protocol);
	SOCKETCLASS();
	
	//注:本类暂使用C风格字符串而非string

	//绑定
	int m_bind(const char* IP, u_short port);
	
	//监听
	int m_listen(int backlog);

	//接收请求
	SOCKETCLASS m_accept();

	//请求连接
	int m_connect(const char* IP, u_short port);

	//接收与传输
	char* m_recv(int len = BUFSIZE);
	int m_send(const char* senddata);

	//关闭套接字
	int m_close();
	
	//清理DLL
	static void dll_stop();

	//UDP里的接收和传输
	char* m_recvfrom(int len = BUFSIZE);
	//不填IP和port时为发送者的IP和端口 或 上一次目标的IP和端口
	int m_sendto(const char* senddata, const char* IP = "", u_short port = 0);
	
	

private:
	static WSADATA wsaData;
	//判断DLL是否已经启动
	static bool dll_is_using;
	//封装的几个套接字属性
	int m_af = AF_INET;
	int m_type = SOCK_STREAM;
	int m_protocol = IPPROTO_TCP;
	//封装一个SOCKET
	SOCKET m_socket;
	//定义DLL错误
	static bool dll_error;

	//封装struct sockaddr_in 结构体
	struct sockaddr_in addr;
	
	struct sockaddr_in targetaddr;

	int addrlen = sizeof(SOCKADDR);
	

	//数据
	char recvdata[BUFSIZE] = "";
	char senddata[BUFSIZE] = "";
	
};
#endif // !SOCKETCLASS_H