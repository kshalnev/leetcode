#include "std.hpp"

// https://leetcode.com/problems/reconstruct-itinerary/

class Solution {
public:
    class Graph
    {
    public:
      void init(vector<pair<string, string>> const & tickets)
      {
        for (auto const & ft : tickets)
          add(ft.first, ft.second);
      }
      void add(string const & from, string const & to)
      {
        auto i = m_g.find(from);
        if (i == m_g.end())
          i = m_g.insert(make_pair(from, set<string>())).first;
        if (m_g.find(to) == m_g.end())
          m_g.insert(make_pair(to, set<string>()));
        i->second.insert(to);
      }
      void remove(string const & from, string const & to)
      {
        auto i = m_g.find(from);
        i->second.erase(to);
      }
      size_t size() const { return m_g.size(); }
      set<string> adj(string const & v) const
      {
        assert(has(v));
        return m_g.find(v)->second;
      }
      bool has(string const & v) const
      {
        return m_g.find(v) != m_g.end();
      }
      size_t edges() const
      {
        size_t n = 0;
        for (auto const & adj : m_g)
            n += adj.second.size();
        return n;
      }
    private:
      unordered_map<string, set<string>> m_g;
    };

    bool recur(Graph & g,
               string const & from,
               vector<string> & tmp,
               vector<string> & res)
    {
      tmp.emplace_back(from);

      set<string> adj = g.adj(from);

      if (adj.empty())
      {
        if (g.edges() == 0)
        {
          res = move(tmp);
          return true;
        }

        tmp.pop_back();
        return false;
      }

      for (auto const & to : adj)
      {
        g.remove(from, to);
        if (recur(g, to, tmp, res))
          return true;
        g.add(from, to);
      }

      tmp.pop_back();
      return false;
    }

    vector<string> findItinerary(vector<pair<string, string>> const & tickets, string const & first)
    {
      Graph g;
      g.init(tickets);
      if (!g.has(first)) return vector<string>();

      vector<string> tmp, res;
      recur(g, first, tmp, res);
      return res;
    }

    vector<string> findItinerary(vector<pair<string, string>> tickets)
    {
        return findItinerary(tickets, "JFK");
    }
};

void test_findItinerary()
{
    vector<pair<string, string>> tickets1({{"MUC","LHR"}, {"JFK","MUC"}, {"SFO","SJC"}, {"LHR","SFO"}});
    vector<string> path1 = Solution().findItinerary(tickets1);
    assert(path1 == vector<string>({"JFK","MUC","LHR","SFO","SJC"}));

    vector<pair<string, string>> tickets2({{"JFK","SFO"},{"JFK","ATL"},{"SFO","ATL"},{"ATL","JFK"},{"ATL","SFO"}});
    vector<string> path2 = Solution().findItinerary(tickets2);
    assert(path2 == vector<string>({"JFK","ATL","JFK","SFO","ATL","SFO"}));
}
