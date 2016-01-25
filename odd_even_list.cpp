#include "std.hpp"

// https://leetcode.com/problems/odd-even-linked-list/

struct ListNode
{
    ListNode * next;
    int val;
    ListNode(int v) : next(nullptr), val(v) {}
};

class Solution {
public:
    ListNode* oddEvenList(ListNode* head) {
        ListNode oddRoot(1), evenRoot(2);
        ListNode* odd = &oddRoot;
        ListNode* even = &evenRoot;
        bool isOdd = true;
        while (head != nullptr)
        {
            if (isOdd)
            {
                odd->next = head;
                odd = head;
            }
            else
            {
                even->next = head;
                even = head;
            }
            isOdd = !isOdd;
            head = head->next;
        }
        odd->next = evenRoot.next;
        even->next = nullptr;
        return oddRoot.next;
    }
};

static ListNode * MakeList(initializer_list<int> const & il)
{
    ListNode t(0);
    ListNode * p = &t;
    for (int val : il)
    {
        ListNode * n = new ListNode(val);
        p->next = n;
        p = n;
    }
    return t.next;
}

void test_oddEvenList()
{
    ListNode * p = MakeList({1,2,3,4,5,6,7,8});
    p = Solution().oddEvenList(p);
}
