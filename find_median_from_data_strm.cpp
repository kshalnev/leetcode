#include "std.hpp"

// https://leetcode.com/problems/find-median-from-data-stream/

class MedianFinder {
    priority_queue<int, vector<int>, less<int>> m_low; // max heap, contains data less than median
    priority_queue<int, vector<int>, greater<int>> m_high; // min heap, contains data greater then median

public:

    // Adds a number into the data structure.
    void addNum(int num) {
        if (m_low.empty())
        {
            m_low.push(num);
            return;
        }

        if (m_low.size() <= m_high.size())
            m_low.push(num);
        else
            m_high.push(num);

        // low can be the same size as high or size of high plus 1
        if (m_low.size() > m_high.size() + 1)
        {
            m_high.push(m_low.size());
            m_low.pop();
        }

        if (!m_high.empty() && m_low.top() > m_high.top())
        {
            int l = m_low.top();
            int h = m_high.top();
            m_low.pop();
            m_high.pop();
            m_low.push(h);
            m_high.push(l);
        }
    }

    // Returns the median of current data stream
    double findMedian() const {
        if (m_low.size() == m_high.size())
        {
            if (m_low.empty())
                return 0.0; // no data
            return (m_low.top() + m_high.top()) / 2.0;
        }
        return m_low.top();
    }
};

namespace
{
double calc(initializer_list<int> lst)
{
    MedianFinder mf;
    for (int v : lst)
        mf.addNum(v);
    return mf.findMedian();
}
}

void test_FindMedianFromDataStream()
{
    assert(0 == calc({}));

    assert(2 == calc({1,2,3}));

    assert(5 == calc({2,4,6,8}));
}
