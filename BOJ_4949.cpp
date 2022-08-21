#include <stdio.h>
#include <cstring>
#include <stack>

using namespace std;

bool check_str(const char* str);

int main()
{
    char str[110];

    while(true)
    {
        fgets(str, 110, stdin);
        str[strlen(str) - 1] = '\0';

        if(*str == '.' && *(str + 1) == '\0') break;

        printf("%s\n", (check_str(str))? "yes" : "no");
    }
}

bool check_str(const char* str)
{
    const char* p = str;
    stack<char> stk;

    while(*p)
    {
        switch (*p)
        {
        case '(':
            stk.push('(');
            break;

        case ')':
            if(stk.empty()) return 0;
            else if (stk.top() != '(') return 0;
            stk.pop();
            break;

        case '[':
            stk.push('[');
            break;
            
        case ']':
            if(stk.empty()) return 0;
            else if (stk.top() != '[') return 0;
            stk.pop();
            break;
        }

        p++;
    }

    if(!stk.empty()) return 0;
    else             return 1;
}