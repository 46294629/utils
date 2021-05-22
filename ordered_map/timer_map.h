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
