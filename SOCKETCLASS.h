#pragma once
#ifndef SOCKETCLASS_H
#define SOCKETCLASS_H
#include <WinSock2.h>
#define BUFSIZE 2049
class SOCKETCLASS
{
public:
	//���캯��
	SOCKETCLASS(int af, int type, int protocol);
	SOCKETCLASS();
	
	//ע:������ʹ��C����ַ�������string

	//��
	int m_bind(const char* IP, u_short port);
	
	//����
	int m_listen(int backlog);

	//��������
	SOCKETCLASS m_accept();

	//��������
	int m_connect(const char* IP, u_short port);

	//�����봫��
	char* m_recv(int len = BUFSIZE);
	int m_send(const char* senddata);

	//�ر��׽���
	int m_close();
	
	//����DLL
	static void dll_stop();

	//UDP��Ľ��պʹ���
	char* m_recvfrom(int len = BUFSIZE);
	//����IP��portʱΪ�����ߵ�IP�Ͷ˿� �� ��һ��Ŀ���IP�Ͷ˿�
	int m_sendto(const char* senddata, const char* IP = "", u_short port = 0);
	
	

private:
	static WSADATA wsaData;
	//�ж�DLL�Ƿ��Ѿ�����
	static bool dll_is_using;
	//��װ�ļ����׽�������
	int m_af = AF_INET;
	int m_type = SOCK_STREAM;
	int m_protocol = IPPROTO_TCP;
	//��װһ��SOCKET
	SOCKET m_socket;
	//����DLL����
	static bool dll_error;

	//��װstruct sockaddr_in �ṹ��
	struct sockaddr_in addr;
	
	struct sockaddr_in targetaddr;

	int addrlen = sizeof(SOCKADDR);
	

	//����
	char recvdata[BUFSIZE] = "";
	char senddata[BUFSIZE] = "";
	
};
#endif // !SOCKETCLASS_H