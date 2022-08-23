#include <cstdio>
#include <vector>
#include <algorithm>

typedef unsigned int u32;

std::vector<u32> TransPreorderToPostorder(const std::vector<u32>::iterator& src_begin, const std::vector<u32>::iterator& src_end);

int main()
{
    u32 number_of_node = 0;
    std::vector<u32> preorder_vec;

    while (true)
    {
        u32 tmp;
        
        if(scanf(" %u", &tmp) != EOF)
        {
            preorder_vec.push_back(tmp);
            number_of_node++;
        }
        else
        {
            break;
        }
    }

    std::vector<u32> postorder_vec = TransPreorderToPostorder(preorder_vec.begin(), preorder_vec.end());

    for (u32 i : postorder_vec)
    {
        printf("%u\n", i);
    }
}

std::vector<u32> TransPreorderToPostorder(const std::vector<u32>::iterator& src_begin, const std::vector<u32>::iterator& src_end)
{
    std::vector<u32> vec;
    std::vector<u32> recursion_result_vec;
    std::vector<u32>::iterator left_begin, left_end, right_begin, right_end;

    if(src_begin >= src_end) return vec;
    else
    {
        left_begin = src_begin + 1;
        right_end = src_end;
        
        right_begin = src_end;
        for (auto iter = src_begin; iter != src_end; iter++)
        {
            if(*iter > *src_begin)
            {
                right_begin = iter;
                break;
            } 
        }
        left_end = right_begin;

        recursion_result_vec = TransPreorderToPostorder(left_begin, left_end);
        vec.insert(vec.end(), recursion_result_vec.begin(), recursion_result_vec.end());
        
        recursion_result_vec = TransPreorderToPostorder(right_begin, right_end);
        vec.insert(vec.end(), recursion_result_vec.begin(), recursion_result_vec.end());

        vec.push_back(*src_begin);

        return vec;
    }

}