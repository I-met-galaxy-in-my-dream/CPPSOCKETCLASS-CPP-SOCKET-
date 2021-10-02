#include "SOCKETCLASS.h"
#pragma comment (lib,"ws2_32.lib")


WSADATA SOCKETCLASS::wsaData;

//判断dll是否已经启动
bool SOCKETCLASS::dll_is_using = false;
//判断dll是否成功启动
bool SOCKETCLASS::dll_error = false;
SOCKETCLASS::SOCKETCLASS(int af, int type, int protocol):m_af(af),m_type(type),m_protocol(protocol)
{
	if (!this->dll_is_using)
	{
		if (WSAStartup(MAKEWORD(2, 2), &this->wsaData))//返回0执行成功
		{
			this->dll_error = true;
			return;
		}
		this->dll_is_using = true;
	}
	this->m_socket = socket(this->m_af, this->m_type, this->m_protocol);
}
SOCKETCLASS::SOCKETCLASS()
{
	if (!this->dll_is_using)
	{
		if (WSAStartup(MAKEWORD(2, 2), &this->wsaData))//返回0执行成功
		{
			this->dll_error = true;
			return;
		}
		this->dll_is_using = true;
	}
	this->m_socket = socket(this->m_af, this->m_type, this->m_protocol);
}

//绑定
int SOCKETCLASS::m_bind(const char* IP, u_short port)
{
	this->addr.sin_family = this->m_af;
	this->addr.sin_addr.s_addr = inet_addr(IP);
	this->addr.sin_port = htons(port);
	return bind(m_socket, (SOCKADDR*)&this->addr, sizeof(SOCKADDR));
}

//监听
int SOCKETCLASS::m_listen(int backlog)
{
	return listen(this->m_socket, backlog);
}

//接收请求
SOCKETCLASS SOCKETCLASS::m_accept()
{
	SOCKETCLASS temp;
	temp.m_socket = accept(this->m_socket, (SOCKADDR*)&this->targetaddr, &this->addrlen);
	temp.m_af = AF_INET;
	temp.m_type = SOCK_STREAM;
	temp.m_protocol = IPPROTO_TCP;
	return temp;
}

//请求连接
int SOCKETCLASS::m_connect(const char* IP, u_short port)
{
	this->targetaddr.sin_family = AF_INET;
	this->targetaddr.sin_addr.s_addr = inet_addr(IP);
	this->targetaddr.sin_port = htons(port);
	return connect(this->m_socket, (SOCKADDR*)&this->targetaddr, sizeof(SOCKADDR));
}

char* SOCKETCLASS::m_recv(int len)
{
	recv(this->m_socket, this->recvdata, len, NULL);
	return this->recvdata;
}

int SOCKETCLASS::m_send(const char* senddata)
{
	if (BUFSIZE >= sizeof(senddata))
	{
		strcpy(this->senddata, senddata);
	}
	else
	{
		strncpy(this->senddata, senddata, BUFSIZE);
	}
	
	return send(this->m_socket, senddata, sizeof(senddata), NULL);
}

//关闭套接字
int SOCKETCLASS::m_close()
{
	return closesocket(this->m_socket);
}

//清理DLL
void SOCKETCLASS::dll_stop()
{
	if (dll_is_using)
	{
		if (WSACleanup())
		{
			dll_error = true;
			return;
		}
		dll_is_using = false;
	}
}

//UDP接收
char* SOCKETCLASS::m_recvfrom(int len)
{
	recvfrom(this->m_socket, this->recvdata, len, NULL, (SOCKADDR*)&this->targetaddr, &this->addrlen);
	return this->recvdata;
}

//UDP传输
int SOCKETCLASS::m_sendto(const char* senddata, const char* IP, u_short port)
{
	if (BUFSIZE >= sizeof(senddata))
	{
		strcpy(this->senddata, senddata);
	}
	else
	{
		strncpy(this->senddata, senddata, BUFSIZE);
	}
	if ((strcmp(IP, "") == 0) && (port == 0))
	{
		return sendto(this->m_socket, senddata, sizeof(senddata), NULL, (SOCKADDR*)&this->targetaddr, sizeof(SOCKADDR));
	}
	else
	{
		this->targetaddr.sin_family = this->m_af;
		this->targetaddr.sin_addr.s_addr = inet_addr(IP);
		this->targetaddr.sin_port = htons(port);
		return sendto(this->m_socket, senddata, sizeof(senddata), NULL, (SOCKADDR*)&this->targetaddr, sizeof(SOCKADDR));
	}
}