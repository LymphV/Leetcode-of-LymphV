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
给定两个单词（beginWord 和 endWord）和一个字典，找到从 beginWord 到 endWord 的最短转换序列的长度。转换需遵循如下规则：

每次转换只能改变一个字母。
转换过程中的中间单词必须是字典中的单词。
说明:

如果不存在这样的转换序列，返回 0。
所有单词具有相同的长度。
所有单词只由小写字母组成。
字典中不存在重复的单词。
你可以假设 beginWord 和 endWord 是非空的，且二者不相同。
示例 1:

输入:
beginWord = "hit",
endWord = "cog",
wordList = ["hot","dot","dog","lot","log","cog"]

输出: 5

解释: 一个最短转换序列是 "hit" -> "hot" -> "dot" -> "dog" -> "cog",
     返回它的长度 5。
示例 2:

输入:
beginWord = "hit"
endWord = "cog"
wordList = ["hot","dot","dog","lot","log"]

输出: 0

解释: endWord "cog" 不在字典中，所以无法进行转换。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/word-ladder
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)

class Solution {///200ms 56.87% 28.4M 7.76%
    using pii = pair<int,int>;

    unordered_map<string, int> words;
    int idNow, n, m;

    int getId (string & s)
    {
        if (words.count(s)) return words[s];
        else return words[s] = ++idNow;
    }

    void addEdge (vector<vector<int>> & graph, string & s)
    {
        int i = getId(s);
        FOR(j,n)
        {
            char tmp = s[j];
            s[j] = '*';

            int id = getId(s);

            graph[i].emplace_back(id);
            graph[id].emplace_back(i);
            //print(s, id);
            s[j] = tmp;
        }
    }
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        n = beginWord.size(), m = wordList.size();
        vector<vector<int>> graph((m + 1) * (n + 1));
        idNow = m - 1;
        FOR(i,m)
        {
            string & s = wordList[i];
            words[s] = i;

            addEdge(graph, s);
        }
        if (!words.count(endWord)) return 0;

        int target = words[endWord], start = getId(beginWord);
        if (m <= start) addEdge(graph, beginWord);
/*FOR(i,idNow)print(i,graph[i]);
print(words);*/
        queue<pii> q; q.push({start, 1});
        while (!q.empty())
        {
            auto [now, rst] = q.front(); q.pop();//print(now,rst);
            for (int i : graph[now]) for (int j : graph[i])
            {

                if (j == target) return rst + 1;
                if (j < m && wordList[j].size())wordList[j] = "", q.push({j, rst + 1});
            }
        }
        return 0;
    }
};


class SolutionV5 {///132ms 80.37% 11.1M 63.12%
    using psi = pair<string,int>;
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> words{begin(wordList),end(wordList)};
        if (!words.count(endWord)) return 0;

        int n = beginWord.size();
        queue<psi> q;
        q.push({beginWord, 1});
        while (!q.empty())
        {
            auto [now, rst] = q.front(); q.pop();
            if (now == endWord) return rst;
            FOR(i,n)
            {
                char tmp = now[i];
                FOR(j,26)
                {
                    now[i] = 'a' + j;
                    if (words.count(now))
                        words.erase(now), q.push({now, rst + 1});
                }
                now[i] = tmp;
            }
        }
        return 0;
    }
};

class SolutionV4 {///204ms 56.00% 40.8M 5.01%
    using psi = pair<string,int>;
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_map<string, int> words;
        unordered_map<string, unordered_set<int>> graph;
        int n = beginWord.size(), m = wordList.size();
        int id = n;
        FOR(i,m)
        {
            words[wordList[i]] = i;
            FOR(j,n)
            {
                string s = wordList[i];
                s[j] = '*';
                graph[s].insert(i);
            }
        }
        if (!words.count(endWord)) return 0;

        queue<psi> q;
        q.push({beginWord, 1});
        while (!q.empty())
        {
            auto [now, rst] = q.front(); q.pop();print(now,rst);
            FOR(i,n)
            {
                string s = now;
                s[i] = '*';
                for (int j : graph[s])
                {
                    if (wordList[j] == endWord) return rst + 1;
                    if (words.count(wordList[j]))words.erase(wordList[j]), q.push({wordList[j], rst + 1});
                }
            }
        }
        return 0;
    }
};

class SolutionV3 {///188ms 59.63% 11.2M 58.68%
    using psi = pair<string,int>;
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> words{begin(wordList),end(wordList)};
        if (!words.count(endWord)) return 0;

        int n = beginWord.size();
        queue<psi> q;
        q.push({beginWord, 1});
        while (!q.empty())
        {
            auto [now, rst] = q.front(); q.pop();
            if (now == endWord) return rst;
            FOR(i,n)
            {
                FOR(j,26)
                {
                    string s = now;
                    s[i] = 'a' + j;
                    if (words.count(s))
                        words.erase(s), q.push({s, rst + 1});
                }
            }
        }
        return 0;
    }
};


class SolutionV2 {///328ms 42.80% 12.1M 41.94%
    using psi = pair<string,int>;
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_map<string, int> words;
        for (auto & x : wordList) words[x];
        if (!words.count(endWord)) return 0;

        int n = beginWord.size();
        vector<unordered_set<char>> cnt(n);

        for (auto & s : wordList)FOR(i,n)
            cnt[i].insert(s[i]);


        queue<psi> q;
        q.push({beginWord, 1});
        words[beginWord] = 1;
        while (!q.empty())
        {
            auto [now, rst] = q.front(); q.pop();
            if (now == endWord) return rst;
            FOR(i,n)
            {
                for (char c : cnt[i])
                {
                    string s = now;
                    s[i] = c;
                    if (words.count(s) && !words[s])
                        words[s] = 1, q.push({s, rst + 1});
                }
            }
        }
        return 0;
    }
};


class SolutionV1 {///236ms 50.42% 11.8M 46.72%
    using psi = pair<string,int>;
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_map<string, int> words;
        for (auto & x : wordList) words[x];
        if (!words.count(endWord)) return 0;

        int n = beginWord.size();
        queue<psi> q;
        q.push({beginWord, 1});
        words[beginWord] = 1;
        while (!q.empty())
        {
            auto [now, rst] = q.front(); q.pop();
            if (now == endWord) return rst;
            FOR(i,n)
            {
                FOR(j,26)
                {
                    string s = now;
                    s[i] = 'a' + j;
                    if (words.count(s) && !words[s])
                        words[s] = 1, q.push({s, rst + 1});
                }
            }
        }
        return 0;
    }
};



#if defined(LocalLymphV)
int main()
{
    using pss = pair<string,string>;
    vector<pair<pss, vector<string>>> xs
    {
        {
            {"hit","cog"},{"hot","dot","dog","lot","log","cog"}
        }
    };
    for (auto [x,y] : xs)
        print(x,y), print(Solution().ladderLength(x.first,x.second,y)), print("===");
    return 0;
}
#endif
