#include <cstdio>
#include <memory.h>

typedef unsigned int u32;

class Point
{
public:
    Point() {}
    Point(u32 _y, u32 _x) : y(_y), x(_x) {}
    u32 y;
    u32 x;
};

class MarbleMap
{
public:
    MarbleMap(u32 _N, u32 _M);
    MarbleMap(const MarbleMap& map);
    void operator=(const MarbleMap& map);
    ~MarbleMap();
    char*& operator[](const u32& idx);
    void set();
    void print();
    int up();
    int down();
    int left();
    int right();

private:
    char** arr;
    u32 N, M;
    Point R;
    Point B;
};

MarbleMap::MarbleMap(u32 _N, u32 _M) : N(_N), M(_M)
{
    arr = new char*[N];
    for (u32 i = 0; i < N; i++) arr[i] = new char[M];
}

MarbleMap::MarbleMap(const MarbleMap& map)
{
    N = map.N, M = map.M, R = map.R, B = map.B;

    arr = new char*[N];
    for (u32 i = 0; i < N; i++) arr[i] = new char[M], memcpy(arr[i], map.arr[i], M * sizeof(char));
}

void MarbleMap::operator=(const MarbleMap& map)
{
    for (u32 i = 0; i < N; i++) delete[] arr[i];
    delete[] arr;

    N = map.N, M = map.M, R = map.R, B = map.B;

    arr = new char*[N];
    for (u32 i = 0; i < N; i++) arr[i] = new char[M], memcpy(arr[i], map.arr[i], M * sizeof(char));
}

MarbleMap::~MarbleMap()
{
    for (u32 i = 0; i < N; i++) delete[] arr[i];
    delete[] arr;
}

char*& MarbleMap::operator[](const u32& idx) { return arr[idx]; }

void MarbleMap::set()
{
    for (u32 i = 0; i < N; i++)
    {
        for (u32 j = 0; j < M; j++)
        {
            if      (arr[i][j] == 'R') R = {i, j};
            else if (arr[i][j] == 'B') B = {i, j};
        }
    }
}

void MarbleMap::print()
{
    printf("--------------\n");
    for (u32 i = 0; i < N; i++)
    {
        for (u32 j = 0; j < M; j++) printf("%c", arr[i][j]);
        printf("\n");
    }
    printf("\n");
}

int MarbleMap::up()
{
    int flag = 0;

    if(R.y < B.y)
    {
        u32 init;

        if(R.y != 0 && R.x != 0)
        {
            bool reg_flag = true;
            init = R.y;

            for (int i = R.y - 1; i >= 0; i--)
            {
                if      (arr[i][R.x] == '#' || arr[i][R.x] == 'B') { init = i + 1; break; }
                else if (arr[i][R.x] == 'O')
                {
                    flag = -1;
                    reg_flag = false;
                    arr[R.y][R.x] = '.';
                    R = { 0, 0 };
                }
            }
            if(reg_flag && init != R.y)
            {
                if(flag == 0) flag = 1;
                arr[R.y][R.x] = '.';
                arr[init][R.x] = 'R';
                R.y = init;
            }
        }
        if(B.y != 0 && B.x != 0)
        {
            bool reg_flag = true;
            init = B.y;

            for (int i = B.y - 1; i >= 0; i--)
            {
                if      (arr[i][B.x] == '#' || arr[i][B.x] == 'R') { init = i + 1; break; }
                else if (arr[i][B.x] == 'O')
                {
                    reg_flag = false;
                    arr[B.y][B.x] = '.';
                    B = { 0, 0 };
                    return 0;
                }
            }
            if(reg_flag && init != B.y)
            {
                if(flag == 0) flag = 1;
                arr[B.y][B.x] = '.';
                arr[init][B.x] = 'B';
                B.y = init;
            }
        }
    }
    else
    {
        u32 init;

        if(B.y != 0 && B.x != 0)
        {
            bool reg_flag = true;
            init = B.y;

            for (int i = B.y - 1; i >= 0; i--)
            {
                if      (arr[i][B.x] == '#' || arr[i][B.x] == 'R') { init = i + 1; break; }
                else if (arr[i][B.x] == 'O')
                {
                    reg_flag = false;
                    arr[B.y][B.x] = '.';
                    B = { 0, 0 };
                    return 0;
                }
            }
            if(reg_flag && init != B.y)
            {
                if(flag == 0) flag = 1;
                arr[B.y][B.x] = '.';
                arr[init][B.x] = 'B';
                B.y = init;
            }
        }
        if(R.y != 0 && R.x != 0)
        {
            bool reg_flag = true;
            init = R.y;

            for (int i = R.y - 1; i >= 0; i--)
            {
                if      (arr[i][R.x] == '#' || arr[i][R.x] == 'B') { init = i + 1; break; }
                else if (arr[i][R.x] == 'O')
                {
                    flag = -1;
                    reg_flag = false;
                    arr[R.y][R.x] = '.';
                    R = { 0, 0 };
                }
            }
            if(reg_flag && init != R.y)
            {
                if(flag == 0) flag = 1;
                arr[R.y][R.x] = '.';
                arr[init][R.x] = 'R';
                R.y = init;
            }
        }
    }

    return flag;
}

int MarbleMap::down()
{
    int flag = 0;

    if(R.y > B.y)
    {
        u32 init;

        if(R.y != 0 && R.x != 0)
        {
            bool reg_flag = true;
            init = R.y;

            for (int i = R.y + 1; i < N; i++)
            {
                if      (arr[i][R.x] == '#' || arr[i][R.x] == 'B') { init = i - 1; break; }
                else if (arr[i][R.x] == 'O')
                {
                    flag = -1;
                    reg_flag = false;
                    arr[R.y][R.x] = '.';
                    R = { 0, 0 };
                }
            }
            if(reg_flag && init != R.y)
            {
                if(flag == 0) flag = 1;
                arr[R.y][R.x] = '.';
                arr[init][R.x] = 'R';
                R.y = init;
            }
        }
        if(B.y != 0 && B.x != 0)
        {
            bool reg_flag = true;
            init = B.y;

            for (int i = B.y + 1; i < N; i++)
            {
                if      (arr[i][B.x] == '#' || arr[i][B.x] == 'R') { init = i - 1; break; }
                else if (arr[i][B.x] == 'O')
                {
                    reg_flag = false;
                    arr[B.y][B.x] = '.';
                    B = { 0, 0 };
                    return 0;
                }
            }
            if(reg_flag && init != B.y)
            {
                if(flag == 0) flag = 1;
                arr[B.y][B.x] = '.';
                arr[init][B.x] = 'B';
                B.y = init;
            }
        }
    }
    else
    {
        u32 init;

        if(B.y != 0 && B.x != 0)
        {
            bool reg_flag = true;
            init = B.y;

            for (int i = B.y + 1; i < N; i++)
            {
                if      (arr[i][B.x] == '#' || arr[i][B.x] == 'R') { init = i - 1; break; }
                else if (arr[i][B.x] == 'O')
                {
                    reg_flag = false;
                    arr[B.y][B.x] = '.';
                    B = { 0, 0 };
                    return 0;
                }
            }
            if(reg_flag && init != B.y)
            {
                if(flag == 0) flag = 1;
                arr[B.y][B.x] = '.';
                arr[init][B.x] = 'B';
                B.y = init;
            }
        }
        if(R.y != 0 && R.x != 0)
        {
            bool reg_flag = true;
            init = R.y;

            for (int i = R.y + 1; i < N; i++)
            {
                if      (arr[i][R.x] == '#' || arr[i][R.x] == 'B') { init = i - 1; break; }
                else if (arr[i][R.x] == 'O')
                {
                    flag = -1;
                    reg_flag = false;
                    arr[R.y][R.x] = '.';
                    R = { 0, 0 };
                }
            }
            if(reg_flag && init != R.y)
            {
                if(flag == 0) flag = 1;
                arr[R.y][R.x] = '.';
                arr[init][R.x] = 'R';
                R.y = init;
            }
        }
    }

    return flag;
}

int MarbleMap::left()
{
    int flag = 0;

    if(R.x < B.x)
    {
        u32 init;

        if(R.y != 0 && R.x != 0)
        {
            bool reg_flag = true;
            init = R.x;

            for (int i = R.x - 1; i >= 0; i--)
            {
                if      (arr[R.y][i] == '#' || arr[R.y][i] == 'B') { init = i + 1; break; }
                else if (arr[R.y][i] == 'O')
                {
                    flag = -1;
                    reg_flag = false;
                    arr[R.y][R.x] = '.';
                    R = { 0, 0 };
                }
            }
            if(reg_flag && init != R.x)
            {
                if(flag == 0) flag = 1;
                arr[R.y][R.x] = '.';
                arr[R.y][init] = 'R';
                R.x = init;
            }
        }
        if(B.y != 0 && B.x != 0)
        {
            bool reg_flag = true;
            init = B.x;

            for (int i = B.x - 1; i >= 0; i--)
            {
                if      (arr[B.y][i] == '#' || arr[B.y][i] == 'R') { init = i + 1; break; }
                else if (arr[B.y][i] == 'O')
                {
                    reg_flag = false;
                    arr[B.y][B.x] = '.';
                    B = { 0, 0 };
                    return 0;
                }
            }
            if(reg_flag && init != B.x)
            {
                if(flag == 0) flag = 1;
                arr[B.y][B.x] = '.';
                arr[B.y][init] = 'B';
                B.x = init;
            }
        }
    }
    else
    {
        u32 init;

        if(B.y != 0 && B.x != 0)
        {
            bool reg_flag = true;
            init = B.x;

            for (int i = B.x - 1; i >= 0; i--)
            {
                if      (arr[B.y][i] == '#' || arr[B.y][i] == 'R') { init = i + 1; break; }
                else if (arr[B.y][i] == 'O')
                {
                    reg_flag = false;
                    arr[B.y][B.x] = '.';
                    B = { 0, 0 };
                    return 0;
                }
            }
            if(reg_flag && init != B.x)
            {
                if(flag == 0) flag = 1;
                arr[B.y][B.x] = '.';
                arr[B.y][init] = 'B';
                B.x = init;
            }
        }
        if(R.y != 0 && R.x != 0)
        {
            bool reg_flag = true;
            init = R.x;

            for (int i = R.x - 1; i >= 0; i--)
            {
                if      (arr[R.y][i] == '#' || arr[R.y][i] == 'B') { init = i + 1; break; }
                else if (arr[R.y][i] == 'O')
                {
                    flag = -1;
                    reg_flag = false;
                    arr[R.y][R.x] = '.';
                    R = { 0, 0 };
                }
            }
            if(reg_flag && init != R.x)
            {
                if(flag == 0) flag = 1;
                arr[R.y][R.x] = '.';
                arr[R.y][init] = 'R';
                R.x = init;
            }
        }
    }

    return flag;
}

int MarbleMap::right()
{
    int flag = 0;

    if(R.x > B.x)
    {
        u32 init;

        if(R.y != 0 && R.x != 0)
        {
            bool reg_flag = true;
            init = R.x;

            for (int i = R.x + 1; i < M; i++)
            {
                if      (arr[R.y][i] == '#' || arr[R.y][i] == 'B') { init = i - 1; break; }
                else if (arr[R.y][i] == 'O')
                {
                    flag = -1;
                    reg_flag = false;
                    arr[R.y][R.x] = '.';
                    R = { 0, 0 };
                }
            }
            if(reg_flag && init != R.x)
            {
                if(flag == 0) flag = 1;
                arr[R.y][R.x] = '.';
                arr[R.y][init] = 'R';
                R.x = init;
            }
        }
        if(B.y != 0 && B.x != 0)
        {
            bool reg_flag = true;
            init = B.x;

            for (int i = B.x + 1; i < M; i++)
            {
                if      (arr[B.y][i] == '#' || arr[B.y][i] == 'R') { init = i - 1; break; }
                else if (arr[B.y][i] == 'O')
                {
                    reg_flag = false;
                    arr[B.y][B.x] = '.';
                    B = { 0, 0 };
                    return 0;
                }
            }
            if(reg_flag && init != B.x)
            {
                if(flag == 0) flag = 1;
                arr[B.y][B.x] = '.';
                arr[B.y][init] = 'B';
                B.x = init;
            }
        }
    }
    else
    {
        u32 init;

        if(B.y != 0 && B.x != 0)
        {
            bool reg_flag = true;
            init = B.x;

            for (int i = B.x + 1; i < M; i++)
            {
                if      (arr[B.y][i] == '#' || arr[B.y][i] == 'R') { init = i - 1; break; }
                else if (arr[B.y][i] == 'O')
                {
                    reg_flag = false;
                    arr[B.y][B.x] = '.';
                    B = { 0, 0 };
                    return 0;
                }
            }
            if(reg_flag && init != B.x)
            {
                if(flag == 0) flag = 1;
                arr[B.y][B.x] = '.';
                arr[B.y][init] = 'B';
                B.x = init;
            }
        }
        if(R.y != 0 && R.x != 0)
        {
            bool reg_flag = true;
            init = R.x;

            for (int i = R.x + 1; i < M; i++)
            {
                if      (arr[R.y][i] == '#' || arr[R.y][i] == 'B') { init = i - 1; break; }
                else if (arr[R.y][i] == 'O')
                {
                    flag = -1;
                    reg_flag = false;
                    arr[R.y][R.x] = '.';
                    R = { 0, 0 };
                }
            }
            if(reg_flag && init != R.x)
            {
                if(flag == 0) flag = 1;
                arr[R.y][R.x] = '.';
                arr[R.y][init] = 'R';
                R.x = init;
            }
        }
    }

    return flag;
}

u32 min = 11;

void DFS(const MarbleMap& map, u32 stage, u32 count);

int main()
{
    u32 N, M;

    scanf(" %u %u", &N, &M);

    MarbleMap map(N, M);

    for (u32 i = 0; i < N; i++) 
    {
        for (u32 j = 0; j < M; j++)
        {
            scanf(" %c", &map[i][j]);
        }
    }

    map.set();
    DFS(map, 0, 10);
    if(min == 11) printf("-1\n");
    else printf("%u\n", min);
}

void DFS(const MarbleMap& map, u32 stage, u32 count)
{
    if(count == 0) return;
    else
    {
        int val;
        
        MarbleMap tmp = map;
        val = tmp.up();
        if     (val ==  1 && stage < min - 1) DFS(tmp, stage + 1, count - 1);
        else if(val == -1)                    { min = (stage + 1 < min)? stage + 1 : min; return; }

        tmp = map;
        val = tmp.down();
        if     (val ==  1 && stage < min - 1) DFS(tmp, stage + 1, count - 1);
        else if(val == -1)                    { min = (stage + 1 < min)? stage + 1 : min; return; }

        tmp = map;
        val = tmp.right();
        if     (val ==  1 && stage < min - 1) DFS(tmp, stage + 1, count - 1);
        else if(val == -1)                    { min = (stage + 1 < min)? stage + 1 : min; return; }

        tmp = map;
        val = tmp.left();
        if     (val ==  1 && stage < min - 1) DFS(tmp, stage + 1, count - 1);
        else if(val == -1)                    { min = (stage + 1 < min)? stage + 1 : min; return; }
    }
}