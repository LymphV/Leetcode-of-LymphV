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
对链表进行插入排序。


插入排序的动画演示如上。从第一个元素开始，该链表可以被认为已经部分排序（用黑色表示）。
每次迭代时，从输入数据中移除一个元素（用红色表示），并原地将其插入到已排好序的链表中。

 

插入排序算法：

插入排序是迭代的，每次只移动一个元素，直到所有元素可以形成一个有序的输出列表。
每次迭代中，插入排序只从输入数据中移除一个待排序的元素，找到它在序列中适当的位置，并将其插入。
重复直到所有输入数据插入完为止。
 

示例 1：

输入: 4->2->1->3
输出: 1->2->3->4
示例 2：

输入: -1->5->3->4->0
输出: -1->0->3->4->5

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/insertion-sort-list
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)
///无插优化
class Solution {///28ms 76.83% 9.8M 14.81%
public:
    ListNode* insertionSortList(ListNode* head) {
        if (!head) return 0;
        ListNode hair{0, head};
        while (head->next)
        {
            for (; head->next && head->val <= head->next->val; head = head->next);
            if (!head->next) break;
            auto now = &hair;
            for (; now->next->val < head->next->val; now = now->next); ///unguarded
            auto tmp = head->next;
            head->next = tmp->next;
            tmp->next = now->next;
            now->next = tmp;
        }
        return hair.next;
    }
};

///纯插入
class SolutionV1 {///52ms 43.43% 9.8M 18.48%
public:
    ListNode* insertionSortList(ListNode* head) {
        if (!head) return 0;
        ListNode hair{0, head};
        head = head->next;
        hair.next->next = 0;
        while (head)
        {
            auto now = &hair;
            for (; now->next && now->next->val < head->val; now = now->next);
            auto tmp = head;
            head = head->next;
            tmp->next = now->next;
            now->next = tmp;
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
