#include <iostream>
#include <string>
#include <stack>

int main()
{
    std::string input;
    std::string output;
    std::stack<char> stk;

    std::ios_base::sync_with_stdio(false);\

    std::cin >> input;

    for(const char& ch : input)
    {
        if(ch == '+' || ch == '-')
        {
            while (!stk.empty())
            {
                char op = stk.top();

                if(op == '(') break;

                stk.pop();

                output.push_back(op);
            }

            stk.push(ch);
        }
        else if(ch == '*' || ch == '/')
        {
            while(!stk.empty())
            {
                char op = stk.top();
                
                if(op == '+' || op == '-' || op == '(') break;

                stk.pop();

                output.push_back(op);
            }

            stk.push(ch);
        }
        else if(ch == '(')
        {
            stk.push('(');
        }
        else if(ch == ')')
        {
            while(!stk.empty())
            {
                char op = stk.top();
                stk.pop();

                if(op == '(') break;

                output.push_back(op);

            }
        }
        else
        {
            output.push_back(ch);
        }
    }

    while(!stk.empty())
    {
        char op = stk.top();
        stk.pop();

        output.push_back(op);
    }

    std::cout << output;
}