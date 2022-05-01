#ifndef QUEUE_HXX
#define QUEUE_HXX
#include <cstddef>
#include <cassert>

namespace cpp
{

template <typename T>
inline Queue<T>::Queue(size_t a_capacity)
: m_array(new T[a_capacity])
, m_capacity(a_capacity)
, m_tos(0)
, m_head(0)
, m_tail(0)
{   
    axioms();
}


template <typename T>
inline Queue<T>::Queue(Queue<T> const& a_queue)
: m_array(new T[a_queue.m_capacity])
, m_capacity(a_queue.m_capacity)
, m_tos(a_queue.m_tos)
, m_head(a_queue.m_head)
, m_tail(a_queue.m_tail)
{
    for(size_t i = 0; i < m_capacity; ++i)
    {
        m_array[i] = a_queue.m_array[i];
    }

    axioms();
}

template <typename T>
inline Queue<T>& Queue<T>::operator=(Queue<T> const& a_source)
{
    if(this != &a_source)
    {
        m_tos = a_source.m_tos;
        m_head = a_source.m_head;
        m_tail = a_source.m_tail;
        size_t counter = 0;
        if(capacity() != a_source.capacity())
        {
            m_capacity = a_source. m_capacity;
            T *data = new T[m_capacity];
            for(size_t i = m_head; counter++ < m_tos; i = (i + 1) % m_capacity)
            {
                data[i] = a_source.m_array[i];
            }
            swap(m_array, data);
            delete [] data;
        }
        else
        {
            for(size_t i = m_head; counter++ < m_tos; i = (i + 1) % m_capacity)
            {
                m_array[i] = a_source.m_array[i];
            }
        }
        axioms();
    }
    return *this;
}



template <typename T>
inline void Queue<T>::enqueue(T a_item)
{
    assert(!isFull());
    m_array[m_tail] = a_item;
    ++m_tos;
    m_tail = (m_tail + 1) % m_capacity;
    axioms();
}

template <typename T>
inline Queue<T>::~Queue()
{
    delete [] m_array;
}

template <typename T>
inline T Queue<T>::dequeue()
{
    assert(!isEmpty());
    T result = m_array[m_head];
    --m_tos;
    m_head = (m_head + 1) % m_capacity;
    axioms();
    return result;
}

template <typename T>
inline size_t Queue<T>::size() const
{
    return m_tos;
}

template <typename T>
inline size_t Queue<T>::capacity() const
{
    return m_capacity;
}

template <typename T>
inline bool Queue<T>::isEmpty() const
{
    return m_tos == 0;
}

template <typename T>
inline bool Queue<T>::isFull() const
{
    return m_tos == m_capacity;
}

template <typename T>
inline void Queue<T>::clear()
{
    m_head = 0;
    m_tail = 0;
    m_tos = 0;
    axioms();
}

template <typename T>
inline void Queue<T>::swap(T *&x, T*& y)
{
    T *temp = x;
    x = y;
    y = temp;
    axioms();
}

template <typename T>
inline void Queue<T>::axioms() const
{
    assert(m_capacity > 0);
    assert(m_tos <= m_capacity);
    assert(m_head < m_capacity);
    assert(m_tail < m_capacity);
}

}

namespace animals
{

inline Cat::Cat(size_t age, char gender)
: m_age(age)
, m_gender(gender)
{

}

inline size_t Cat::age() const
{
    return m_age;
}
inline char Cat::gender() const
{
    return m_gender;
}

}  // namespace cpp


#endif // QUEUE.HXX