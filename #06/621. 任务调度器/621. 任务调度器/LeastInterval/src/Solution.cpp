#include "Solution.h"


#if defined(LocalLymphV)
int main()
{
    vector<pair<vector<char>,int>> xs{
        //{{'A','A','A','B','B','B'},2},
        //{{'A','A','A','A','A','A','B','C','D','E','F','G'},2},
        {{'A','A','B','B','C','C','D','D'},2},
    };
    for (auto [x,y] : xs)
        print(x,y), print(Solution().leastInterval(x,y)), print("===");
    return 0;
}
#endif
