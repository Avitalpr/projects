#ifndef THREAD_HPP
#define THREAD_HPP

#include <pthread.h>
#include <vector>
#include <cstddef>
#include <stdexcept>
#include <cerrno>


namespace mt
{


class Thread
{
public:
    Thread(void* (*pf)(void*) = 0, void* a_arg = 0);

    ~Thread();
    Thread(Thread const& a_source);

    void detach();
    void join();
    void* get() const;

    static void* join(pthread_t const& a_thread);
    static pthread_t self();



private:

    mutable pthread_t m_tid;
    void* m_context;
    mutable bool m_wasJoined;
    
    
};

template <typename Args>
class ThreadGroup
{
public:

    explicit ThreadGroup(Args* a_arg = 0, void* (*pf)(void*) = 0, size_t a_numOfThreads = 0);

    ThreadGroup(std::vector<Args>& a_vec, void* (*pf)(void*));



    void detach();
    void join();

    Thread const& operator[](size_t a_index) const;

    void init(size_t a_size, std::vector<Args>& a_args, void* (*pf)(void*));

    void init(size_t a_size, Args& a_arg, void* (*pf)(void*));



private:

    std::vector<Thread> m_elements;
};


}   // namespace mt

#include "./inl/thread.hxx"

#endif // THREAD_HPP