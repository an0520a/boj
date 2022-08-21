#include <cstdio>
#include <stack>

typedef unsigned int u32;

int main()
{
    char str[101];
    char tmp[101];
    char* strP = str;
    char* tmpP = tmp; 
    std::stack<char> stk;

    scanf(" %s", str);

    while(*strP)
    {
        switch (*strP)
        {
        case '(':
            stk.push('(');
            break;

        case ')':
            while(stk.top() != '(')
            {
                *tmpP = stk.top();
                stk.pop();

                tmpP++;
            }
            stk.pop();
            break;

        case '*':
        case '/':
            while(!stk.empty() && stk.top() != '(' && stk.top() != '+' && stk.top() != '-')
            {
                *tmpP = stk.top();
                stk.pop();

                tmpP++;
            }
            stk.push(*strP);
            break;

        case '+':
        case '-':
            while(!stk.empty() && stk.top() != '(')
            {
                *tmpP = stk.top();
                stk.pop();

                tmpP++;
            }
            stk.push(*strP);
            break;

        default:
            *tmpP = *strP;
            tmpP++;
            break;
        }

        strP++;
    }

    while(!stk.empty())
    {
        *tmpP = stk.top();
        stk.pop();

        tmpP++;
    }

    *tmpP = '\0';

    printf("%s\n", tmp);
}