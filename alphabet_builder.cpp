#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// a < b < d
// a < c
// b < c : a < b < c

class AlphabetBuilder
{
public:
    using TString = std::string;
    using TChar = TString::value_type;

    void Add(TString s)
    {
        if (s.empty())
            return;

        if (m_prev.empty())
        {
            m_root = s[0];
            m_graph[s[0]].m_char = s[0];
            m_prev = std::move(s);
            return;
        }

        // Check lexigraphical order
        assert(m_prev < s);

        size_t const n = std::min(m_prev.length(), s.length());
        size_t i = 0;
        for (; i < n; ++i) if (s[i] != m_prev[i]) break;
        if (n == i)
        {
            // Check lexigraphical order
            assert(n == m_prev.length());
            m_prev = std::move(s);
            return;
        }

        // Since input 's' is lexigraphically sorted,
        // m_prev[i] < s[i]

        Connect(m_prev[i], s[i]);

        m_prev = std::move(s);
    }

    std::pair<TString, bool> GetAlphabet() const
    {
        TString tmp, res;
        tmp.reserve(m_graph.size());
        res.reserve(m_graph.size());
        tmp.push_back(m_root);
        bool const full = FindAlphabetRecursive(m_root, tmp, res);
        assert(std::is_sorted(res.begin(), res.end()));
        return std::make_pair(move(res), full);
    }

private:
    struct Node
    {
        TChar m_char;
        std::vector<Node*> m_greater;
    };

    Node & GetNode(TChar c)
    {
        auto const i = m_graph.find(c);
        if (i != m_graph.end())
            return i->second;
        Node & node = m_graph[c];
        node.m_char = c;
        return node;
    }

    Node const & GetNode(TChar c) const
    {
        auto const i = m_graph.find(c);
        assert(i != m_graph.end());
        return i->second;
    }

    bool IsConnected(TChar lo, TChar hi) const
    {
        std::stack<TChar> s;
        s.push(lo);
        while (!s.empty())
        {
            TChar const c = s.top();
            s.pop();
            if (c == hi)
                return true;
            auto const i = m_graph.find(c);
            if (i != m_graph.end())
                for (auto const & n : i->second.m_greater)
                    s.push(n->m_char);
        }
        return false;
    }

    void Connect(TChar lo, TChar hi)
    {
        if (IsConnected(lo, hi))
            return;

        Node & nodeLo = GetNode(lo);
        Node & nodeHi = GetNode(hi);

        nodeLo.m_greater.emplace_back(&nodeHi);
    }

    bool FindAlphabetRecursive(TChar c, TString & tmp, TString & res) const
    {
        Node const & node = GetNode(c);

        if (node.m_greater.empty())
        {
            if (res.length() < tmp.length())
                res = tmp;
            return res.length() == m_graph.size();
        }

        for (auto const & n : node.m_greater)
        {
            tmp.push_back(n->m_char);
            if (FindAlphabetRecursive(n->m_char, tmp, res))
                return true;
            tmp.pop_back();
        }

        return false;
    }

private:
    TChar m_root;
    TString m_prev;
    std::unordered_map<TChar, Node> m_graph;
};

std::set<std::string> ReadFile(const char * filepath)
{
    std::set<std::string> content;
    std::ifstream is(filepath, std::ifstream::in);
    while (!is.eof())
    {
        std::string s;
        is >> s;
        if (!s.empty())
            content.emplace(std::move(s));
    }
    return content;
}

void test_alphabet_1()
{
    AlphabetBuilder ab;
    ab.Add("AAB");
    ab.Add("ABA");
    ab.Add("ACC");
    ab.Add("BBC");
    ab.Add("CAC");

    auto res = ab.GetAlphabet();
    std::cout << "Alphabet " << res.first << " " << (res.second ? "complete" : "partial") << std::endl;
}

void test_alphabet_2(const char * const filepath)
{
    AlphabetBuilder ab;
    for (auto const & s : ReadFile(filepath))
        ab.Add(s);

    auto res = ab.GetAlphabet();
    std::cout << "Alphabet " << res.first << " " << (res.second ? "complete" : "partial") << std::endl;
}
