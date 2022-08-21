#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <vector>

size_t* createPi(const char* const search);
std::vector<size_t> kmp(const char* const src, const char* const search);

size_t* createPi(const char* const search)
{
    size_t searchLen = strlen(search);
    size_t j = 0;
    size_t* pi = (size_t *)malloc(searchLen * sizeof(size_t));
    pi[0] = 0;

    for (size_t i = 1; i < searchLen; i++)
    {
        while(j > 0 && search[i] != search[j]) j = pi[j - 1];
        if(search[i] == search[j]) pi[i] = j + 1, j++;
    }

    return pi;
}

std::vector<size_t> kmp(const char* const src, const char* const search)
{
    size_t srcLen = strlen(src), searchLen = strlen(search);
    size_t* pi = createPi(search);
    size_t j = 0;
    std::vector<size_t> result;

    for (size_t i = 0; i < srcLen; i++)
    {
        while(j > 0 && src[i] != search[j]) j = pi[j - 1];
        if(src[i] == search[j])
        {
            if(j == searchLen - 1) result.push_back(i - j), j = pi[j];
            else                   j++;
        }
    }

    free(pi);

    return result;
}

int main()
{
    char* src = new char[1000010];
    char* search = new char[1000010];

    fgets(src, 1000010, stdin); src[strlen(src) - 1] = '\0';
    fgets(search, 1000010, stdin), search[strlen(search) - 1] = '\0';

    std::vector<size_t> result = kmp(src, search);

    printf("%lu\n", result.size());

    for (size_t i = 0; i < result.size(); i++) printf("%lu ", result[i] + 1);
}