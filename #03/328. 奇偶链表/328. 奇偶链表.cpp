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
����һ�������������е������ڵ��ż���ڵ�ֱ�����һ����ע�⣬����������ڵ��ż���ڵ�ָ���ǽڵ��ŵ���ż�ԣ������ǽڵ��ֵ����ż�ԡ�

�볢��ʹ��ԭ���㷨��ɡ�����㷨�Ŀռ临�Ӷ�ӦΪ O(1)��ʱ�临�Ӷ�ӦΪ O(nodes)��nodes Ϊ�ڵ�������

ʾ�� 1:

����: 1->2->3->4->5->NULL
���: 1->3->5->2->4->NULL
ʾ�� 2:

����: 2->1->3->5->6->4->7->NULL
���: 2->3->6->7->1->5->4->NULL
˵��:

Ӧ�����������ڵ��ż���ڵ�����˳��
����ĵ�һ���ڵ���Ϊ�����ڵ㣬�ڶ����ڵ���Ϊż���ڵ㣬�Դ����ơ�

��Դ�����ۣ�LeetCode��
���ӣ�https://leetcode-cn.com/problems/odd-even-linked-list
����Ȩ������������С���ҵת������ϵ�ٷ���Ȩ������ҵת����ע��������
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
