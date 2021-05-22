#ifndef ORDERED_MAP_H
#define ORDERED_MAP_H

#include <unordered_map>

template<typename KEY, typename VALUE, typename ORDERED_KEY>
class OrderedMap
{
public:
    std::pair<typename std::unordered_map<KEY, VALUE>::iterator, bool> insert(const std::pair<KEY, VALUE> &pair, const ORDERED_KEY &ordered_key)
    {
        std::pair<typename std::unordered_map<KEY, VALUE>::iterator, bool> it = m_unordered_map.insert(pair);
        if (true == it.second)
        {
            m_ordered_map.insert(std::pair<ORDERED_KEY, KEY>(ordered_key, pair.first));
        }
        return it;
    }

    int erase(typename std::unordered_map<KEY, VALUE>::iterator it, typename std::multimap<ORDERED_KEY, KEY>::iterator ordered_it)
    {
        m_ordered_map.erase(ordered_it);
        m_unordered_map.erase(it);
        return 0;
    }

    int erase(typename std::unordered_map<KEY, VALUE>::iterator it, const ORDERED_KEY &ordered_key)
    {
        std::pair<typename std::multimap<ORDERED_KEY, KEY>::iterator, 
            typename std::multimap<ORDERED_KEY, KEY>::iterator> range = m_ordered_map.equal_range(ordered_key);
        while (range.first != range.second && range.first->second != it->first)
        {
            ++range.first;
        }
        if (range.first == range.second)
        {
            m_unordered_map.erase(it);
            return -1;
        }
        m_ordered_map.erase(range.first);
        m_unordered_map.erase(it);
        return 0;
    }

    void clear()
    {
        m_ordered_map.clear();
        m_unordered_map.clear();
    }
    bool empty()
    {
        return m_unordered_map.empty();
    }
    unsigned size()
    {
        return m_unordered_map.size();
    }
    typename std::unordered_map<KEY, VALUE>::iterator find(const KEY &key)
    {
        return m_unordered_map.find(key);
    }
    typename std::unordered_map<KEY, VALUE>::iterator begin()
    {
        return m_unordered_map.begin();
    }
    typename std::unordered_map<KEY, VALUE>::iterator end()
    {
        return m_unordered_map.end();
    }
    void erase(typename std::unordered_map<KEY, VALUE>::iterator it)
    {
        m_unordered_map.erase(it);
    }

    typename std::multimap<ORDERED_KEY, KEY>::iterator get_first_key()
    {
        return m_ordered_map.begin();
    }
    typename std::multimap<ORDERED_KEY, KEY>::iterator get_last_key()
    {
        return m_ordered_map.end();
    }
    void erase_ordered_iterator(typename std::multimap<ORDERED_KEY, KEY>::iterator it)
    {
        m_ordered_map.erase(it);
    }
    void update_order(typename std::multimap<ORDERED_KEY, KEY>::iterator it, const ORDERED_KEY &ordered_key)
    {
        m_ordered_map.insert(std::pair<ORDERED_KEY, KEY>(ordered_key, it->second));
        m_ordered_map.erase(it);
    }
    typename std::multimap<ORDERED_KEY, KEY>::iterator find_ordered_iter_by_key(const KEY &key)
    {
        typename std::multimap<ORDERED_KEY, KEY>::iterator it = m_ordered_map.begin();
        while (it != m_ordered_map.end() && it->second != key)
        {
            ++it;
        }
        return it;
    }

protected:
    std::unordered_map<KEY, VALUE> m_unordered_map;
    std::multimap<ORDERED_KEY, KEY> m_ordered_map;
};

#endif
