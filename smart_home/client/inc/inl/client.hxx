#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>
#include <cstddef>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/select.h>
#include <iostream>

#define MAX_WORD 80
#define PORT 8080


template <typename T>
Client<T>::Client(const char* a_serverIpAdress, size_t a_port)
{
	if(a_serverIpAdress == nullptr)
	{
		return;
	}
	
	assignServerIPAndPort(&m_servaddr, sizeof(m_servaddr), a_serverIpAdress, a_port);
	
	m_clientId = socket(AF_INET, SOCK_STREAM, 0);
	if(m_clientId == -1) 
	{
		return;
	}

	if(clientConnect(sizeof(m_servaddr)) != CLIENT_SUCCESS)
	{
		return;
	}
	std::cout << "connected" << "\n";
}

template <typename T>
CliErr Client<T>::clientConnect(size_t a_servaddrSsize)
{
	if(connect(m_clientId, (struct sockaddr*)&m_servaddr, sizeof(m_servaddr)) != 0) {
		return CLIENT_CONNECTION_FAILED;
	}

	return CLIENT_SUCCESS;
}

template <typename T>
Client<T>::~Client()
{
	close(m_clientId);
}

template <typename T>
int Client<T>::clientSend(T* a_message, size_t a_msgSize)
{
	//char* message = static_cast<char*>(&a_message);
	int byteSend = send(m_clientId, a_message, a_msgSize, 0);
	std::cout << "senddd:" << a_message << "\n";
	
	if(byteSend < 0)
	{
		if(errno != EAGAIN && errno != EWOULDBLOCK)
		{
			return 0;
		}
	}
	return byteSend;
}

template <typename T>
CliErr Client<T>::recieve(T* a_message, size_t a_msgSize)
{
	int recvErr;
	bzero(a_message, a_msgSize);
	
	recvErr = recv(m_clientId, a_message, a_msgSize, 0);
	if(recvErr == 0)
	{
		return CLIENT_SERVER_CLOSED_CONNECTION;
	}
	else if(recvErr < 0)
	{
		if(errno != EAGAIN && errno != EWOULDBLOCK)
		{
			return CLIENT_RECIEVE_FAILED;
		}
	}
	return CLIENT_SUCCESS;
}

template <typename T>
void Client<T>::disconnect()
{
	close(m_clientId);
}


template <typename T>
void Client<T>::assignServerIPAndPort(struct sockaddr_in* a_servaddr, size_t a_servaddrSsize, const char* a_serverIpAdress, size_t a_port)
{
	bzero(a_servaddr, a_servaddrSsize);   

	a_servaddr->sin_family = AF_INET;
	a_servaddr->sin_addr.s_addr = inet_addr(a_serverIpAdress);
	a_servaddr->sin_port = htons(a_port);
}

template <typename T>
int Client<T>::clientId() const
{
	return m_clientId;
}





