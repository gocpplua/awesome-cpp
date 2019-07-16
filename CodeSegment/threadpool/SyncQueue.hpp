//===============================================================
//Summary:
//          SyncQueue 类， 
//FileName:
//          SyncQueue.hpp
//Remarks:
//          ...
//Date:
//          2019/7/16
//Author:   chenqi
//          chenqi(chenqi@comfun.com)
//===============================================================
#pragma once
#include<iostream>
#include<list>
#include<mutex>
#include<condition_variable>
extern std::recursive_mutex g_coutmutex;

template<typename T>

class SyncQueue
{
public:
    SyncQueue(int maxSize) :m_maxSize(maxSize), m_needStop(false) {};
    ~SyncQueue() {};
    void Put(const T& x)
    {
        Add(x);
    }
    void Put(T&& x)
    {
        Add(std::forward<T>(x)); //为了保持x是原来的类型，使用完美转发
    }

    void Take(std::list<T>& list)
    {
        std::unique_lock<std::mutex> locker(m_mutex);
        m_notEmpty.wait(locker, [this] {return m_needStop || NotEmpty(); }); //lambda表达式省略了参数
        if (m_needStop)
        {
            return;
        }
        list = std::move(m_queue);
        m_notFull.notify_one(); // 唤醒一个正在等待的线程
    }
    void Take(T& t)
    {
        std::unique_lock<std::mutex> locker(m_mutex);
        m_notEmpty.wait(locker, [this] {return m_needStop || NotEmpty(); }); //lambda表达式省略了参数
        if (m_needStop)
        {
            return;
        }
        t = m_queue.front();
        m_queue.pop_front();
        m_notFull.notify_one(); // 唤醒一个正在等待的线程
    }
    void Stop()
    {
        {
            std::lock_guard<std::mutex> locker(m_mutex);
            m_needStop = true;
        }
        m_notFull.notify_all();
        m_notEmpty.notify_all();
    }
    bool Empty()
    {
        std::lock_guard<std::mutex> locker(m_mutex);
        return m_queue.empty();
    }
    bool Full()
    {
        std::lock_guard<std::mutex> locker(m_mutex);
        return m_queue.size() == m_maxSize;

    }
    size_t Size()
    {
        std::lock_guard<std::mutex> locker(m_mutex);
        return m_queue.size();

    }
    int Count()
    {
        return m_queue.size();
    }
private:
    bool NotFull() const
    {
        bool full = m_queue.size() >= m_maxSize;
        if (full)
        {
            std::lock_guard<std::recursive_mutex> locker(g_coutmutex);
            std::cout << "缓冲区满了,需要等待...线程ID:" << std::this_thread::get_id() << std::endl;
        }
        return !full;
    }
    bool NotEmpty() const
    {
        bool empty = m_queue.empty();
        if (empty)
        {
            std::lock_guard<std::recursive_mutex> locker(g_coutmutex);
            std::cout << "缓冲区空了,需要等待...线程ID:" << std::this_thread::get_id() << std::endl;
        }
        return !empty;
    }
    template<typename F>
    void Add(F&& x)
    {
        std::unique_lock<std::mutex> locker(m_mutex);
        m_notFull.wait(locker, [this] {return m_needStop || NotFull(); }); //lambda表达式省略了参数
        if (m_needStop)
        {
            return;
        }
        m_queue.push_back(std::forward<F>(x));
        m_notEmpty.notify_one();
    }
private:

    std::list<T> m_queue;
    std::mutex m_mutex;
    std::condition_variable m_notFull;
    std::condition_variable m_notEmpty;
    int m_maxSize;
    bool m_needStop;
};

