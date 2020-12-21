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
给你两个二进制字符串，返回它们的和（用二进制表示）。

输入为 非空 字符串且只包含数字 1 和 0。

 

示例 1:

输入: a = "11", b = "1"
输出: "100"
示例 2:

输入: a = "1010", b = "1011"
输出: "10101"
 

提示：

每个字符串仅由字符 '0' 或 '1' 组成。
1 <= a.length, b.length <= 10^4
字符串如果不是 "0" ，就都不含前导零。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/add-binary
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)

class Solution { ///0ms 100.00% 6.6M 63.69%
public:
    string addBinary(string a, string b) {
        int n = a.size(), m = b.size();
        if (n == 1 && a[0] == '0') return b;
        if (m == 1 && b[0] == '0') return a;
        string rst;
        char carry = 0;
        for (int i = n - 1, j = m - 1; 0 <= i || 0 <= j || carry; --i, --j)
        {
            char c = (0 <= i ? a[i] - '0' : 0) + (0 <= j ? b[j] - '0' : 0) + carry;
            carry = c >> 1;
            rst += '0' + (c & 1);
        }
        return {rbegin(rst), rend(rst)};
    }
};

class SolutionV2 { ///8ms 20.62% 7.2M 9.06%
    class BigInt2
    {
    protected:
        using vc = vector<char>;

        vc data;


        BigInt2 & assign (string value)
        {
            data.clear();
            if (value.size() == 1 && value[0] == '0') return *this;
            for (auto it = rbegin(value); it != rend(value); ++it)
                data.emplace_back(*it - '0');
            return *this;
        }
        string toString () const
        {
            string rst = "";
            for (auto it = rbegin(data); it != rend(data); ++it)
                rst += '0' + *it;
            return rst.empty() ? "0" : rst;//rst;//
        }

        BigInt2 & iadd (const BigInt2 & value, int offset = 0)
        {
            char carry = 0;
            int n = data.size(), m = value.data.size();
            if (!m) return *this;
            if (!n)
            {
                data.resize(offset);
                data.insert(end(data), begin(value.data), end(value.data));
                return *this;
            }

            if (n < offset) data.resize(offset), n = offset;
            for (int i = offset, j = 0; i < n || j < m || carry; ++i, ++j)
            {
                if (i < n)
                {

                    data[i] = data[i] + (j < m ? value.data[j] : 0) + carry;
                    carry = data[i] >> 1;
                    data[i] &= 1;
                }
                else
                {
                    data.emplace_back((j < m ? value.data[j] : 0) + carry);
                    carry = data[i] >> 1;
                    data[i] &= 1;
                }
            }
            return *this;
        }

        BigInt2 add (const BigInt2 & value, int offset = 0) const
        {
            BigInt2 rst(*this);
            return rst.iadd(value, offset);
        }

    public:
        BigInt2 (string value) {assign(value);}


        virtual ~BigInt2() {}

        std::size_t size () const {return data.size();}

        operator string () const{return toString();}
        BigInt2 & operator+= (const BigInt2 & value){return iadd(value);}
        BigInt2 operator+ (const BigInt2 & value) const {return add(value);}
        BigInt2 & operator= (string value) {return assign(value);}
    };

public:
    string addBinary(string a, string b) {
        return BigInt2(a) + BigInt2(b);
    }
};

class SolutionV1 { ///4ms 69.75% 7M 14.43%
    class BigInt
    {
    protected:
        using vc = vector<char>;
        const static int DIGIT = 2;

        vc data;

        BigInt & assign (int value)
        {
            for(data.clear(); value; value /= DIGIT)
                data.emplace_back(value % DIGIT);
            return *this;
        }
        BigInt & assign (string value)
        {
            data.clear();
            if (value.size() == 1 && value[0] == '0') return *this;
            for (auto it = rbegin(value); it != rend(value); ++it)
                data.emplace_back(*it - '0');
            return *this;
        }
        public:
        string toString () const
        {
            string rst = "";
            for (auto it = rbegin(data); it != rend(data); ++it)
                rst += '0' + *it;
            return rst.empty() ? "0" : rst;//rst;//
        }

        BigInt & iadd (const BigInt & value, int offset = 0)
        {
            char carry = 0;
            int n = data.size(), m = value.data.size();
            if (!m) return *this;
            if (!n)
            {
                data.resize(offset);
                data.insert(end(data), begin(value.data), end(value.data));
                return *this;
            }

            if (n < offset) data.resize(offset), n = offset;
            for (int i = offset, j = 0; i < n || j < m || carry; ++i, ++j)
            {
                if (i < n)
                {

                    data[i] = data[i] + (j < m ? value.data[j] : 0) + carry;
                    carry = data[i] / DIGIT;
                    data[i] %= DIGIT;
                }
                else
                {
                    data.emplace_back((j < m ? value.data[j] : 0) + carry);
                    carry = data[i] / DIGIT;
                    data[i] %= DIGIT;
                }
            }
            return *this;
        }

        BigInt add (const BigInt & value, int offset = 0) const
        {
            BigInt rst(*this);
            return rst.iadd(value, offset);
        }

        BigInt mul (const BigInt & value) const
        {
            if (data.empty() || value.data.empty()) return 0;
            vector<BigInt> times{BigInt(), *this};
            BigInt rst;
            int offset = 0;
            for (auto it = begin(value.data); it != end(value.data); ++it, ++offset)
            {
                for (int i = times.size(); i <= *it; ++i)
                    times.emplace_back(add(times[i - 1]));
                rst.iadd(times[*it], offset);
            }
            return rst;
        }
        BigInt & imul (const BigInt & value) {return *this = mul(value);}

    public:
        BigInt (int value = 0) {assign(value);}
        BigInt (string value) {assign(value);}


        virtual ~BigInt() {}

        std::size_t size () const {return data.size();}

        operator string () const{return toString();}
        BigInt & operator+= (const BigInt & value){return iadd(value);}
        BigInt operator+ (const BigInt & value) const {return add(value);}
        BigInt & operator= (int value) {return assign(value);}
        BigInt & operator= (string value) {return assign(value);}
        BigInt & operator*= (const BigInt & value){return imul(value);}
        BigInt operator* (const BigInt & value) const {return mul(value);}
    };

public:
    string addBinary(string a, string b) {
        return BigInt(a) + BigInt(b);
    }
};

#if defined(LocalLymphV)
int main()
{
    vector<pair<string,string>> xs{
        {"11", "1"},
        {"1010", "1011"}
    };
    for (auto & [x, y] : xs)
        print(x, y), print(Solution().addBinary(x, y)), print("===");
    return 0;
}
#endif
