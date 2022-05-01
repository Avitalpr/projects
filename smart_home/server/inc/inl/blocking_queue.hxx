#ifndef BLOCKING_QUEUE_HXX
#define BLOCKING_QUEUE_HXX

#include <cstddef>
#include <cassert>
#include <pthread.h>
#include "blocking_queue.hpp"
#include <condition_variable>
#include <mutex>


namespace cpp
{

class QueueExceptions : public std::exception
{
public:

    virtual const char* what() const  throw()
    {
        return "blocking queue failed";
    } 
};

class QueueConstructorExceptions : public QueueExceptions
{
public:

    virtual const char* what() const  throw()
    {
        return "blocking queue constructor failed";
    } 
};

class QueueEnqueueExceptions : public QueueExceptions
{
public:

    virtual const char* what() const  throw()
    {
        return "blocking enqueue failed";
    } 
};

class QueueDequeueExceptions : public QueueExceptions
{
public:

    virtual const char* what() const  throw()
    {
        return "blocking dequeue failed";
    } 
};

class QueueSizeExceptions : public QueueExceptions
{
public:

    virtual const char* what() const  throw()
    {
        return "blocking size failed";
    } 
};

class QueueCapacityExceptions : public QueueExceptions
{
public:

    virtual const char* what() const  throw()
    {
        return "blocking capacity failed";
    } 
};

class QueueIsEmptyExceptions : public QueueExceptions
{
public:

    virtual const char* what() const  throw()
    {
        return "blocking is empty failed";
    } 
};

class QueueIsFullExceptions : public QueueExceptions
{
public:

    virtual const char* what() const  throw()
    {
        return "blocking is full failed";
    } 
};

class QueueClearExceptions : public QueueExceptions
{
public:

    virtual const char* what() const  throw()
    {
        return "blocking clear failed";
    } 
};

// template <typename Key, typename Value>
// struct LockGuard{
    
//     LockGuard(std::unique_lock<std::mutex>& a_mutex)
//     : m_mutex(a_mutex)
//     {
        
//         m_mutex.lock();
//     }

//     ~LockGuard()
//     {
//         m_mutex.unlock();
//     }

// private:

//     std::std::mutex& m_mutex;

// };

// Lock lock(m_mutex);
//     m_cond.wait(lock, [this]() {return !nonBlockFull();});
//     m_queue.enqueue(a_item);
//     m_cond.notify_all();

typedef std::unique_lock<std::mutex> LockGuard;


template <typename T>
inline BlockingQueue<T>::BlockingQueue(size_t a_capacity)
: m_queue(a_capacity)
, m_mutex()
, m_cond()
{ 
}

template <typename T>
inline bool BlockingQueue<T>::enqueue(T a_item)
{

    LockGuard lock(m_mutex);

    m_cond.wait(lock, [this]() {return !this->unBlockIsFull();});
    m_queue.enqueue(a_item);
    m_cond.notify_all();   

    return true;
}

template <typename T>
inline bool BlockingQueue<T>::dequeue(T& a_content)
{

    LockGuard lock(m_mutex);

    m_cond.wait(lock, [this]() {return !this->unBlockIsEmpty();});
    a_content = m_queue.dequeue();
    m_cond.notify_all(); 

    return true;
    

}

template <typename T>
inline size_t BlockingQueue<T>::size() const
{
    size_t res;
    // try
    // {
        LockGuard lock(m_mutex);

        res = m_queue.size();


    // }
    // catch(const MutexExceptions& e)
    // {
    //     throw cpp::QueueSizeExceptions();
    // }
    return res;

}

template <typename T>
inline size_t BlockingQueue<T>::capacity() const
{
    size_t res;
    // try
    // {
        LockGuard lock(m_mutex);

        res = m_queue.capacity();

    // }
    // catch(const MutexExceptions& e)
    // {
    //     throw cpp::QueueCapacityExceptions();
    // }
    return res;

}

template <typename T>
inline bool BlockingQueue<T>::isEmpty() const
{
    bool res;
    // try
    // {
        LockGuard lock(m_mutex);
        res = m_queue.isEmpty();
 
    // }
    // catch(const MutexExceptions& e)
    // {
    //     throw cpp::QueueIsEmptyExceptions();
    // }
    return res;

}

template <typename T>
inline bool BlockingQueue<T>::isFull() const
{
    bool res;
    // try
    // {
        LockGuard lock(m_mutex);
        res = m_queue.isFull();
 
    // }
    // catch(const MutexExceptions& e)
    // {
    //     std::cerr << e.what() << '\n';
    //     throw cpp::QueueIsFullExceptions();
    // }
    return res;

}

template <typename T>
inline void BlockingQueue<T>::clear()
{
    // try
    // {
        LockGuard lock(m_mutex);
        m_queue.clear();

    // }
    // catch(const MutexExceptions& e)
    // {
    //     throw cpp::QueueClearExceptions();
    // }
    
}

template <typename T>
inline bool BlockingQueue<T>::unBlockIsEmpty() const
{
    return m_queue.isEmpty();
}

template <typename T>
inline bool BlockingQueue<T>::unBlockIsFull() const
{
    return m_queue.isFull();
}


}  // namespace cpp


#endif // BLOCKING_QUEUE_HXX