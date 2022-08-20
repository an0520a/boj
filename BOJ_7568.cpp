#include <stdio.h>
#include <stdlib.h>

typedef unsigned int u32;

typedef struct _person
{
    u32 weight;
    u32 height;
    u32 rank;
} person;

int main()
{
    u32 N;
    scanf(" %u", &N);

    person* arr = (person*)malloc(N * sizeof(person));

    for (u32 i = 0; i < N; i++)
    {
        u32 x, y;
        scanf(" %u %u", &x, &y);

        arr[i] = person{x, y, 1};
    }

    auto cmp = [](const person& A, const person& B)->bool{ return (A.weight > B.weight && A.height > B.height)? 1 : 0; };

    for (u32 i = 0; i < N; i++)
    {
        for (u32 j = 0; j < N; j++)
        {
            if(cmp(arr[j], arr[i])) arr[i].rank++;
        }

        printf("%u ", arr[i].rank);
    }
    printf("\n");
    
}