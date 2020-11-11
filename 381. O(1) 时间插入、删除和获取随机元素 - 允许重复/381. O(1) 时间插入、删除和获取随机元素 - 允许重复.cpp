#if defined(LocalLymphV)
#include "../leetcode.h"
#include <LymphV>
#else
#define print(...) 0
#endif

#if !defined(LocalLymphV) || !defined(DebugLymphV)
#define debug(x) 0
#endif
/**
设计一个支持在平均 时间复杂度 O(1) 下， 执行以下操作的数据结构。

注意: 允许出现重复元素。

insert(val)：向集合中插入元素 val。
remove(val)：当 val 存在时，从集合中移除一个 val。
getRandom：从现有集合中随机获取一个元素。每个元素被返回的概率应该与其在集合中的数量呈线性相关。
示例:

// 初始化一个空的集合。
RandomizedCollection collection = new RandomizedCollection();

// 向集合中插入 1 。返回 true 表示集合不包含 1 。
collection.insert(1);

// 向集合中插入另一个 1 。返回 false 表示集合包含 1 。集合现在包含 [1,1] 。
collection.insert(1);

// 向集合中插入 2 ，返回 true 。集合现在包含 [1,1,2] 。
collection.insert(2);

// getRandom 应当有 2/3 的概率返回 1 ，1/3 的概率返回 2 。
collection.getRandom();

// 从集合中删除 1 ，返回 true 。集合现在包含 [1,2] 。
collection.remove(1);

// getRandom 应有相同概率返回 1 和 2 。
collection.getRandom();

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/insert-delete-getrandom-o1-duplicates-allowed
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)
class RandomizedCollection {///92ms 93.89% 26.7M 7.43%
    unordered_map<int,unordered_set<int>> mp;
    vector<int> ns;
    default_random_engine e;
public:
    /** Initialize your data structure here. */
    RandomizedCollection() : e(time(0)){}

    /** Inserts a value to the collection. Returns true if the collection did not already contain the specified element. */
    bool insert(int val) {
        auto & rst = mp[val];
        rst.insert(ns.size());
        ns.emplace_back(val);
        return rst.size() == 1;
    }

    /** Removes a value from the collection. Returns true if the collection contained the specified element. */
    bool remove(int val) {
        auto & a = mp[val];
        if (a.empty()) return 0;
        auto it = a.begin();
        int i = *it, j = ns.size() - 1;
        swap(ns[i], ns[j]);
        a.erase(it);
        ns.pop_back();

        auto & b = mp[ns[i]];
        b.insert(i);
        b.erase(j);
        return 1;
    }

    /** Get a random element from the collection. */
    int getRandom() {
        if (ns.empty()) return 0;
        uniform_int_distribution<unsigned int> ui (0, ns.size() - 1);///闭区间
        return ns[ui(e)];
    }
};

/**
 * Your RandomizedCollection object will be instantiated and called as such:
 * RandomizedCollection* obj = new RandomizedCollection();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */


#if defined(LocalLymphV)
int main()
{
    vector<> xs{};
    for (auto x : xs)
        print(x), print(Solution().(x)), print("===");
    return 0;
}
#endif
