#include <iostream>
#include <array>

std::pair<size_t, size_t> DividePaper(bool* paper, size_t paper_size, size_t y, size_t x, size_t check_size)
{
    const static auto get_value = [paper, paper_size](size_t row_index, size_t col_index)->bool
    {
        return paper[row_index * paper_size + col_index];
    };

    if (check_size == 1)
    {
        if (get_value(y, x) == true)
        {
            return { 1, 0 };
        }
        else
        {
            return { 0, 1 };
        }
    }
    else
    {
        std::pair<size_t, size_t> paper_num = { 0, 0 };
        std::pair<size_t, size_t> tmp_paper_num = { 0, 0 };
        size_t next_check_size = check_size / 2;

        tmp_paper_num = DividePaper(paper, paper_size, y, x, next_check_size);
        paper_num.first += tmp_paper_num.first, paper_num.second += tmp_paper_num.second;

        tmp_paper_num = DividePaper(paper, paper_size, y + next_check_size, x, next_check_size);
        paper_num.first += tmp_paper_num.first, paper_num.second += tmp_paper_num.second;

        tmp_paper_num = DividePaper(paper, paper_size, y, x + next_check_size, next_check_size);
        paper_num.first += tmp_paper_num.first, paper_num.second += tmp_paper_num.second;

        tmp_paper_num = DividePaper(paper, paper_size, y + next_check_size, x + next_check_size, next_check_size);
        paper_num.first += tmp_paper_num.first, paper_num.second += tmp_paper_num.second;

        auto [blue_paper_num, white_paper_num] = paper_num;

        if      (white_paper_num == 0)  return std::pair<size_t, size_t>(1, 0);
        else if (blue_paper_num == 0)   return std::pair<size_t, size_t>(0, 1);
        else                            return paper_num;
    }
}

int main()
{
    size_t paper_size;

    std::ios_base::sync_with_stdio(false);

    std::cin >> paper_size;

    bool* paper = new bool[paper_size * paper_size];

    for (size_t i = 0; i < paper_size; i++)
    {
        for (size_t j = 0; j < paper_size; j++)
        {
            std::cin >> paper[i * paper_size + j];
        }
    }

    auto [blue_paper_num, white_paper_num] = DividePaper(paper, paper_size, 0, 0, paper_size);

    std::cout << white_paper_num << std::endl << blue_paper_num << std::endl;

    delete[] paper;
}