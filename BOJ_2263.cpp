#include <iostream>
#include <vector>

typedef unsigned int u32;

using namespace std;

void getPreOrder(u32* inOrder, u32* inOrder_begin, u32* inOrder_end, u32* postOrder_begin, u32* postOrder_end, u32* valToInIndex);

int main()
{
    u32 N;
    u32 *preOrder, *inOrder, *postOrder, *valToInIndex;
    scanf(" %u", &N);

    preOrder = new u32[N];
    inOrder = new u32[N];
    postOrder = new u32[N];
    valToInIndex = new u32[N + 1];
 
    for (u32 i = 0; i < N; i++)
    {
        u32 tmp;
        scanf(" %u", &tmp);
        inOrder[i] = tmp;
        valToInIndex[tmp] = i;
    }

    for (u32 i = 0; i < N; i++)
    {
        scanf(" %u", postOrder + i);
    }

    getPreOrder(inOrder, inOrder, inOrder + N, postOrder, postOrder + N, valToInIndex);
    printf("\n");

    delete[] preOrder;
    delete[] inOrder;
    delete[] postOrder;
    delete[] valToInIndex;
}

void getPreOrder(u32* inOrder, u32* inOrder_begin, u32* inOrder_end, u32* postOrder_begin, u32* postOrder_end, u32* valToInIndex)
{
    u32 root = *(postOrder_end - 1);
    u32* root_inOrder = inOrder + valToInIndex[root];

    printf("%u ", root);

    if (root_inOrder > inOrder_begin)
    {
        u32 left_size = root_inOrder - inOrder_begin;
        getPreOrder(inOrder, inOrder_begin, root_inOrder, postOrder_begin, postOrder_begin + left_size, valToInIndex);
    }
    if (root_inOrder + 1 < inOrder_end)
    {
        u32 right_size = inOrder_end - (root_inOrder + 1);
        getPreOrder(inOrder, root_inOrder + 1, inOrder_end, postOrder_end - 1 - right_size, postOrder_end - 1, valToInIndex);
    }
}

