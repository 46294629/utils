//该类作为需要单例的友元类

#ifndef SINGLETON_H
#define SINGLETON_H

#include <stdio.h>

template<typename T>
class SingletonClass
{
public:
    static T *get_instance()
    {
        if (NULL == m_instance)
        {
            m_instance = new T();
        }
        return m_instance;
    }
    ~SingletonClass()
    {
        delete m_instance;
        m_instance = NULL;
    }

private:
    static T *m_instance;
};

template <typename T> 
T *SingletonClass<T>::m_instance = NULL;

#endif
