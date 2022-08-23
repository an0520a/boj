#include <cstdio>
#include <queue>
#include <list>
#include <algorithm>

typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct StructJewel
{
    u32 M;
    u32 V;
} Jewel;

template <typename T>
T* LowerBound(T* begin, T* end, T& val);

int main()
{
    u32 N, K;
    u32* bag_arr = nullptr;
    Jewel* jewel_arr = nullptr;
    u64 get_jewel_value_sum = 0;
    auto jewel_comp = [](const Jewel& x, const Jewel& y)->bool{ return x.V < y.V; };
    std::priority_queue<Jewel, std::vector<Jewel>, decltype(jewel_comp)> que(jewel_comp);

    scanf(" %u %u", &N, &K);

    jewel_arr = new Jewel[N];
    bag_arr = new u32[K];

    /*
        필요 : 
        1. 가치가 높은 보석은 가능한한 가방에 들어가야한다.
        1.1. 가치가 높은 보석부터 가방에 넣는다.
        1.2. 가치가 같다면, 먼저 무거운 보석을 가능한 가벼운 가방에 넣는다.
        2. 가치가 낮은 보석은 불가능하다면 가방에 들어가지 않아도 된다.
        3. 가벼운 가방부터 사용해야한다.
    */

    for (size_t i = 0; i < N; i++)
    {
        scanf(" %u %u", &jewel_arr[i].M, &jewel_arr[i].V);
    }

    for (size_t i = 0; i < K; i++)
    {
        scanf(" %u", bag_arr + i);
    }

    std::sort(jewel_arr, jewel_arr + N, [](const Jewel& x, const Jewel& y)->bool{ return x.M < y.M; });
    std::sort(bag_arr, bag_arr + K);

    for (size_t i = 0, j = 0; i < K; i++)
    {
        for (; j < N; j++)
        {
            if(bag_arr[i] >= jewel_arr[j].M) que.push(jewel_arr[j]);
            else break;
        }

        if(!que.empty())
        {
            get_jewel_value_sum += que.top().V;
            que.pop();
        }
    }

    printf("%llu\n", get_jewel_value_sum);


    delete[] jewel_arr;
    delete[] bag_arr;
}