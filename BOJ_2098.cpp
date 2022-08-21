#include <stdio.h>
#include <memory.h>

typedef unsigned int u8;
typedef unsigned int u16;
typedef unsigned int u32;

constexpr u16 getBit(u32 i) { return 0b1 << i; }
constexpr u16 getFullBit(u32 length) { return (0b1 << length) - 1; }

typedef struct _bit16 bit16;

struct _bit16
{
    u16 bit;
    inline bit16& operator=(const u16& _bit) { bit = _bit; return *this; }
    inline bit16& operator=(const bit16& _bit) { bit = _bit.bit; return *this; }
    inline bit16 operator&(const u16& _bit) { return bit16{bit & _bit}; }
    inline bit16 operator|(const bit16& _bit) { return bit16{bit | _bit.bit}; }
    inline bit16 operator&(const bit16& _bit) { return bit16{bit & _bit.bit}; }
    inline bit16 operator|(const u16& _bit) { return bit16{bit | _bit}; }
    inline bool operator!=(const u16& _bit) { return bit != _bit; }
    inline bool operator!=(const bit16& _bit) { return bit != _bit.bit; }
    inline bool operator==(const u16& _bit) { return bit == _bit; } 
    inline bool operator==(const bit16& _bit) { return bit == _bit.bit; } 
    inline bool operator[](const u32& i) { return (bit & (0b1 << i))? true : false; }
};

u32 DFS(u32 (*graph)[16], u32 N, u32 vertex, bit16 bit);

int main()
{
    u32 N;
    u32 graph[16][16];

    scanf(" %u", &N);

    for (u32 i = 0; i < N; i++)
    {
        for (u32 j = 0; j < N; j++)
        {
            scanf(" %u", &graph[i][j]);
        }
    }

    printf("%u\n", DFS(graph, N, 0, bit16{0b1}));
}

u32 DFS(u32 (*graph)[16], u32 N, u32 vertex, bit16 bit)
{
    static u32 memo[16][0b10000000000000000] = { 0 };

    if(memo[vertex][bit.bit] != 0)
    {
        return memo[vertex][bit.bit];
    }
    else if(bit == getFullBit(N))
    {
        if(graph[vertex][0]) return memo[vertex][bit.bit] = graph[vertex][0];
        else                 return memo[vertex][bit.bit] = 0x7F7F7F7E;
    }
    else
    {
        u32 min = 0x7F7F7F7E;

        for (u32 i = 1; i < N; i++)
        {
            if(graph[vertex][i] != 0 && bit[i] == false)
            {
                u32 tmp = DFS(graph, N, i, bit | getBit(i)) + graph[vertex][i];
                min = (tmp < min)? tmp : min;
            }
        }

        return memo[vertex][bit.bit] = min;
    }
}