#include <cstdio>
#include <queue>
#include <list>
#include <algorithm>

typedef unsigned int u32;

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
    // u32* bag_weight_arr = nullptr;
    std::list<u32> bag_weight_list;
    Jewel* jewel_arr = nullptr;
    u32 get_jewel_value_sum = 0;

    scanf(" %u %u", &N, &K);

    jewel_arr = new Jewel[N];
    // bag_weight_arr = new u32[K];

    /*
        필요 : 
        1. 가치가 높은 보석은 가능한한 가방에 들어가야한다.
        1.1. 가치가 높은 보석부터 가방에 넣는다.
        1.2. 가치가 같다면, 먼저 무거운 보석을 가능한 가벼운 가방에 넣으려 한다.
        2. 가치가 낮은 보석은 불가능하다면 가방에 들어가지 않아도 된다.
        3. 되도록 가벼운 가방부터 사용해야한다.
    */

    for (size_t i = 0; i < N; i++)
    {
        scanf(" %u %u", &jewel_arr[i].M, &jewel_arr[i].V);
    }

    for (size_t i = 0; i < K; i++)
    {
        u32 tmp;
        scanf(" %u", &tmp);
        bag_weight_list.push_back(tmp);
    }

    auto jewel_comp = [](const Jewel& x, const Jewel& y)->bool{ return (x.V == y.V)? (x.M > y.M) : (x.V > y.V); };
    std::sort(jewel_arr, jewel_arr + N, jewel_comp);
    std::sort(bag_weight_list.begin(), bag_weight_list.end());

    for (size_t i = 0; i < N; i++)
    {
        std::list<u32>::iterator iter = std::lower_bound(bag_weight_list.begin(), bag_weight_list.end(), jewel_arr[i].V);

        if(iter != bag_weight_list.end()) get_jewel_value_sum += jewel_arr[i].V;
    }

    printf("%u\n", get_jewel_value_sum);


    delete[] jewel_arr;
}