#ifndef SERVER_HPP
#define SERVER_HPP

#include <cstdlib>
#include <vector>
#include <atomic>

typedef struct Server Server;

typedef enum Status
{ 
    CONNECTION_FAIL = -1, 
    SERVER_OK, 
    INIT_FAIL, 
    RECV_FAIL,
    SEND_FAIL,
    NULL_ERR,
    ALLOC_ERR 
					 
} Status; 


typedef void (*MsgReceivedFunc)(int a_clientID, void* a_buffer, int a_bufferSize, void* a_context); 


struct ParamsContext
{
	MsgReceivedFunc m_msgReceived;
	void* m_context;


ParamsContext()
: m_msgReceived(nullptr)
, m_context(nullptr)
{
}

ParamsContext(MsgReceivedFunc a_recv, void* a_con = nullptr)
: m_msgReceived(a_recv)
, m_context(a_con)
{
}

};

class Server 
{
public:
    Server(size_t a_MTU = 1500, size_t a_max = 1024, ParamsContext a_context = ParamsContext());
    ~Server();

    Status ServerRun();
    Status ServerSendMessage(int a_clientID, void* a_bufferSend, int a_bufferSize);
    Status ServerStop();

private:
    int Init(int* a_sock, fd_set* a_master);
    int CreateStreamConnection(int* a_sock, fd_set* a_master);
    int Initialization(int _sock) ;
    int CheckNewClients();
    void CheckCurrentClients(fd_set* a_temp, int a_activity);
    int Receive(int a_sock);
    void CloseAllSockets();

private:
    Server(Server const& a_source);
    Server& operator=(Server const& a_other);

private:
    ParamsContext m_AppFunctions;
    std::vector<int> m_clientsList;
    fd_set m_master;
    fd_set m_activitySockets;
    size_t m_MTU;
    size_t m_maxSockets;
    size_t m_clientsCounter;
    std::atomic<int> m_status;
    int m_listenerSocket;
};



#endif  // SERVER_HPP