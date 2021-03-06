#if defined(LocalLymphV)
#include "../../leetcode.h"
#include <LymphV>
#else
#define print(...) 0
#endif

#if !defined(LocalLymphV) || !defined(DebugLymphV)
#define debug(x) 0
#endif
/**
给定一个单链表，把所有的奇数节点和偶数节点分别排在一起。请注意，这里的奇数节点和偶数节点指的是节点编号的奇偶性，而不是节点的值的奇偶性。

请尝试使用原地算法完成。你的算法的空间复杂度应为 O(1)，时间复杂度应为 O(nodes)，nodes 为节点总数。

示例 1:

输入: 1->2->3->4->5->NULL
输出: 1->3->5->2->4->NULL
示例 2:

输入: 2->1->3->5->6->4->7->NULL
输出: 2->3->6->7->1->5->4->NULL
说明:

应当保持奇数节点和偶数节点的相对顺序。
链表的第一个节点视为奇数节点，第二个节点视为偶数节点，以此类推。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/odd-even-linked-list
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
class Solution {///20ms 44.43% 10.7M 5.58%
public:
    ListNode* oddEvenList(ListNode* head) {
        ListNode hair[2];
        ListNode * tail[2] {&hair[0], &hair[1]};
        for (int i = 0; head;head = head->next, ++i)
            tail[i & 1] = tail[i & 1]->next = head;
        tail[1]->next = 0, tail[0]->next = hair[1].next;
        return hair[0].next;
    }
};


class SolutionV1 {///16ms 76.88% 10.8M 5.24%
public:
    ListNode* oddEvenList(ListNode* head) {
        ListNode hair[2];
        ListNode * tail[2] {&hair[0], &hair[1]};
        for (int i = 0; head;head = head->next, ++i)
        {
            int j = i & 1;
            tail[j]->next = head;
            tail[j] = head;
        }
        tail[1]->next = 0;
        tail[0]->next = hair[1].next;
        return hair[0].next;
    }
};


#if defined(LocalLymphV)
int main()
{
    vector<> xs{};
    for (auto x : xs)
        print(x), print(Solution().(x)), print("===");
    return 0;
}
#endif
