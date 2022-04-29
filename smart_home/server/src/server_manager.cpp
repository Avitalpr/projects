#include "server_manager.hpp"
#include <iostream>
#include <memory>
#include "interest.hpp"
#include "create_controller.hpp"
#include "protocol.hpp"
#include "event.hpp"
#include "loader.hpp"

namespace smart_home
{

void MsgReceivedFunc(int a_clientID, void* a_buffer, int a_bufferSize, void* a_context)
{
    std::cout << "avital\n";
    char const* buffer = static_cast<char const*>(a_buffer);
    std::shared_ptr<Router>* ptr = static_cast<std::shared_ptr<Router>* >(a_context);
    Event<int> event = protocol::unpack<int>(buffer);
    (*ptr)->notify(Interest(event.type(), event.location()), event);


}

ServerManager::ServerManager(std::shared_ptr<Router> a_router)
: m_reader()
,  m_router(a_router)//std::make_unique<Subject>())
, m_params(MsgReceivedFunc, &m_router)
, m_server(1000, 100, m_params)
// , m_controller(std::make_unique<TempController>(5))
{

}

void ServerManager::run()
{
    std::ifstream file = m_reader.open("config.txt");
    std::vector<ConfigData> agents = m_reader.read(file, '|');
    CreateController creator;
    for(auto const& e: agents)
    {
        std::shared_ptr<Controller> control = creator.create(e)(e);
        std::vector<Interest> interes = control->getInterests();
        for(auto e: interes)
        {
            m_router->attach(control, e);
        }
    }
    m_server.ServerRun();
}

} // smart_home