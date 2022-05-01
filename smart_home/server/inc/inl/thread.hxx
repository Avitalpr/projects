#ifndef THREAD_HXX
#define THREAD_HXX

#include <pthread.h>
#include <cassert>
#include "thread.hpp"
#include <exception>

namespace cpp
{

class TreadExceptions : public std::exception
{
public:

    virtual const char* what() const  throw()
    {
        return "thread failed";
    } 
};

class TreadInsufficientMemoryExceptions : public TreadExceptions
{
public:

    virtual const char* what() const  throw()
    {
        return "EAGAIN - Insufficient resources to create another thread";
    } 
};

class TreadInvalidExceptions : public TreadExceptions
{
public:

    virtual const char* what() const  throw()
    {
        return "EINVAL thread is not a joinable thread";
    } 
};

class TreadNotFoundExceptions : public TreadExceptions
{
public:

    virtual const char* what() const  throw()
    {
        return "EINVAL thread is not a joinable thread";
    } 
};

class TreadDeadLockExceptions : public TreadExceptions
{
public:

    virtual const char* what() const  throw()
    {
        return "EDEADLK deadlock was detected";
    } 
};

} // namespace cpp;

namespace mt
{

inline Thread::Thread(void* (*pf)(void*), void* a_arg)
: m_context()
, m_wasJoined()
{
    int res = pthread_create(&m_tid, 0, pf, a_arg);
    switch (res)
    {
    case 0:
        break;

    case EAGAIN:
        throw cpp::TreadInsufficientMemoryExceptions();    
    
    default:
       assert(false);
    }
}

inline Thread::Thread(Thread const& a_source)
: m_tid(a_source.m_tid)
, m_context(a_source.m_context)
, m_wasJoined(a_source.m_wasJoined)
{
    a_source.m_wasJoined = true;
    a_source.m_tid = 0;
}

inline Thread::~Thread()
{
    assert(m_wasJoined);
}

inline void Thread::detach()
{
    int res = pthread_detach(m_tid);
    switch (res)
    {
    case 0:
        break;

    case EINVAL:
        throw cpp::TreadInvalidExceptions();

    case ESRCH:
        throw cpp::TreadNotFoundExceptions();

    default:
        assert(false);
    }
}

inline void Thread::join()
{
    int res = pthread_join(m_tid, &m_context);
    switch (res)
    {
    case 0:
        break;

    case EINVAL:
        throw cpp::TreadInvalidExceptions();

    case ESRCH:
        throw cpp::TreadNotFoundExceptions();

    case  EDEADLK:
        throw cpp::TreadDeadLockExceptions();

    default:
        assert(false);
    }
    m_wasJoined = true;
}

inline void* Thread::join(pthread_t const& a_thread)
{
    void* context;
    int res = pthread_join(a_thread, &context);
    switch (res)
    {
    case 0:
        break;

    case EINVAL:
        throw cpp::TreadInvalidExceptions();

    case ESRCH:
        throw cpp::TreadNotFoundExceptions();

    case  EDEADLK:
        throw cpp::TreadDeadLockExceptions();

    default:
        assert(false);
    }
    return context;
}

inline pthread_t Thread::self()
{
    return pthread_self();
}


inline void* Thread::get() const
{
    return m_context;
}


template <typename Args>
ThreadGroup<Args>::ThreadGroup(Args* a_arg, void* (*pf)(void*), size_t a_numOfThreads)
{
    for(size_t i = 0; i < a_numOfThreads; ++i)
    {
        Thread thrad(pf,a_arg);
        m_elements.push_back(thrad);
    }
}

template <typename Args>
ThreadGroup<Args>::ThreadGroup(std::vector<Args>& a_vec, void* (*pf)(void*))
{
    size_t size = a_vec.size();
    for(size_t i = 0; i < size; ++i)
    {
        Thread thrad(pf, &a_vec[i]);
        m_elements.push_back(thrad);
    }
}

template <typename Args>
void ThreadGroup<Args>::detach()
{
    size_t size = m_elements.size();
    for(size_t i = 0; i < size; ++i)
    {
        m_elements[i].detach();
    }
}

template <typename Args>
void ThreadGroup<Args>::join()
{
    size_t size = m_elements.size();
    for(size_t i = 0; i < size; ++i)
    {
        m_elements[i].join();
    }
}

template <typename Args>
Thread const& ThreadGroup<Args>::operator[](size_t a_index) const
{
    return m_elements[a_index];
}

template <typename Args>
void ThreadGroup<Args>::init(size_t a_size, std::vector<Args>& a_args, void* (*pf)(void*))
{
    m_elements.reserve(a_size);
    for(size_t i = 0; i < a_size; ++i)
    {
        Thread t(pf, &a_args[i]);
        m_elements.push_back(t);
    }
}

template <typename Args>
void ThreadGroup<Args>::init(size_t a_size, Args& a_arg, void* (*pf)(void*))
{
    m_elements.reserve(a_size);
    for(size_t i = 0; i < a_size; ++i)
    {
        Thread t(pf, &a_arg);
        m_elements.push_back(t);
    }
}










}   // namespace mt



#endif  // THREAD_HXX