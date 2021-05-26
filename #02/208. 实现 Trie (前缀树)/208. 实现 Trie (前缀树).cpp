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
Trie（发音类似 "try"）或者说 前缀树 是一种树形数据结构，用于高效地存储和检索字符串数据集中的键。这一数据结构有相当多的应用情景，例如自动补完和拼写检查。

请你实现 Trie 类：

Trie() 初始化前缀树对象。
void insert(String word) 向前缀树中插入字符串 word 。
boolean search(String word) 如果字符串 word 在前缀树中，返回 true（即，在检索之前已经插入）；否则，返回 false 。
boolean startsWith(String prefix) 如果之前已经插入的字符串 word 的前缀之一为 prefix ，返回 true ；否则，返回 false 。
 

示例：

输入
["Trie", "insert", "search", "search", "startsWith", "insert", "search"]
[[], ["apple"], ["apple"], ["app"], ["app"], ["app"], ["app"]]
输出
[null, null, true, false, true, null, true]

解释
Trie trie = new Trie();
trie.insert("apple");
trie.search("apple");   // 返回 True
trie.search("app");     // 返回 False
trie.startsWith("app"); // 返回 True
trie.insert("app");
trie.search("app");     // 返回 True
 

提示：

1 <= word.length, prefix.length <= 2000
word 和 prefix 仅由小写英文字母组成
insert、search 和 startsWith 调用次数 总计 不超过 3 * 104 次

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/implement-trie-prefix-tree
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)

class Trie {///80ms 42.43% 38.3M 91.66%
    using vi = vector<int>;
    using vvi = vector<vi>;
    static const int N = 27;

    vvi data;
public:
    /** Initialize your data structure here. */
    Trie() : data(1, vi(N, 0)){}

    /** Inserts a word into the trie. */
    void insert(string word) {
        int now = 0;
        for (char c : word)
        {
            int & next = data[now][c - 'a'];
            if (!next)
            {
                next = data.size();
                data.emplace_back(vi(N,0));
            }
            now = next;
        }
        data[now].back() = 1;
    }

    /** Returns if the word is in the trie. */
    bool search(string word) {
        int now = 0;
        for (char c : word)
        {
            if (!(now = data[now][c - 'a'])) return 0;
        }
        return now && data[now].back();
    }

    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        int now = 0;
        for (char c : prefix)
        {
            if (!(now = data[now][c - 'a'])) return 0;
        }
        return now;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */

#if defined(LocalLymphV)
int main()
{
    auto a = Trie();
    print (a.data);
    a.insert("app");
    print (a.data);
    print(a.search("app"));
    print(a.startsWith("ap"));
    return 0;
}
#endif
