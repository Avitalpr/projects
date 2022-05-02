#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <cstdlib>
#include <cstddef>
#include <netinet/in.h>
#include <string.h>
#include <sys/select.h>
#include <errno.h>
#include <new>
#include <vector>
#include <iterator>
#include <cassert>
#include <iostream>
#include "server.hpp"

const int SERVER_PORT = 8888;
const char* SERVER_IP = "127.0.0.1";
const int MAX_FD = 1024;
const bool ON = 1;
const bool OFF = 0;
const int FAIL = -1;
const int ERR_SIZE = 100;


Server::Server(size_t a_MTU, size_t a_max, ParamsContext a_context)
{
	if(Init(&m_listenerSocket, &m_master) != SERVER_OK) 
	{
		return;
	}
	
	m_AppFunctions = a_context;
	m_clientsCounter = 1;
	m_status = ON;
	m_maxSockets = a_max;
	m_MTU = a_MTU;
    std::vector<int> m_clientsList;
}


Status Server::ServerRun() 
{
	fd_set temp;
	int activity = 0;
	m_status = ON;

	while(m_status == ON) 
	{
		temp = m_master;
		activity = select (MAX_FD, &temp , nullptr, nullptr, nullptr);

		if(FD_ISSET(m_listenerSocket, &temp) == 1)
		{	
			CheckNewClients();
			--activity;
		}

		if(activity > 0)
		{
			CheckCurrentClients(&temp, activity);
		}
	
		if(m_status == OFF)
		{
			break;
		}
	}
	return SERVER_OK ;
}

Status Server::ServerSendMessage(int a_clientID, void* a_bufferSend, int a_bufferSize) 
{
	int bytes_sent;
	if(a_bufferSend == nullptr)
	{
		return SEND_FAIL ;
	}
	bytes_sent = send (a_clientID, a_bufferSend, a_bufferSize, 0);
	if(bytes_sent < 0) 
	{
		return SEND_FAIL;
	}
	return SERVER_OK ;
}

Server::~Server() 
{
	CloseAllSockets();
}

// Status Server::ServerStop()
// {
// 	m_status = OFF ; 
// 	const char* message = "stop the system\n";
// 	void* m = const_cast<void*>(static_cast<const void*>(message));
// 	m_poisonSocket.ClientSend(m, 17);
// 	return SERVER_OK;
// }

int Server::Init(int* a_sock, fd_set* a_master) 
{
	if(CreateStreamConnection(a_sock, a_master) != SERVER_OK)
	{
		std::cout << "initialization1\n";
		return INIT_FAIL;
	}
	if(Initialization(*a_sock) != SERVER_OK) 
	{
		std::cout << "initialization2\n";
		return INIT_FAIL;
	}
	if(listen(*a_sock, SOMAXCONN) < 0)
	{
		std::cout << "initialization3\n";
		return INIT_FAIL;
	}
	return SERVER_OK;
}

int Server::CreateStreamConnection(int* a_sock, fd_set* a_master) 
{
	int optval = 1;
	FD_ZERO(a_master);
	*a_sock = socket(AF_INET, SOCK_STREAM, 0);
	if(*a_sock < 0)
 	{
		return INIT_FAIL ;
	}
	if(setsockopt(*a_sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0)
	{
		return INIT_FAIL;
	}
	FD_SET(*a_sock, a_master);
	return SERVER_OK;
}

int Server::Initialization(int a_sock) 
{
	struct sockaddr_in sin;
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr =   INADDR_ANY ; 
	sin.sin_port = htons( SERVER_PORT );
	if(bind(a_sock, (struct sockaddr*) &sin, sizeof(sin)) < 0) 
	{
		return INIT_FAIL;
	}
	return SERVER_OK;
}

int Server::CheckNewClients () 
{
	int sock , sockNum;
	struct sockaddr_in client_sin;
	socklen_t addr_len = sizeof(client_sin);	
	sockNum = accept(m_listenerSocket, (struct sockaddr*) &client_sin, &addr_len);
	if (sockNum < 0)
	{
		return FAIL ;
	}
	else 
	{
		if(m_clientsCounter > m_maxSockets) 
		{
			close(sockNum);
			return FAIL;
		}
        sock = sockNum;
        m_clientsList.push_back(sock);
		FD_SET(sock, &m_master);
		++m_clientsCounter;
		
		return sockNum ;
	}
}


int Server::Receive(int  a_sock)
{
	size_t msgSize = 0;
	int bytes_received = 0;
	char* bufferRecv = new char[m_MTU];
	char* p = bufferRecv;

	do{
		bytes_received = recv(a_sock, p, 1, 0);

		 if(bytes_received == -1 || bytes_received == 0)
		 {
		 	return RECV_FAIL;  
		 }
		 msgSize = *p - 1;
		 p += bytes_received;

	}
	while(bytes_received != 1);
	size_t origSize = msgSize;
	assert(bytes_received < int(m_MTU));
	do
	{
		bytes_received = recv (a_sock,p, msgSize, 0);
		if(bytes_received < 0) 
		{
			return RECV_FAIL;  
		}
		msgSize -= bytes_received;
		p += bytes_received;

	} while (msgSize > 0);

    m_AppFunctions.m_msgReceived (a_sock , bufferRecv , origSize ,m_AppFunctions.m_context);

   delete[] bufferRecv;
   return SERVER_OK ;
}

void Server::CheckCurrentClients(fd_set* a_temp, int a_activity) 
{
	int socket  , status;
    std::vector<int>::iterator it;
	std::vector<int>::iterator begin = m_clientsList.begin();
	std::vector<int>::iterator end =  m_clientsList.end();
	for(it = begin; it != end && a_activity != 0; ++it)
	{
		socket = *it;
		// if(socket == m_poisonSocket.clientId())
		// {
		// 	m_status = OFF;
		// }	
		if(FD_ISSET(socket, a_temp)) 
		{
			--a_activity;
			status = Receive(socket);
			if(status == RECV_FAIL)
			{
				close(socket);
                m_clientsList.erase(it);
				--m_clientsCounter;
				--it;
				FD_CLR(socket, &m_master);
			}
			
		}
		
	}
}

void Server::CloseAllSockets() 
{
    std::vector<int>::iterator it;
	std::vector<int>::iterator begin = m_clientsList.begin();
	std::vector<int>::iterator end =  m_clientsList.end();
	int socket;
	for(it = begin; it != end; ++it)
	{
		socket = *it;
		close(socket);
	}
}