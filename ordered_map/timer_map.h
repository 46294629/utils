#ifndef TIMER_MAP_H
#define TIMER_MAP_H

#include "ordered_map.h"

template<typename KEY, typename VALUE, typename ORDERED_KEY>
class TimerMap : public OrderedMap< KEY, VALUE, ORDERED_KEY>
{
public:
    TimerMap()
    {
        m_expire_callback = NULL;
    }
    ~TimerMap()
    {
        m_expire_callback = NULL;
    }
    void RegisterCallback(int (*expire_callback) (void *this_pointer, KEY &unordered_key, ORDERED_KEY &new_key))
    {
        m_expire_callback = expire_callback;
    }
    /*
    c++编译模版类时要分为两阶段查找，第一阶段检查与模板参数无关的变量/函数，找不到则报错；第二阶段在实例化模板时，再对依赖模板参数的变量/函数进行检查。
    如果子类也是模板类，第一阶段检查独立的变量/函数时，如果调用父类变量/函数不显式加this，会被认为是独立变量/函数，但此时还未示例化父类，在类中找不到定义，故报错
    */
    void CheckExpire(void *this_pointer, const ORDERED_KEY &expire_key)
    {
        if (NULL == m_expire_callback)
        {
            return;
        }
        typename std::multimap<ORDERED_KEY, KEY>::iterator ordered_iter;
        ORDERED_KEY new_key;
        for (ordered_iter = this->m_ordered_map.begin(); ordered_iter != this->m_ordered_map.end();)
        {
            if (expire_key < ordered_iter->first)
            {
                break;
            }
            if (0 == m_expire_callback(this_pointer, ordered_iter->second, new_key))
            {
                this->update_order(ordered_iter++, new_key);
            }
            else
            {
                this->m_ordered_map.erase(ordered_iter++);
            }
        }
    }
private:
    int (*m_expire_callback) (void *this_pointer, KEY &unordered_key, ORDERED_KEY &new_key);
};

#endif
