#include "server_manager.hpp"
#include <iostream>
#include <memory>
#include "interest.hpp"
#include "create_controller.hpp"
#include "protocol.hpp"
#include "event.hpp"
#include "loader.hpp"
#include <exception>

namespace smart_home
{

namespace details_impl
{

class Args
{
public:
Args(cpp::BlockingQueue<Event<int> >& a_queue,std::shared_ptr<Router>& a_router, Logger& a_logger)
: m_queue(a_queue)
, m_router(a_router)
, m_logger(a_logger)
{
}


cpp::BlockingQueue<Event<int> >& m_queue;
std::shared_ptr<Router>& m_router;
Logger& m_logger;


};

static void* innerHandler(void* a_context)
{
    std::shared_ptr<Args>* context = static_cast<std::shared_ptr<Args>* >(a_context);

    auto& queue = (*context)->m_queue;
    auto& router = (*context)->m_router;
    auto& logger = (*context)->m_logger;

    smart_home::Event<int> event;
    queue.dequeue(event);
    
    // make documantation of events in log
    logger.log(event.toString()); // convert func from event to string is required

    // route event to the suitable controller to handle
    router->notify(Interest(event.type(), event.location()), event);
    return nullptr;

}

} // details_impl

void MsgReceivedFunc(int a_clientID, void* a_buffer, int a_bufferSize, void* a_context)
{
    char const* buffer = static_cast<char const*>(a_buffer);
    cpp::BlockingQueue<Event<int> >* queue = static_cast<cpp::BlockingQueue<Event<int> >* >(a_context);

    queue->enqueue(std::move(protocol::unpack<int>(buffer)));
}


void ServerManager::eventsHandler()
{
    m_eventHandlers.init(2, m_args, details_impl::innerHandler);
}

ServerManager::ServerManager(std::shared_ptr<Router> a_router)
: m_reader()
, m_eventsQueue(1000)
, m_router(a_router)
, m_logger(Logger::instance())
, m_contextPair(m_router, m_logger)
, m_params(MsgReceivedFunc, &m_eventsQueue)
, m_server(1000, 100, m_params)
, m_eventHandlers()
, m_args(std::make_shared<details_impl::Args>(m_eventsQueue, m_router, m_logger))
{}

void ServerManager::run()
{
    std::ifstream file = m_reader.open("config.txt");
    std::vector<ConfigData> agents = m_reader.read(file, '|');
    CreateController creator;
    for(auto const& e: agents)
    {
        std::function<std::shared_ptr<Controller>(const ConfigData&)> it;
        try
        {
            it = creator.getController(e);
            
        }
        catch(const std::exception& e)
        {
            throw e;
        }
        
        std::shared_ptr<Controller> controller = it(e);
        std::vector<Interest> interes = controller->getInterests();
        for(auto e: interes)
        {
            m_router->attach(controller, e);
        }
    }

    eventsHandler();
    m_server.ServerRun();
}

} // smart_home