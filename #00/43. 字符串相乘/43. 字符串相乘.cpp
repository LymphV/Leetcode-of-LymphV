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
给定两个以字符串形式表示的非负整数 num1 和 num2，返回 num1 和 num2 的乘积，它们的乘积也表示为字符串形式。

示例 1:

输入: num1 = "2", num2 = "3"
输出: "6"
示例 2:

输入: num1 = "123", num2 = "456"
输出: "56088"
说明：

num1 和 num2 的长度小于110。
num1 和 num2 只包含数字 0-9。
num1 和 num2 均不以零开头，除非是数字 0 本身。
不能使用任何标准库的大数类型（比如 BigInteger）或直接将输入转换为整数来处理。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/multiply-strings
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)

class BigInt
{
protected:
    using vc = vector<char>;
    const static int DIGIT = 10;

    vc data;

    BigInt & assign (int value)
    {
        for(data.clear(); value; value /= DIGIT)
            data.emplace_back(value % 10);
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
        return rst.empty() ? "0" : rst;
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


ostream & operator<< (ostream & out, const BigInt & value)
{
    return out << string(value);
}


class Solution {///24ms 33.67% 8.5M 33.93%
public:
    string multiply(string num1, string num2) {
        return BigInt(num1) * BigInt(num2);
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
