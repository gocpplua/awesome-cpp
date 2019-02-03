#pragma once
#include<list>
#include<thread>
#include<atomic>
#include "SyncQueue.hpp"

const int MaxTaskCount = 2;

class ThreadPool
{
public:
    using Task = std::function<void()>;
         
    ThreadPool(int numThreads = std::thread::hardware_concurrency()):m_queue(MaxTaskCount)
    {
        Start(numThreads);
    }
    ~ThreadPool() 
    {
        Stop();
    }
    void Stop()
    {
        std::call_once(m_flag, [this] {StopThreadGroup(); });
    }

    void AddTask(Task&& task)
    {
        m_queue.Put(std::forward<Task>(task));
    }
    void AddTask(const Task& task)
    {
        m_queue.Put(task);
    }

private:
    void Start(int numThreads)
    {
        m_running = true;
        for (int i = 0; i < numThreads; i++)
        {
            m_threadgroup.push_back(std::make_shared<std::thread>(&ThreadPool::RunInThread, this));
        }
    }
    void RunInThread()
    {
        {
            std::lock_guard<std::recursive_mutex> locker(g_coutmutex);
            std::cout << "[start]RunInThread线程ID:" << std::this_thread::get_id() << std::endl;
        }
        int i = 0;
        while (m_running)
        {
            {
                std::lock_guard<std::recursive_mutex> locker(g_coutmutex);
                std::cout << "[start]RunInThread线程ID:" << std::this_thread::get_id() << std::endl;
            }
            std::list<Task> list;
            m_queue.Take(list);
            for (auto& task : list)
            {
                if (!m_running)
                {
                    std::cout << "[end11]RunInThread线程ID:" << std::this_thread::get_id() << std::endl;
                    return;
                }
                i++;
                task();
            }
        }
        {
            std::lock_guard<std::recursive_mutex> locker(g_coutmutex);
            std::cout << "i = " << i << std::endl;
            std::cout << "[end]RunInThread线程ID:" << std::this_thread::get_id() << std::endl;
        }
    }
    void StopThreadGroup()
    {
        m_queue.Stop();
        m_running = false;
        for (auto& thread : m_threadgroup)
        {
            if (thread)
            {
                thread->join();
            }
        }
        m_threadgroup.clear();
    }

private:
    std::list<std::shared_ptr<std::thread>> m_threadgroup;
    SyncQueue<Task> m_queue;
    std::atomic_bool m_running;
    std::once_flag m_flag;

};