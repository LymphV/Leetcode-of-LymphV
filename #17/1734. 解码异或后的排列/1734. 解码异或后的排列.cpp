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
给你一个整数数组 perm ，它是前 n 个正整数的排列，且 n 是个 奇数 。

它被加密成另一个长度为 n - 1 的整数数组 encoded ，满足 encoded[i] = perm[i] XOR perm[i + 1] 。比方说，如果 perm = [1,3,2] ，那么 encoded = [2,1] 。

给你 encoded 数组，请你返回原始数组 perm 。题目保证答案存在且唯一。

 

示例 1：

输入：encoded = [3,1]
输出：[1,2,3]
解释：如果 perm = [1,2,3] ，那么 encoded = [1 XOR 2,2 XOR 3] = [3,1]
示例 2：

输入：encoded = [6,5,4,6]
输出：[2,4,1,5,3]
 

提示：

3 <= n < 105
n 是奇数。
encoded.length == n - 1

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/decode-xored-permutation
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)
#define MS(x,y) memset (x, y, sizeof(x))

class Solution {///160ms 65.34% 95.8M 58.57%
    using vi = vector<int>;
public:
    vector<int> decode(vector<int>& encoded) {
        int n = encoded.size();
        vi rst(n+1);
        rst[0] = 0;
        ffor(i,(n+1)/4*4,n+2) rst[0] ^= i;
        for (int i = 1; i < n; i += 2) rst[0] ^= encoded[i];
        FOR(i,n) rst[i + 1] = rst[i] ^ encoded[i];
        return rst;
    }
};

class Solution {///204ms 14.34% 95.8M 67.33%
    using vi = vector<int>;
public:
    vector<int> decode(vector<int>& encoded) {
        int n = encoded.size();
        vi rst(n+1);
        rst[0] = 0;
        FOR(i,n+1) rst[0] ^= i + 1;
        for (int i = 1; i < n; i += 2) rst[0] ^= encoded[i];
        FOR(i,n) rst[i + 1] = rst[i] ^ encoded[i];
        return rst;
    }
};

class Solution {///TLE
    using vi = vector<int>;

    bool decode(vi & encoded, vi & rst)
    {
        int n = encoded.size();
        int check[n + 1];
        MS(check,0);
        check[rst[0] - 1] = 1;
        FOR(i,n)
        {
            int t = rst[i + 1] = rst[i] ^ encoded[i];
            if (t < 1 || n + 1 < t || check[t - 1]) return 0;
            check[t - 1] = 1;
        }
        return 1;
    }
public:
    vector<int> decode(vector<int>& encoded) {
        int n = encoded.size() + 1;
        vi rst(n);
        ffor(i,1,n+1)
        {
            rst[0] = i;
            if (decode(encoded,rst)) break;
        }
        return rst;
    }
};

class SolutionV1 {///TLE
    using vi = vector<int>;

    bool decode(vi & encoded, vi & rst)
    {
        unordered_set<int> check{rst[0]};
        int n = encoded.size();
        FOR(i,n)
        {
            int t = rst[i + 1] = rst[i] ^ encoded[i];
            if (t < 1 || n + 1 < t || check.count(t)) return 0;
            check.insert(t);
        }
        return 1;
    }
public:
    vector<int> decode(vector<int>& encoded) {
        int n = encoded.size() + 1;
        vi rst(n);
        ffor(i,1,n+1)
        {
            rst[0] = i;
            if (decode(encoded,rst)) break;
        }
        return rst;
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
