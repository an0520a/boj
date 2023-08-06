#include <iostream>
#include <vector>
#include <queue>

int main()
{
    size_t N, M;
    size_t K;
    size_t max_value;
    bool* known_arr = nullptr;
    std::vector< std::vector<size_t> > graph;
    std::vector< std::vector<size_t> > party_vec;
    std::queue<size_t> point_queue;

    std::cin >> N >> M;

    max_value = M;

    known_arr = new bool[N + 1]{ false };
    graph.resize(N + 1);
    party_vec.resize(M);

    std::cin >> K;

    for (size_t i = 0; i < K; i++)
    {
        size_t v;

        std::cin >> v;

        known_arr[v] = true;
        point_queue.push(v);
    }

    for (size_t i = 0; i < M; i++)
    {
        size_t K;

        std::cin >> K;

        for (size_t j = 0; j < K; j++)
        {
            size_t v;

            std::cin >> v;

            party_vec[i].push_back(v);
        }
    }

    for (size_t i = 0; i < M; i++)
    {
        for (size_t j = 1; j < party_vec[i].size(); j++)
        {
            graph[party_vec[i][0]].push_back(party_vec[i][j]);
            graph[party_vec[i][j]].push_back(party_vec[i][0]);
        }
    }

    while(!point_queue.empty())
    {
        size_t p = point_queue.front();
        point_queue.pop();

        for (size_t v : graph[p])
        {
            if (known_arr[v] == false)
            {
                known_arr[v] = true;
                point_queue.push(v);
            }
        }
    }

    for (size_t i = 0; i < M; i++)
    {
        for (size_t p : party_vec[i])
        {
            if (known_arr[p] == true)
            {
                max_value--;
                break;
            }
        }
    }

    std::cout << max_value << std::endl;

    delete[] known_arr;
    known_arr = nullptr;
}