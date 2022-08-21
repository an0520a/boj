#include <stdio.h>

typedef unsigned int u32;
typedef struct _entry entry;

struct _entry
{
    char left;
    char right;
};

entry tree[26] = { { '\0', '\0' } };

void preOrder(char A);
void inOrder(char A);
void postOrder(char A);

int main()
{
    u32 N;

    scanf(" %u", &N);

    for (u32 i = 0; i < N; i++)
    {
        char node, left, right;

        scanf(" %c %c %c", &node, &left, &right);

        if(left != '.')  tree[node - 'A'].left  = left;
        if(right != '.') tree[node - 'A'].right = right;
    }

    preOrder('A'), printf("\n");
    inOrder('A'), printf("\n");
    postOrder('A'), printf("\n");
}

void preOrder(char A)
{
    if(A == '\0') return;

    printf("%c", A);
    preOrder(tree[A - 'A'].left);
    preOrder(tree[A - 'A'].right);
}

void inOrder(char A)
{
    if(A == '\0') return;

    inOrder(tree[A - 'A'].left);
    printf("%c", A);
    inOrder(tree[A - 'A'].right);
}

void postOrder(char A)
{
    if(A == '\0') return;
    
    postOrder(tree[A - 'A'].left);
    postOrder(tree[A - 'A'].right);
    printf("%c", A);
}