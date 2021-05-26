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
存在一个按升序排列的链表，给你这个链表的头节点 head ，请你删除链表中所有存在数字重复情况的节点，只保留原始链表中 没有重复出现 的数字。

返回同样按升序排列的结果链表。

 

示例 1：


输入：head = [1,2,3,3,4,4,5]
输出：[1,2,5]
示例 2：


输入：head = [1,1,1,2,3]
输出：[2,3]
 

提示：

链表中节点数目在范围 [0, 300] 内
-100 <= Node.val <= 100
题目数据保证链表已经按升序排列

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/remove-duplicates-from-sorted-list-ii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)


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


class Solution {///8ms 84.65% 10.8M 62.06%
public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode hair{0, head};
        for (head = &hair; head->next;)
        {
            if (!head->next->next || head->next->val != head->next->next->val) head = head->next;
            else
            {
                while (head->next->next && head->next->val == head->next->next->val) head->next = head->next->next;
                head->next = head->next->next;
            }
        }
        return hair.next;
    }
};

class SolutionV1 {///16ms 13.88% 10.8M 47.33%
public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode hair{0, NULL};
        for (ListNode * tail = &hair; head;)
        {
            if (!head->next || head->val != head->next->val)
            {
                tail = tail->next = head;
                head = head->next;
                tail->next = NULL;
            }
            else
            {
                while (head->next && head->val == head->next->val) head = head->next;
                head = head->next;
            }
        }
        return hair.next;

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
