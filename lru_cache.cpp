#include "std.hpp"

// https://leetcode.com/problems/lru-cache/

/*
class MinHeap
{
public:
  MinHeap(size_t capacity)
  : m_items(capacity)
  , m_count()
  {}

  using TKeyValue = pair<int, int>;

  size_t size() const
  {
    assert(m_count <= m_items.size());
    return m_count;
  }

  bool empty() const
  {
    assert(m_count <= m_items.size());
    return m_count == 0;
  }

  TKeyValue const & top() const
  {
    assert(m_count <= m_items.size());
    assert(m_count > 0);
    retun m_items[0];
  }

  void pop()
  {
    assert(m_count <= m_items.size());
    assert(m_count > 0);
    m_items[0] = m_items[m_count - 1];
    --m_count;
    heapify(0);
  }

  void insert(TKeyValue const & item)
  {
    assert(m_count < m_items.size());
    int i = m_count;
    m_items[m_count] = item;
    ++m_count;
    while (i > 0)
    {
      int p = (i - 1) / 2;
      if (m_items[p].second < m_items[i].second) break;
      swap(m_items[p], m_items[i]);
      i = p;
    }
  }

private:
  void heapify(int n)
  {
    int const l = 2 * n + 1;
    int const r = 2 * n + 2;
    int min = n;
    if (l < m_count && m_items[l].second < m_items[n].second) min = l;
    if (r < m_count && m_items[r].second < m_items[n].second) min = r;
    if (min == l)
    {
      swap(m_item[n], m_item[l]);
      heapify(l);
    }
    else if (min == r)
    {
      swap(m_item[n], m_item[r]);
      heapify(r);
    }
  }

  vector<TKeyValue> m_items;
  size_t m_count;
};
*/

class LRUCache
{
public:
    LRUCache(int capacity)
      : m_valueAndTick(max(1, capacity))
      , m_count(0)
      , m_key2index(max(1, capacity))
      , m_tick(0)
    {
    }

    int get(int key)
    {
        const int i = get_key_index(key);
        if (i == -1) return -1;
        update_key_usage(key, i);
        return m_valueAndTick[i].first;
    }

    void set(int key, int value)
    {
        int i = get_key_index(key);
        if (i == -1)
        {
          if (m_count == m_valueAndTick.size())
          {
            int oldKey = find_least_used_key();
            i = get_key_index(oldKey);
            m_key2index.erase(oldKey);
            m_key2index[key] = i;
          }
          else
          {
            i = m_count;
            m_key2index[key] = i;
            ++m_count;
          }
        }
        m_valueAndTick[i].first = value;
        update_key_usage(key, i);
    }

private:
  int get_tick() { return ++m_tick; }

  int get_key_index(int key) const
  {
    auto const itr = m_key2index.find(key);
    if (itr == m_key2index.end()) return -1;
    return itr->second;
  }

  void update_key_usage(int key, int i)
  {
    m_tick2key.erase(m_valueAndTick[i].second);
    m_valueAndTick[i].second = m_tick2key.insert(make_pair(get_tick(), key)).first->first;
  }

  int find_least_used_key() const
  {
    return m_tick2key.begin()->second;
  }

  using TTick2KeyMap = map<int, int>;

  vector<pair<int, int>> m_valueAndTick;
  size_t m_count;

  unordered_map<int, int> m_key2index;

  TTick2KeyMap m_tick2key;
  unsigned int m_tick;
};

void test_LRUCache()
{
    LRUCache c(1);
    c.set(2,1);
    assert(1 == c.get(2));
    c.set(3,2);
    int a = c.get(2);
    int b = c.get(3);
}
