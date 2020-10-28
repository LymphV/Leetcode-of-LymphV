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

*/
///python.set.__and__
template <typename T>
unordered_set<T> operator & (const unordered_set<T> & self, const unordered_set<T> & value)
{
    unordered_set<T> res;
    for (typename unordered_set<T>::const_iterator it = self.begin(); it != self.end(); ++it)
        if (value.find(*it) != value.end())
            res.insert(*it);
    return res;
}

class IntSet
{
    int v;
public:
    IntSet (int v) : v(v) {}

    class iterator
    {
        int v;
        int now;
    public:
        iterator (int value, int nowPos = 0) : v(value), now(nowPos)
        {
            for (; v; v >>= 1, ++now)
                if (v & 1) break;
        }

        bool operator== (iterator it) const
        {
            return v == it.v && (!v || now == it.now);
        }
        bool operator!= (iterator it) const
        {
            return !(*this == it);
        }


        iterator & operator++ ()
        {
            for(v >>= 1, ++now; v; v >>= 1, ++now)
                if (v & 1) break;
            return *this;
        }

        iterator operator++ (int)
        {
            iterator rst(v, now);
            ++*this;
            return rst;
        }

        int operator* ()
        {
            return now;
        }
    };

    iterator begin ()
    {
        return iterator(v);
    }
    iterator end ()
    {
        return iterator(0);
    }
};


#define FOR(x,y) for (int x = 0; x < y; ++x)
#define ffor(x,y,z) for (int x = y; x < z; ++x)
using vvc = vector<vector<char>>;

///存有效位置
class SolutionV6 {///16ms 40.05% 9.9M 8.94%
    using si = unordered_set<int>;
    using block = tuple<int,int,int,int>;
    using vi = vector<int>;
    using pii = pair<int,int>;

    vector<int> cnt;
    vector<vector<pii>> pos;

    unordered_map<int, int> validBlock;

    block x2b (int x)
    {
        if (x < 9)return {x, x + 1, 0, 9};
        if (x < 18) return {0, 9, x - 9, x - 8};
        x -= 18;
        int i = x / 3 * 3, j = x % 3 * 3;
        return {i, i + 3, j, j + 3};
    }
    vi p2x (int i, int j)
    {
        return {i, j + 9, i / 3 * 3 + j / 3 + 18};
    }

    auto valid (const vi & xs)
    {
        return cnt[xs[0]] & cnt[xs[1]] & cnt[xs[2]];
    }

    void add (int v, const vi & xs)
    {
        for (int x : xs)
        {
            cnt[x] &= ((1<<9) - 1 - (1 << v));
            if (!--validBlock[x])
                validBlock.erase(x);
        }
    }
    void del (int v, const vi & xs)
    {
        for (int x : xs)
            cnt[x] |= (1 << v), ++validBlock[x];
    }



    void solveBlock (vvc & board, int x, int y = 0);


    int bestBlock()
    {
        int rst = -1, minValid = 10;
        for (auto [x, y] : validBlock)
            if (y < minValid)
                rst = x, minValid = y;
        return rst;
    }

    void solve (vvc & board)
    {
        if (validBlock.empty()) throw 0;
        int x = bestBlock();
        int il, ir, jl, jr;
        tie(il,ir,jl,jr) = x2b(x);
        //print(x, validBlock, il, ir, jl, jr);
        solveBlock(board, x);
    }

public:
    void solveSudoku(vector<vector<char>>& board) {
        cnt = vector<int>(27, (1 << 9) - 1);
        pos = vector<vector<pii>>(27, vector<pii>{});
        FOR(x,27) validBlock[x] = 9;

        FOR(i,9)FOR(j,9)
        {
            if (board[i][j] != '.')
                add(board[i][j] - '1', p2x(i,j));
            else for (int x : p2x(i, j))
                pos[x].emplace_back(pii(i,j));
        }
//print(p2x(0,2));
//print(validBlock);
//FOR(i,27) print(i,bitset<9>(cnt[i]), validBlock[i]);

        try{solve(board);}
        catch(int){print("hh");}
    }
};

void SolutionV6::solveBlock (vvc & board, int x, int y)
{
    int i, j;
    for (; y < pos[x].size(); ++y)
    {
        tie(i,j) = pos[x][y];
        if (board[i][j] == '.') break;
    }

    if (y == pos[x].size())
    {
        solve(board);
        return;
    }


    vi && xs = p2x (i, j);
    for (int v : IntSet(valid(xs)))
    {//print(i,j,v,board[i]);
        add (v, xs);
        board[i][j] = '1' + v;
        solveBlock(board, x, y + 1);
        del (v, xs);
        board[i][j] = '.';
    }
}


///int set
class SolutionV5 {///12ms 43.02% 9.8M 8.96%
    using si = unordered_set<int>;
    using block = tuple<int,int,int,int>;
    using vi = vector<int>;

    vector<int> cnt;
    unordered_map<int, int> validBlock;

    block x2b (int x)
    {
        if (x < 9)return {x, x + 1, 0, 9};
        if (x < 18) return {0, 9, x - 9, x - 8};
        x -= 18;
        int i = x / 3 * 3, j = x % 3 * 3;
        return {i, i + 3, j, j + 3};
    }
    vi p2x (int i, int j)
    {
        return {i, j + 9, i / 3 * 3 + j / 3 + 18};
    }

    auto valid (const vi & xs)
    {
        return cnt[xs[0]] & cnt[xs[1]] & cnt[xs[2]];
    }

    void add (int v, const vi & xs)
    {
        for (int x : xs)
        {
            cnt[x] &= ((1<<9) - 1 - (1 << v));
            if (!--validBlock[x])
                validBlock.erase(x);
        }
    }
    void del (int v, const vi & xs)
    {
        for (int x : xs)
            cnt[x] |= (1 << v), ++validBlock[x];
    }



    void solveBlock (vvc & board, int i, int j, int il, int ir, int jl, int jr);


    int bestBlock()
    {
        int rst = -1, minValid = 10;
        for (auto [x, y] : validBlock)
            if (y < minValid)
                rst = x, minValid = y;
        return rst;
    }

    void solve (vvc & board)
    {
        if (validBlock.empty()) throw 0;
        int x = bestBlock();
        int il, ir, jl, jr;
        tie(il,ir,jl,jr) = x2b(x);
        //print(x, validBlock, il, ir, jl, jr);
        solveBlock(board, il, jl, il, ir, jl, jr);
    }

public:
    void solveSudoku(vector<vector<char>>& board) {
        cnt = vector<int>(27, (1 << 9) - 1);
        FOR(x,27) validBlock[x] = 9;

        FOR(i,9)FOR(j,9) if (board[i][j] != '.')
            add(board[i][j] - '1', p2x(i,j));
//print(p2x(0,2));
//print(validBlock);
//FOR(i,27) print(i,bitset<9>(cnt[i]), validBlock[i]);

        try{solve(board);}
        catch(int){print("hh");}
    }
};

void SolutionV5::solveBlock (vvc & board, int i, int j, int il, int ir, int jl, int jr)
{
    for(;;)
    {
        if (j == jr) j = jl, ++i;
        if (i == ir)
        {
            solve(board);
            return;
        }
        if (board[i][j] != '.') ++j;
        else break;
    }


    vi && xs = p2x (i, j);
    for (int v : IntSet(valid(xs)))
    {//print(i,j,v,board[i]);
        add (v, xs);
        board[i][j] = '1' + v;
        solveBlock(board,i,j+1,il,ir,jl,jr);
        del (v, xs);
        board[i][j] = '.';
    }
}



///有效数最少的block
class SolutionV4 {///36ms 22.11% 16.1M 5.88%
    using si = unordered_set<int>;
    using block = tuple<int,int,int,int>;
    using vi = vector<int>;

    vector<si> cnt;
    unordered_map<int, int> validBlock;

    block x2b (int x)
    {
        if (x < 9)return {x, x + 1, 0, 9};
        if (x < 18) return {0, 9, x - 9, x - 8};
        x -= 18;
        int i = x / 3 * 3, j = x % 3 * 3;
        return {i, i + 3, j, j + 3};
    }
    vi p2x (int i, int j)
    {
        return {i, j + 9, i / 3 * 3 + j / 3 + 18};
    }

    auto valid (const vi & xs)
    {
        return cnt[xs[0]] & cnt[xs[1]] & cnt[xs[2]];
    }

    void add (int v, const vi & xs)
    {
        for (int x : xs)
        {
            cnt[x].erase(v);
            if (!--validBlock[x])
                validBlock.erase(x);
        }
    }
    void del (int v, const vi & xs)
    {
        for (int x : xs)
            cnt[x].insert(v), ++validBlock[x];
    }



    void solveBlock (vvc & board, int i, int j, int il, int ir, int jl, int jr);


    int bestBlock()
    {
        int rst = -1, minValid = 10;
        for (auto [x, y] : validBlock)
            if (y < minValid)
                rst = x, minValid = y;
        return rst;
    }

    void solve (vvc & board)
    {
        if (validBlock.empty()) throw 0;
        int x = bestBlock();
        int il, ir, jl, jr;
        tie(il,ir,jl,jr) = x2b(x);
        //print(x, validBlock, il, ir, jl, jr);
        solveBlock(board, il, jl, il, ir, jl, jr);
    }

public:
    void solveSudoku(vector<vector<char>>& board) {
        cnt = vector<si>(27, {1,2,3,4,5,6,7,8,9});
        FOR(x,27) validBlock[x] = 9;

        FOR(i,9)FOR(j,9) if (board[i][j] != '.')
            add(board[i][j] - '0', p2x(i,j));
//print(p2x(0,2));
//print(validBlock);
//FOR(i,27) print(i,cnt[i], validBlock[i]);

        try{solve(board);}
        catch(int){print("hh");}
    }
};

void SolutionV4::solveBlock (vvc & board, int i, int j, int il, int ir, int jl, int jr)
{
    for(;;)
    {
        if (j == jr) j = jl, ++i;
        if (i == ir)
        {
            solve(board);
            return;
        }
        if (board[i][j] != '.') ++j;
        else break;
    }


    vi && xs = p2x (i, j);
    for (int v : valid(xs))
    {//print(i,j,v,board[i]);
        add (v, xs);
        board[i][j] = '0' + v;
        solveBlock(board,i,j+1,il,ir,jl,jr);
        del (v, xs);
        board[i][j] = '.';
    }
}


///有效数集合求交
class SolutionV3 {///156ms 6.56% 27.1M 5.00%
    using si = unordered_set<int>;
    using block = tuple<int,int,int,int>;
    using vi = vector<int>;
    vector<si> cnt;
    block x2b (int x)
    {
        if (x < 9)return {x, x + 1, 0, 9};
        if (x < 18) return {0, 9, x, x + 1};
        x -= 18;
        int i = x / 3 * 3, j = x % 3 * 3;
        return {i, i + 3, j, j + 3};
    }
    vi p2x (int i, int j)
    {
        return {i, j + 9, i / 3 * 3 + j / 3 + 18};
    }

    /*bool check (int v, const vi & xs)
    {
        for (int x : xs)
            if (!cnt[x].count(v))
                return 0;
        return 1;
    }*/
    auto valid (const vi & xs)
    {
        return cnt[xs[0]] & cnt[xs[1]] & cnt[xs[2]];
    }

    void add (int v, const vi & xs)
    {
        for (int x : xs)
            cnt[x].erase(v);
    }
    void del (int v, const vi & xs)
    {
        for (int x : xs)
            cnt[x].insert(v);
    }

    void solve (vector<vector<char>>& board, int i = 0, int j = 0)
    {
        if (j == 9) j = 0, ++i;
        if (i == 9) throw 0;
        if (board[i][j] != '.') solve(board,i,j+1);
        else
        {
            vi && xs = p2x (i, j);
            for (int v : valid(xs))
            {//print(i,j,v,board[i]);
                //if (!check(v, xs)) continue;
                add (v, xs);
                board[i][j] = '0' + v;
                solve(board,i,j+1);
                del (v, xs);
                board[i][j] = '.';
            }
        }
    }

public:
    void solveSudoku(vector<vector<char>>& board) {
        cnt = vector<si>(27, {1,2,3,4,5,6,7,8,9});

        FOR(i,9)FOR(j,9) if (board[i][j] != '.')
            add(board[i][j] - '0', p2x(i,j));
//print(p2x(0,2));
//FOR(i,27) print(i,cnt[i]);
        try{solve(board);}
        catch(int){print("hh");}
    }
};




///有效数集合
class SolutionV2 {///200ms 5.53% 19.3M 5.00%
    using si = unordered_set<int>;
    using block = tuple<int,int,int,int>;
    using vi = vector<int>;
    vector<si> cnt;
    block x2b (int x)
    {
        if (x < 9)return {x, x + 1, 0, 9};
        if (x < 18) return {0, 9, x, x + 1};
        x -= 18;
        int i = x / 3 * 3, j = x % 3 * 3;
        return {i, i + 3, j, j + 3};
    }
    vi p2x (int i, int j)
    {
        return {i, j + 9, i / 3 * 3 + j / 3 + 18};
    }

    bool check (int v, const vi & xs)
    {
        for (int x : xs)
            if (!cnt[x].count(v))
                return 0;
        return 1;
    }

    void add (int v, const vi & xs)
    {
        for (int x : xs)
            cnt[x].erase(v);
    }
    void del (int v, const vi & xs)
    {
        for (int x : xs)
            cnt[x].insert(v);
    }

    void solve (vector<vector<char>>& board, int i = 0, int j = 0)
    {
        if (j == 9) j = 0, ++i;
        if (i == 9) throw 0;
        if (board[i][j] != '.') solve(board,i,j+1);
        else
        {
            vi && xs = p2x (i, j);
            ffor(v,1,10)
            {//print(i,j,v,board[i]);
                if (!check(v, xs)) continue;
                add (v, xs);
                board[i][j] = '0' + v;
                solve(board,i,j+1);
                del (v, xs);
                board[i][j] = '.';
            }
        }
    }

public:
    void solveSudoku(vector<vector<char>>& board) {
        cnt = vector<si>(27, {1,2,3,4,5,6,7,8,9});

        FOR(i,9)FOR(j,9) if (board[i][j] != '.')
            add(board[i][j] - '0', p2x(i,j));
//print(p2x(0,2));
//FOR(i,27) print(i,cnt[i]);
        try{solve(board);}
        catch(int){print("hh");}
    }
};


///无效数集合
class SolutionV1 {///208ms 5.35% 19.3M 5.00%
    using si = unordered_set<int>;
    using block = tuple<int,int,int,int>;
    using vi = vector<int>;
    si cnt[27];
    block x2b (int x)
    {
        if (x < 9)return {x, x + 1, 0, 9};
        if (x < 18) return {0, 9, x, x + 1};
        x -= 18;
        int i = x / 3 * 3, j = x % 3 * 3;
        return {i, i + 3, j, j + 3};
    }
    vi p2x (int i, int j)
    {
        return {i, j + 9, i / 3 * 3 + j / 3 + 18};
    }

    bool check (int v, const vi & xs)
    {
        for (int x : xs)
            if (cnt[x].count(v))
                return 0;
        return 1;
    }

    void add (int v, const vi & xs)
    {
        for (int x : xs)
            cnt[x].insert(v);
    }
    void del (int v, const vi & xs)
    {
        for (int x : xs)
            cnt[x].erase(v);
    }

    void solve (vector<vector<char>>& board, int i = 0, int j = 0)
    {
        if (j == 9) j = 0, ++i;
        if (i == 9) throw 0;
        if (board[i][j] != '.') solve(board,i,j+1);
        else
        {
            vi && xs = p2x (i, j);
            FOR(v,9)
            {
                if (!check(v, xs)) continue;
                add (v, xs);
                board[i][j] = '1' + v;
                solve(board,i,j+1);
                del (v, xs);
                board[i][j] = '.';
            }
        }
    }

public:
    void solveSudoku(vector<vector<char>>& board) {
        FOR(i,9)FOR(j,9) if (board[i][j] != '.')
            add(board[i][j] - '1', p2x(i,j));
//print(p2x(0,2));
//FOR(i,27) print(i,cnt[i]);
        try{solve(board);}
        catch(int){print("hh");}
    }
};


#if defined(LocalLymphV)
int main()
{
    using vvc = vector<vector<char>>;
    vector<vvc> xs{
        /*{
            {'8','3','.','.','7','.','.','.','.'},
            {'6','.','.','1','9','5','.','.','.'},
            {'.','9','8','.','.','.','.','6','.'},
            {'8','.','.','.','6','.','.','.','3'},
            {'4','.','.','8','.','3','.','.','1'},
            {'7','.','.','.','2','.','.','.','6'},
            {'.','6','.','.','.','.','2','8','.'},
            {'.','.','.','4','1','9','.','.','5'},
            {'.','.','.','.','8','.','.','7','9'}
        },*/
        {
            {'5','3','.','.','7','.','.','.','.'},
            {'6','.','.','1','9','5','.','.','.'},
            {'.','9','8','.','.','.','.','6','.'},
            {'8','.','.','.','6','.','.','.','3'},
            {'4','.','.','8','.','3','.','.','1'},
            {'7','.','.','.','2','.','.','.','6'},
            {'.','6','.','.','.','.','2','8','.'},
            {'.','.','.','4','1','9','.','.','5'},
            {'.','.','.','.','8','.','.','7','9'}
        }
    };
    for (auto x : xs)
        print(x), Solution().solveSudoku(x),print(x), print("===");
    return 0;
}
#endif
