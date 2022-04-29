#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <netinet/in.h>

#define MAX_MSG 1000

// typedef struct CliNet CliNet;

typedef enum CliErr 
{
	CLIENT_SUCCESS = 0,
	CLIENT_NOT_INITIALIZED,
	CLIENT_CONNECTION_FAILED,
	CLIENT_SERVER_CLOSED_CONNECTION,
	CLIENT_SEND_FAILED,
	CLIENT_RECIEVE_FAILED	

} ClientErr;


template <typename T>
class Client
{
public:
    Client(const char* a_serverIpAdress = "127.0.0.1", size_t a_port = 8888);
	~Client();
    int clientSend(T* a_message, size_t a_msgSize);
    ClientErr recieve(T* a_message, size_t a_msgSize);
    void disconnect();
	int clientId() const;

private:
    void assignServerIPAndPort(struct sockaddr_in* a_servaddr, size_t a_servaddrSsize, const char* a_serverIpAdress, size_t a_port);
    ClientErr clientConnect(size_t a_servaddrSsize);

private:
    int m_clientId;
    struct sockaddr_in m_servaddr;
    struct sockaddr_in m_cli;
};

#include "./inl/client.hxx"

#endif // CLIENT_HPP