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
实现 strStr() 函数。

给定一个 haystack 字符串和一个 needle 字符串，在 haystack 字符串中找出 needle 字符串出现的第一个位置 (从0开始)。如果不存在，则返回  -1。

示例 1:

输入: haystack = "hello", needle = "ll"
输出: 2
示例 2:

输入: haystack = "aaaaa", needle = "bba"
输出: -1
说明:

当 needle 是空字符串时，我们应当返回什么值呢？这是一个在面试中很好的问题。

对于本题而言，当 needle 是空字符串时我们应当返回 0 。这与C语言的 strstr() 以及 Java的 indexOf() 定义相符。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/implement-strstr
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)



///hash异或
class Solution///8ms 54.11% 6.8M 58.81%
{
    bool cmp (const string & a, int i, int j, const string & b)
    {
        ffor(k,i,j) if (a[k] != b[k-i]) return 0;
        return 1;
    }
public:
    int strStr (string a, string b)
    {
        int m = a.size(), n = b.size();
        if (!n) return 0;
        if (m < n)return -1;

        int ha1 = 0, ha2 = 0;
        FOR(k,n) ha2 ^= b[k], ha1 ^= a[k];
        ha1 ^= a[n - 1];
        for (int i = 0, j = n; j <= m; ++i, ++j)
        {
            ha1 ^= a[j - 1];
            if (ha1 == ha2 && cmp(a,i,j,b))
                return i;
            ha1 ^= a[i];
        }
        return -1;
    }
};

///手撸KMP
class SolutionV2///4ms 93.89% 7.1M 15.29%
{
public:
    int strStr (string a, string b)
    {
        int m = a.size(), n = b.size();
        if (!n) return 0;
        vector<int> tree(n, -1);
        ffor(j,1,n)
        {
            int k = tree[j - 1];
            while (~k && b[j] != b[k + 1]) k = tree[k];
            if (b[j] == b[k + 1]) tree[j] = k + 1;
        }
        print(tree);
        for (int i = 0, j = 0; i < m;)
        {
            int k = j - 1;
            while (~k && a[i] != b[k + 1]) k = tree[k];
            j = a[i] == b[k + 1] ? k + 2 : k + 1;
            ++i;
            if (j == n) return i - n;
        }
        return -1;
    }
};

///库
class SolutionV1 {///8ms 54.11% 6.6M 88.04%
public:
    int strStr(string haystack, string needle) {
        return haystack.find(needle);
    }
};


#if defined(LocalLymphV)
int main()
{
    vector<pair<string,string>> xs{
        {"hh","aa"},
        {"mississippi","issip"},
        {"hello","ll"}
    };
    for (auto [x,y] : xs)
        print(x,y), print(Solution().strStr(x,y)), print("===");
    return 0;
}
#endif
