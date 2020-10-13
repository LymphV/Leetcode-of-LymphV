#include <LymphV>
/**
给你一个链表数组，每个链表都已经按升序排列。

请你将所有链表合并到一个升序链表中，返回合并后的链表。

 

示例 1：

输入：lists = [[1,4,5],[1,3,4],[2,6]]
输出：[1,1,2,3,4,4,5,6]
解释：链表数组如下：
[
  1->4->5,
  1->3->4,
  2->6
]
将它们合并到一个有序链表中得到。
1->1->2->3->4->4->5->6
示例 2：

输入：lists = []
输出：[]
示例 3：

输入：lists = [[]]
输出：[]
 

提示：

k == lists.length
0 <= k <= 10^4
0 <= lists[i].length <= 500
-10^4 <= lists[i][j] <= 10^4
lists[i] 按 升序 排列
lists[i].length 的总和不超过 10^4

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/merge-k-sorted-lists
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)
///堆优化
class Solution {///44ms 65.41% 13.4M 21.08%
    using pii = pair<int,int>;
public:
    ListNode* mergeKLists(vector<ListNode*>& lists)
    {
        int n = lists.size();
        if (!n) return NULL;
        if (n == 1) return lists[0];

        priority_queue<pii> pq;
        FOR(i,n) if (lists[i]) pq.push(pii(-lists[i]->val, i));

        ListNode * rst = new ListNode{0, NULL};
        ListNode * now = rst;

        while (!pq.empty())
        {
            auto [v, p] = pq.top(); pq.pop();
            now = now->next = lists[p];
            ;
            if(!!(lists[p] = lists[p]->next)) pq.push(pii(-lists[p]->val, p));
        }
        return rst->next;
    }
};

///清洗list剪枝
class SolutionV3 {///300ms 14.00% 16.7M 15.43%
    void clean (vector<ListNode*>& lists)
    {
        for (int i = lists.size() - 1; 0 <= i; --i)
            if (!lists[i]) lists.erase(begin(lists) + i);
    }
public:
    ListNode* mergeKLists(vector<ListNode*>& lists, bool start = 1) {
        if (start) clean(lists);

        int n = lists.size();
        if (!n) return NULL;
        if (n == 1) return lists[0];

        int p = -1;
        int minVal = 0;
        FOR(i,n)
        {
            auto & node = lists[i];
            if (!node) continue;
            if (p < 0 || node->val < minVal)
            {
                p = i;
                minVal = node->val;
            }
        }
        if (p < 0) return NULL;
        auto rst = lists[p];
        lists[p] = lists[p]->next;
        if (!lists[p]) lists.erase(begin(lists) + p);
        rst->next = mergeKLists(lists, 0);
        return rst;
    }
};

///栈解递归
class SolutionV2 {///576ms 7.36% 13.1M 22.74%
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        int n = lists.size();
        if (!n) return NULL;

        ListNode * rst = NULL;
        ListNode * now = NULL;
        for (;;)
        {
            int p = -1;
            int minVal = 0;
            FOR(i,n)
            {
                auto & node = lists[i];
                if (!node) continue;
                if (p < 0 || node->val < minVal)
                {
                    p = i;
                    minVal = node->val;
                }
            }
            if (p < 0) break;

            if (now)
            {
                now->next = lists[p];
                lists[p] = lists[p]->next;
                now = now->next;
            }
            else
            {
                rst = now = lists[p];
                lists[p] = lists[p]->next;
            }
        }
        return rst;
    }
};

///递归
class SolutionV1 {///596ms 7.20% 13.5M 19.78%
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        int n = lists.size();
        if (!n) return NULL;

        int p = -1;
        int minVal = 0;
        FOR(i,n)
        {
            auto & node = lists[i];
            if (!node) continue;
            if (p < 0 || node->val < minVal)
            {
                p = i;
                minVal = node->val;
            }
        }
        if (p < 0) return NULL;
        auto rst = lists[p];
        lists[p] = lists[p]->next;
        rst->next = mergeKLists(lists);
        return rst;
    }
};

int main()
{
    vector<> xs{};
    for (auto x : xs)
        print(x, Solution().(x));

    return 0;
}
