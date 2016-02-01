#include "std.hpp"

// https://leetcode.com/problems/lru-cache/

class LRUCache
{
public:
    LRUCache(int capacity)
      : m_capacity(static_cast<size_t>(max(1, capacity)))
      , m_noRes(-1)
    {
    }

    int get(int key)
    {
        return get_value_ref(key, false);
    }

    void set(int key, int value)
    {
        get_value_ref(key, true) = value;
    }

private:
    int & get_value_ref(int key, bool allocIfNeed)
    {
        auto i = m_keymap.find(key);
        if (i != m_keymap.end())
        {
            auto const li = i->second;
            m_items.emplace_front(*li);
            m_items.erase(li);
            i->second = m_items.begin();
            return i->second->second;
        }

        if (!allocIfNeed) return m_noRes;

        if (m_items.size() < m_capacity)
        {
            m_items.emplace_front(make_pair(key, 0));
            i = m_keymap.insert(make_pair(key, m_items.begin())).first;
        }
        else
        {
            m_items.emplace_front(make_pair(key, 0));
            i = m_keymap.insert(make_pair(key, m_items.begin())).first;
            m_keymap.erase(m_items.back().first);
            m_items.pop_back();
        }
        return i->second->second;
    }

    list<pair<int, int>> m_items;
    unordered_map<int, list<pair<int, int>>::iterator> m_keymap;

    size_t const m_capacity;
    int m_noRes;
};

void test_LRUCache()
{
    LRUCache c(1);
    c.set(2,1);
    assert(1 == c.get(2));
    c.set(3,2);
    int a = c.get(2);
    int b = c.get(3);
    assert(a == -1);
    assert(b == 2);
}
