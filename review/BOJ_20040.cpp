#include <iostream>

size_t find(size_t* parent_arr, size_t idx);
void merge(size_t* parent_arr, size_t idx1, size_t idx2);

int main()
{
    size_t n, m;
    size_t result = 0;
    size_t* parent_arr = nullptr;

    std::ios_base::sync_with_stdio(false);

    std::cin >> n >> m;

    parent_arr = new size_t[n];
    for (size_t i = 0; i < n; i++) parent_arr[i] = i;

    for (size_t i = 0; i < m; i++)
    {
        size_t p1, p2;

        std::cin >> p1 >> p2;

        if(find(parent_arr, p1) == find(parent_arr, p2))
        {
            result = i + 1;
            break;
        }
        else
        {
            merge(parent_arr, p1, p2);
        }
    }

    std::cout << result << std::endl;

    delete[] parent_arr;
}

size_t find(size_t* parent_arr, size_t idx)
{
    if(parent_arr[idx] == idx) return idx;
    else                       return parent_arr[idx] = find(parent_arr, parent_arr[idx]);   
}

void merge(size_t* parent_arr, size_t idx1, size_t idx2)
{
    parent_arr[find(parent_arr, idx1)] =  find(parent_arr, idx2);
}