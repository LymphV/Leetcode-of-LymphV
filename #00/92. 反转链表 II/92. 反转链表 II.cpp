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
给你单链表的头指针 head 和两个整数 left 和 right ，其中 left <= right 。请你反转从位置 left 到位置 right 的链表节点，返回 反转后的链表 。
 

示例 1：


输入：head = [1,2,3,4,5], left = 2, right = 4
输出：[1,4,3,2,5]
示例 2：

输入：head = [5], left = 1, right = 1
输出：[5]
 

提示：

链表中节点数目为 n
1 <= n <= 500
-500 <= Node.val <= 500
1 <= left <= right <= n
 

进阶： 你可以使用一趟扫描完成反转吗？

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/reverse-linked-list-ii
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

class Solution {///0ms 100.00% 7.3M 26.95%
public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        if (left == right) return head;
        ListNode hair{0, head};
        ListNode * a = &hair;
        ffor(i,1,left) a = a->next;

        ListNode b{0,NULL};
        ListNode * d = a -> next;
        ffor(i,left,right+1)
        {
            auto c = b.next;
            b.next = a -> next;
            a -> next = a -> next ->next;
            b.next -> next = c;
        }

        d -> next = a -> next;
        a -> next = b.next;
        return hair.next;
    }
};

class SolutionV1 {///8ms 51.36% 7.2M 61.29%
public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        if (left == right) return head;
        ListNode hair{0, head};
        ListNode * a = &hair;
        ffor(i,1,left) a = a->next;
        ListNode * b = a -> next;
        ffor(i,left,right) b = b->next;
        while (a -> next != b)
        {
            auto c = b -> next;
            b -> next = a -> next;
            a -> next = a -> next ->next;
            b -> next -> next = c;
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
