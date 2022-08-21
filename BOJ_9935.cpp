#include <cstdio>
#include <cstring>
#include <stack>

typedef unsigned int u32;

using namespace std;

int main()
{
    char str[1000001];
    char bombStr[37];

    scanf(" %s", str);
    scanf(" %s", bombStr);

    u32 strL = strlen(str);
    u32 bombL = strlen(bombStr);

    stack<char> stk;

    for (u32 i = 0; i < strL; i++)
    {
        stk.push(str[i]);

        if (str[i] == bombStr[bombL - 1] && stk.size() >= bombL)
        {
            stack<char> tmp;
            bool flag = true;

            for (u32 j = 0; j < bombL; j++)
            {
                if(stk.top() == bombStr[bombL - 1 - j])
                {
                    tmp.push(stk.top());
                    stk.pop();
                }
                else
                {
                    flag = false;
                    break;
                }
            }

            if (flag == false)
            {
                while(!tmp.empty())
                {
                    stk.push(tmp.top());
                    tmp.pop();
                }
            }
        }
    }

    u32 resultL = stk.size() + 1;

    if (resultL != 1)
    {
        char* result = new char[resultL];
        result[resultL - 1] = '\0';
        
        for (int i = resultL - 2; i >= 0; i--)
            result[i] = stk.top(), stk.pop();

        printf("%s\n", result);

        delete[] result;
    }
    else
    {
        printf("FRULA\n");
    }
}