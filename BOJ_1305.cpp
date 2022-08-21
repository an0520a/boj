#include <cstdio>
#include <string.h>
#include <vector>

std::vector<size_t> creatPi(char* search);

int main()
{
    char* str = new char[1000001];
    size_t L;

    scanf(" %lu", &L);
    scanf(" %s", str);

    std::vector<size_t> pi = creatPi(str);

    printf("%lu\n", L - pi[L - 1]);

    delete[] str;
}

std::vector<size_t> creatPi(char* search)
{
    size_t searchLen = strlen(search);
    std::vector<size_t> pi(searchLen);
    pi[0] = 0;
    size_t j = 0;

    for (size_t i = 1; i < searchLen; i++)
    {
        while(j != 0 && search[i] != search[j])
        {
            j = pi[j - 1];
        }

        if(search[i] == search[j])
        {
            pi[i] = j + 1;
            j++;
        }
    }

    return pi;
}