#include <iostream>
#include <string>
#include <stack>

typedef signed long long i64;

int main()
{
    std::string input_origin_str;
    std::string input_explosion_str;
    std::string output_str;
    std::stack<size_t> equal_len_stk;

    std::ios_base::sync_with_stdio(false);

    std::cin >> input_origin_str;

    std::cin >> input_explosion_str;

    equal_len_stk.push(0);

    for (size_t i = 0; i < input_origin_str.size(); i++)
    {
        output_str.push_back(input_origin_str[i]);

        if(input_origin_str[i] == input_explosion_str[equal_len_stk.top()])
        {
            if(equal_len_stk.empty() || equal_len_stk.top() == 0)
            {
                equal_len_stk.push(1);
            }
            else
            {
                equal_len_stk.top()++;
            }
        }
        else
        {
            if(equal_len_stk.top() != 0)
            {
                equal_len_stk.push(0);

                if(input_origin_str[i] == input_explosion_str[equal_len_stk.top()]) equal_len_stk.top()++;
            }
        }

        if(input_explosion_str.size() == equal_len_stk.top())
        {
            output_str.resize(output_str.size() - input_explosion_str.size());


            equal_len_stk.pop();
            
            if(equal_len_stk.empty()) equal_len_stk.push(0);
            
        }
    }

    if(!output_str.empty())
    {
        std::cout << output_str << std::endl;
    }
    else
    {
        std::cout << "FRULA" << std::endl;
    }
}