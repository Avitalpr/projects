#pragma once

#include "server.hpp"
// #include "protocol.hpp"
// #include "blocking_queue.hpp"
// #include "thread.hpp"
#include "controller.hpp"
#include <memory>
#include "router.hpp"
#include "subject.hpp"
#include "reader.hpp"

namespace smart_home
{


class ServerManager
{
public:
    ServerManager(std::shared_ptr<Router> a_router);

    void run();


private:

    void serverReceive();

private:
    Reader m_reader;
    std::shared_ptr<Router> m_router;
    ParamsContext m_params;
    Server m_server;
    // std::unique_ptr<Controller> m_controller;
    
};


} // namespace smart_home
