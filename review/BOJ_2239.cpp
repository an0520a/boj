#include <iostream>
#include <vector>

typedef struct StructPoint
{
    size_t y;
    size_t x;
} Point;

int ctoi(char __c);
void SetSudoku(char (*map)[10]);
bool SetSudokuCalc(
    char (*map)[10], 
    const std::vector<Point>& point_vec, 
    size_t vec_index, 
    bool (*square3x3)[3][10], 
    bool (*row)[10], bool(*col)[10]
);

int main()
{
    char map[9][10];

    std::ios_base::sync_with_stdio(false);

    for (size_t i = 0; i < 9; i++)
    {
        std::cin >> map[i];
    }

    SetSudoku(map);

    for (size_t i = 0; i < 9; i++)
    {
        std::cout << map[i] << "\n";
    }
}

void SetSudoku(char (*map)[10])
{
    bool square3x3[3][3][10] = { false };
    bool row[9][10] = { false };
    bool col[9][10] = { false };
    std::vector<Point> point_vec;

    for (size_t i = 0; i < 9; i++)
    {
        for (size_t j = 0; j < 9; j++)
        {
            if(ctoi(map[i][j]) != 0)
            {
                square3x3[i / 3][j / 3][ctoi(map[i][j])] = true;
                row[i][ctoi(map[i][j])] = true;
                col[j][ctoi(map[i][j])] = true;
            }
            else
            {
                point_vec.push_back({i, j});
            }
        }
    }

    SetSudokuCalc(map, point_vec, 0, square3x3, row, col);
}

bool SetSudokuCalc(
    char (*map)[10], 
    const std::vector<Point>& point_vec, 
    size_t vec_index, 
    bool (*square3x3)[3][10], 
    bool (*row)[10], bool(*col)[10]
)
{
    const Point& p = point_vec[vec_index];

    if(point_vec.size() == vec_index) return true;

    for (size_t i = 1; i <= 9; i++)
    {
        if(square3x3[p.y / 3][p.x / 3][i] == false && row[p.y][i] == false && col[p.x][i] == false)
        {
            square3x3[p.y / 3][p.x / 3][i] = true;
            row[p.y][i] = true;
            col[p.x][i] = true;
            map[p.y][p.x] = '0' + i;

            if(SetSudokuCalc(map, point_vec, vec_index + 1, square3x3, row, col) == true) return true;

            square3x3[p.y / 3][p.x / 3][i] = false;
            row[p.y][i] = false;
            col[p.x][i] = false;
            map[p.y][p.x] = '0';
        }
    }

    return false;
}

int ctoi(char __c)
{
    return __c - '0';
}