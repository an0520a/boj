#include <iostream>
#include <queue>
#include <stack>

typedef unsigned int u32;

int main()
{
    u32 n;
    u32 time = 0;
    u32 previous_num[1000001] = { 1, 0 };
    bool visited[1000001];  
    std::queue<u32> que;
    std::stack<u32> stk;

    std::cin >> n;

    que.push(n);

    while(!que.empty())
    {
        const size_t que_size = que.size();
        bool find_flag = false;

        for (size_t i = 0; i < que_size; i++)
        {
            u32 v = que.front();
            que.pop();

            if(v == 1)
            {
                find_flag = true;
                break;
            }

            if(v % 3 == 0 && previous_num[v / 3] == 0)
            {
                previous_num[v / 3] = v;
                que.push(v / 3);
            }

            if(v % 2 == 0 && previous_num[v / 2] == 0)
            {
                previous_num[v / 2] = v;
                que.push(v / 2);
            }

            if(previous_num[v - 1] == 0)
            {
                previous_num[v - 1] = v;
                que.push(v - 1);
            }

        }

        if(find_flag) break;

        time++;
    }

    u32 v = 1;

    while(v != 0)
    {
        stk.push(v);
        v = previous_num[v];
    }

    std::cout << time << "\n";
    while(!stk.empty())
    {
        std::cout << stk.top() << ' ';
        stk.pop();
    }

    std::cout<< std::endl;
}