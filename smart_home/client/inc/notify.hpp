#pragma once

#include "client.hpp"

namespace smart_home
{

template <typename DATA>
class Notifier
{

public:
    Notifier() = default;
    ~Notifier() = default;

protected:
    void send(DATA* a_data, size_t a_size);

private:
    Client<DATA> m_client;

};
    
} // namespace smart_home

#include "./inl/notify.hxx"