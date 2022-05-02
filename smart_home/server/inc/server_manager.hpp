#pragma once

#include "server.hpp"
// #include "protocol.hpp"
// #include "blocking_queue.hpp"
// #include "thread.hpp"
#include "controller.hpp"
#include <memory>
#include <vector>
#include "router.hpp"
#include "subject.hpp"
#include "reader.hpp"
#include "logger.hpp"
#include "blocking_queue.hpp"
#include "event.hpp"
#include "thread.hpp"
#include "smart_home_ui.hpp"


namespace smart_home
{

namespace details_impl
{
class Args;
}


class ServerManager
{
public:
    using Devices = std::vector<std::shared_ptr<Device>>;
    explicit ServerManager(std::shared_ptr<Router> a_router);

    void run();


private:

    void serverReceive();
    void eventsHandler();
    // void* innerHandler(void*);

private:
    Reader m_reader;
    cpp::BlockingQueue<Event<int> > m_eventsQueue;
    std::shared_ptr<Router> m_router;
    Logger& m_logger;
    std::pair<std::shared_ptr<Router>, Logger&> m_contextPair;
    ParamsContext m_params;
    Server m_server;
    mt::ThreadGroup<std::shared_ptr<details_impl::Args>> m_eventHandlers;
    std::shared_ptr<details_impl::Args> m_args;
    Devices m_devices;
    Home m_home;


};


} // namespace smart_home
