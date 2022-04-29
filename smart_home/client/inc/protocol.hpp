#ifndef PROTOCOL_PACK_HPP
#define PROTOCOL_PACK_HPP

#include "event.hpp"

namespace protocol
{

template <typename T>
size_t pack(smart_home::Event<T> const& a_event, char* a_buffer);

template <typename T>
smart_home::Event<T> unpack(char const* a_message);
    
} // namespace protocol

#include "./inl/protocol.hxx"
#endif // PROTOCOL_H