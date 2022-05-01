#ifndef BLOCKING_QUEUE_HPP
#define BLOCKING_QUEUE_HPP

#include <cstddef>
#include <pthread.h>
#include <exception>
#include "queue.hpp"
#include <condition_variable>
#include <mutex>
#define SIZE 64

namespace cpp
{

template <typename T>
class BlockingQueue
{
public:
    
    explicit BlockingQueue(size_t const a_capacity = SIZE);
  
    bool enqueue(T a_item);
    bool dequeue(T& a_content);

    size_t size() const;
    size_t capacity() const;
    bool isEmpty() const;
    bool isFull() const;
    void clear();

private:

    BlockingQueue(BlockingQueue const& a_source);
    BlockingQueue& operator=(BlockingQueue const& a_queue);

    bool unBlockIsEmpty() const;
    bool unBlockIsFull() const;

private:

    cpp::Queue<T> m_queue;
    // mutable mt::Mutex m_mutex;
    mutable std::mutex m_mutex;
    mutable std::condition_variable m_cond;
    
};


} // namespace cpp

#include "./inl/blocking_queue.hxx"

#endif // BLOCKING_QUEUE_HPP