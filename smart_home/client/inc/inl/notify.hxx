#pragma once

namespace smart_home
{

template <typename DATA>
void Notifier<DATA>::send(DATA* a_data, size_t a_size)
{
    m_client.clientSend(a_data, a_size);
}
    
} // namespace smart_home
