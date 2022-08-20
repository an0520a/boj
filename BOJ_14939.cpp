#include <cstdio>
#include <memory.h>

typedef unsigned char u8;
typedef unsigned int u32;

char memo[1024][10][11] = { 0 };
char onCount[1024] = { 0 };
u8 pushCount[1024] = { 0 };

void set(u32 val = 0, u32 count = 0);
int off(char arr[10][11], u32 y, u32 x);
constexpr int change(char& c);
constexpr u32 getBitMasking(u32 val, u32 index);

int main()
{
    u32 min = 0x7FFFFFFF;
    for (u8 i = 0; i < 10; i++) scanf(" %s", memo[0][i]);
    for (u8 i = 0; i < 9; i++) memo[0][i][10] = '\n';
    for (u8 i = 0; i < 10; i++) for (u8 j = 0; j < 10; j++) if(memo[0][i][j] == 'O') onCount[0]++;
    set();

    for (u32 i = 0; i < 1024; i++) if(onCount[i] == 0) min = (pushCount[i] < min)? pushCount[i] : min;

    for (u8 y = 1; y < 10; y++)
    {
        for (u32 i = 0; i < 1024; i++)
        {
            for (u32 j = 0; j < 10; j++)
            {
                if(memo[i][y - 1][j] == 'O')
                {
                    onCount[i] += off(memo[i], y, j);
                    pushCount[i]++;
                }
            }

            if(onCount[i] == 0) min = (pushCount[i] < min)? pushCount[i] : min;
        }
    }

    if(min != 0x7FFFFFFF) printf("%u\n", min);
    else printf("-1\n");

}

void set(u32 val, u32 count)
{
    if(count == 10) return;
    else
    {
        u32 next = getBitMasking(val, count);
        int nextOffNum;

        memcpy(memo[next][0], memo[val][0], 10 * 11 * sizeof(char));
        nextOffNum = off(memo[next], 0, count);
        onCount[next] = onCount[val] + nextOffNum;
        pushCount[next] = pushCount[val] + 1;

        set(next, count + 1);
        set(val, count + 1);
    }
}

int off(char arr[10][11], u32 y, u32 x)
{
    int sum = 0;

    sum += change(arr[y][x]);
    if(y != 0) sum += change(arr[y - 1][x]);
    if(x != 0) sum += change(arr[y][x - 1]);
    if(y != 9) sum += change(arr[y + 1][x]);
    if(x != 9) sum += change(arr[y][x + 1]);

    return sum;
}

constexpr int change(char& c)
{
    if(c == 'O') {c = '#'; return -1;}
    else         {c = 'O'; return  1;}
}

constexpr u32 getBitMasking(u32 val, u32 index) { return val ^ (1 << index); }