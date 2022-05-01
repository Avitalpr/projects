#ifndef QUEUE_HPP
#define QUEUE_HPP
#include <cstddef>
#define SIZE 64

namespace cpp
{

template <typename T>
class Queue
{
public:
    
    explicit Queue(size_t const a_capacity = SIZE);

    Queue(Queue<T> const& a_queue);
    Queue<T>& operator=(Queue<T> const& a_source);
    ~Queue();

  
    void enqueue(T a_item);
    T dequeue();

    size_t size() const;
    size_t capacity() const;
    bool isEmpty() const;
    bool isFull() const;
    void clear();

private:

    void swap(T *&x, T*& y);

    void axioms() const;
    
    // data member
private:

    T *m_array;
    size_t m_capacity;
    size_t m_tos;
    size_t m_head;
    size_t m_tail;
    
};


}

namespace animals
{


class Cat
{
public:
    Cat(size_t age = 0, char gender = '0');

    size_t age() const;
    char gender() const;

private:

    size_t m_age;
    char m_gender;

};


} // namespace cpp

#include "./inl/queue.hxx"

#endif // QUEUE_HPP