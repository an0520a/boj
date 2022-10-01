#include <iostream>
#include <vector>

typedef unsigned int u32;

std::vector<u32> GetPreorder(
    std::vector<u32>::const_iterator inorder_begin, std::vector<u32>::const_iterator inorder_end,
    std::vector<u32>::const_iterator postorder_begin, std::vector<u32>::const_iterator postorder_end
);

int main()
{
    u32 n;
    std::vector<u32> inorder;
    std::vector<u32> postorder;

    std::ios_base::sync_with_stdio(false);

    std::cin >> n;

    inorder.resize(n);
    postorder.resize(n);

    for (u32 i = 0; i < n; i++)
    {
        std::cin >> inorder[i];
    }

    for (u32 i = 0; i < n; i++)
    {
        std::cin >> postorder[i];
    }

    std::vector<u32> preorder = GetPreorder(inorder.begin(), inorder.end(), postorder.begin(), postorder.end());

    for (u32 x : preorder)
    {
        std::cout << x << ' ';
    }
    std::cout << std::endl;
}

std::vector<u32> GetPreorder(
    std::vector<u32>::const_iterator inorder_begin, std::vector<u32>::const_iterator inorder_end,
    std::vector<u32>::const_iterator postorder_begin, std::vector<u32>::const_iterator postorder_end
)
{
    std::vector<u32> preorder;
    std::vector<u32>::const_iterator inorder_root;
    size_t left_child_tree_size = 0;
    size_t right_child_tree_size = 0;

    u32 root = *(postorder_end - 1);

    for (std::vector<u32>::const_iterator iter = inorder_begin; iter < inorder_end; iter++)
    {
        if(*iter == root) 
        {
            inorder_root = iter;
            break;
        }
    }

    left_child_tree_size = inorder_root - inorder_begin;
    right_child_tree_size = inorder_end - (inorder_root + 1);

    preorder.push_back(root);
    if(left_child_tree_size != 0)
    {
        std::vector<u32> left_child_tree_preorder;
        left_child_tree_preorder = 
            GetPreorder(inorder_begin, inorder_root, postorder_begin, postorder_begin + left_child_tree_size);
        preorder.insert(preorder.end(), left_child_tree_preorder.begin(), left_child_tree_preorder.end());
    }
    if(right_child_tree_size != 0)
    {
        std::vector<u32> right_child_tree_preorder;
        right_child_tree_preorder = 
            GetPreorder(inorder_root + 1, inorder_end, postorder_end - 1 - right_child_tree_size, postorder_end - 1);
        preorder.insert(preorder.end(), right_child_tree_preorder.begin(), right_child_tree_preorder.end());
    }


    return preorder;
}