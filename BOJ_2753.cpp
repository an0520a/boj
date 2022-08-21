#include <cstdio>

int main()
{
    size_t n;
    scanf(" %lu", &n);
    printf("%d\n", (n % 400 == 0 || (n % 4 == 0 && n % 100 != 0))? 1 : 0);
}