#ifndef LRU_CACHE_H
#define LRU_CACHE_H

#include <list>
#include <unordered_map>
#include <new>

#define MAX_ELIMILATE_KEY_ONE_TIME (50)

template<typename Key, typename Value>
class LRUCache
{
public:
    LRUCache() {}
    virtual ~LRUCache() 
    {
        hash_map.clear();
        lru_list.clear();
    }
    
    inline bool check_key_exist(const Key &key)
    {
        return !(hash_map.end() == hash_map.find(key));
    }

    bool get_value(const Key &key, Value &value, void *check_update = NULL)
    {
        typename std::unordered_map<Key, typename std::list<std::pair<Key,Value> >::iterator>::iterator hash_it = hash_map.find(key);
        if (hash_map.end() == hash_it)
        {
            return false;
        }
        value = hash_it->second->second;
        if (check_lru_should_update(value, check_update))
        {
            lru_list.erase(hash_it->second);
            lru_list.push_front(std::pair<Key, Value>(key, value));
            hash_it->second = lru_list.begin();
        }
        return true;
    }

    bool add_key(const Key &key, const Value &value)
    {
        if (check_key_exist(key))
        {
            return true;
        }
        uint32 elimilate_num = 1;
        while (elimilate_num)
        {
            try
            {
                lru_list.push_front(std::pair<Key, Value>(key, value));
                hash_map[key] = lru_list.begin();
                return true;
            }
            catch (std::bad_alloc& ex)
            {
                if (key == lru_list.front().first)
                {
                    lru_list.pop_front();
                }
                elimilate_num = 0;
                elimilate_key(MAX_ELIMILATE_KEY_ONE_TIME, elimilate_num);
            }
        }
        return false;
    }

    bool modify_value(const Key &key, Value &value, void* check_update = NULL)
    {
        typename std::unordered_map<Key, typename std::list<std::pair<Key,Value> >::iterator>::iterator hash_it = hash_map.find(key);
        if (hash_map.end() == hash_it)
        {
            return false;
        }
        if (check_lru_should_update(value, check_update))
        {
            lru_list.erase(hash_it->second);
            lru_list.push_front(std::pair<Key, Value>(key, value));
            hash_it->second = lru_list.begin();
        }
        else
        {
            hash_it->second->second = value;
        }
        return true;
    }

    void del_key(const Key &key)
    {
        typename std::unordered_map<Key, typename std::list<std::pair<Key,Value> >::iterator>::iterator hash_it = hash_map.find(key);
        hash_it = hash_map.find(key);
        if (hash_map.end() == hash_it)
        {
            return;
        }
        delete hash_it->second->second;
        hash_it->second->second = NULL;
        lru_list.erase(hash_it->second);
        hash_map.erase(hash_it);
    }

    void elimilate_key(const unsigned &max_elimilate_num, unsigned &elimilate_num, void *check_update = NULL)
    {
        if (lru_list.empty())
        {
            return;
        }
        elimilate_num = 0;
        typename std::list<std::pair<Key, Value> >::iterator lru_it = lru_list.end();
        --lru_it;
        while (elimilate_num < max_elimilate_num && lru_list.begin() != lru_it)
        {
            if (check_value_can_elimilate(lru_it->second, check_update))
            {
                delete lru_it->second;
                lru_it->second = NULL;
                hash_map.erase(lru_it->first);
                lru_list.erase(lru_it--);
                ++elimilate_num;
            }
            else
            {
                --lru_it;
            }
        }
        if (elimilate_num < max_elimilate_num && lru_list.begin() == lru_it && check_value_can_elimilate(lru_it->second, check_update))
        {
            delete lru_it->second;
            lru_it->second = NULL;
            hash_map.erase(lru_it->first);
            lru_list.erase(lru_it);
            ++elimilate_num;
        }
    }
    //check_update can be time to set last update time
    virtual bool check_lru_should_update(Value &value, void* check_update)
    {
        return true;
    }

    virtual bool check_value_can_elimilate(Value &value, void* check_update)
    {
        
        return true;
    }

    virtual void deep_clear()
    {
        return;
    }

protected:

    std::unordered_map<Key, typename std::list<std::pair<Key, Value> >::iterator> hash_map;
    std::list<std::pair<Key, Value> >lru_list;
};
#endif
