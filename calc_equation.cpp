#include "std.hpp"

// https://leetcode.com/problems/evaluate-division/

class Solution {
public:
    using TGraph = multimap<string, pair<string, double>>;

    static double recur(const TGraph& g,
                        const string& prev,
                        const string& node,
                        const string& target,
                        const double& value)
    {
        if (node == target) return value;

        const auto r = g.equal_range(node);
        for (auto i = r.first; i != r.second; ++i)
        {
            const string& next_node = i->second.first;
            if (next_node == node || next_node == prev) continue; // skip loop
            const double& k = i->second.second;
            const double res = recur(g, node, next_node, target, value * k);
            if (res != -1.0)
                return res;
        }

        return -1.0;
    }

    vector<double> calcEquation(const vector<pair<string, string>>& equations,
                                const vector<double>& values,
                                const vector<pair<string, string>>& queries)
    {
        if (equations.size() != values.size()) {
            // bad input
            return {};
        }

        if (equations.empty()) {
            // empty input, answer does not exist
            return vector<double>(queries.size(), -1.0);
        }

        TGraph g;

        for (size_t i = 0; i < equations.size(); ++i) {
            // a / b = k
            const string& a = equations[i].first;
            const string& b = equations[i].second;
            const double& k = values[i];
            g.insert(make_pair(a, make_pair(b, k)));
            g.insert(make_pair(b, make_pair(a, 1.0 / k)));
        }

        vector<double> res;
        res.reserve(queries.size());

        for (const auto& query : queries) {
            const auto i1 = g.find(query.first);
            const auto i2 = g.find(query.second);
            if (i1 == g.end() || i2 == g.end()) {
                res.emplace_back(-1.0);
                continue;
            }
            res.emplace_back(recur(g, query.first, query.first, query.second, 1.0));
        }

        return res;
    }
};

void test_calcEquation()
{
    // a/b = 2
    // b/c = 3
    // a/c = (a/b)*(b/c) = 6
    vector<pair<string,string>> equations = {{"a", "b"}, {"b", "c"}};
    vector<double> values = {2.0, 3.0};
    vector<pair<string,string>> queries = {{"a", "c"}};
    auto res = Solution().calcEquation(equations, values, queries);
}
