#include <cstdio>
#include <cstring>

typedef unsigned int u32;

int main()
{
    char str[101];
    int index[26];
    for (u32 i = 0; i < 26; i++) index[i] = -1;

    scanf(" %s", str);

    u32 l = strlen(str);
    for (u32 i = 0; i < l; i++) if(index[str[i] - 'a'] == -1) index[str[i] - 'a'] = i;
    for (u32 i = 0; i < 26; i++) printf("%d ", index[i]);
    printf("\n");
}