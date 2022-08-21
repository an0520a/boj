#include <iostream>
#include <exception>

typedef unsigned int u32;
typedef unsigned long long u64;

class Matrix
{
public:
    Matrix(const u32& _row_num, const u32& _col_num);
    Matrix(const Matrix& v);
    ~Matrix();
    void operator=(const Matrix& v);
    u32& at(const u32& row, const u32& col);
    Matrix operator*(const Matrix& v);
    Matrix operator%(const u32& m);
    Matrix pow(u64 n);
    Matrix pow(u64 n, u32 m);
private:
    u32 row_num;
    u32 col_num;
    u32** matrix;
};

Matrix::Matrix(const u32& _row_num, const u32& _col_num) : row_num(_row_num), col_num(_col_num)
{
    matrix = new u32*[row_num];
    
    for (u32 i = 0; i < row_num; i++)
        matrix[i] = new u32[col_num]{ 0 };
}

Matrix::Matrix(const Matrix& v)
{
    row_num = v.row_num;
    col_num = v.col_num;
    matrix = nullptr;

    if (row_num != 0)
    {
        matrix = new u32*[row_num];
        for (u32 i = 0; i < row_num; i++)
            matrix[i] = new u32[col_num];
    }   

    for (u32 i = 0; i < row_num; i++)
    {
        for (u32 j = 0; j < col_num; j++)
        {
            matrix[i][j] = v.matrix[i][j];
        }
    }
}

void Matrix::operator=(const Matrix& v)
{
    row_num = v.row_num;
    col_num = v.col_num;
    matrix = new u32*[row_num]; for (u32 i = 0; i < row_num; i++) matrix[i] = new u32[col_num];

    for (u32 i = 0; i < row_num; i++)
    {
        for (u32 j = 0; j < col_num; j++)
        {
            matrix[i][j] = v.matrix[i][j];
        }
    }
}

Matrix::~Matrix()
{
    for (u32 i = 0; i < row_num; i++)
        delete[] matrix[i];
    delete[] matrix;
    matrix = nullptr;
}

u32& Matrix::at(const u32& row, const u32& col) { return matrix[row][col]; }

Matrix Matrix::operator*(const Matrix& v)
{
    if (col_num != v.row_num) throw std::runtime_error("Not suitable size for matrix multiplication.");

    Matrix tmp(row_num, v.col_num);

    for (u32 i = 0; i < row_num; i++)
    {
        for (u32 j = 0; j < v.col_num; j++)
        {
            for (u32 k = 0; k < col_num; k++)
                tmp.matrix[i][j] += matrix[i][k] * v.matrix[k][j];
        }
    }

    return tmp;
}

Matrix Matrix::operator%(const u32& m)
{
    Matrix tmp(*this);

    for (u32 i = 0; i < row_num; i++)
    {
        for (u32 j = 0; j < col_num; j++)
        {
            tmp.matrix[i][j] %= m;
        }
    }

    return tmp;
}

Matrix Matrix::pow(u64 n)
{
    if (row_num != col_num) throw std::runtime_error("Not suitable size for matrix multiplication.");
    Matrix ret = (*this);
    Matrix result(row_num, col_num);
    for (u32 i = 0; i < row_num; i++) result.matrix[i][i] = 1;

    do
    {
        if (n & 1) result = result * ret;
        ret = ret * ret;
    } while(n >>= 1);

    return result;
}

Matrix Matrix::pow(u64 n, u32 m)
{
    if (row_num != col_num) throw std::runtime_error("Not suitable size for matrix multiplication.");
    Matrix ret = (*this);
    Matrix result(row_num, col_num);
    for (u32 i = 0; i < row_num; i++) result.matrix[i][i] = 1;

    do
    {
        if (n & 1) result =  (result * ret) % m;
        ret = (ret * ret) % m;
    } while(n >>= 1);

    return result;
}

int main()
{
    u32 N;
    u64 B;
    scanf(" %u %llu", &N, &B);

    Matrix mat(N, N);

    for (u32 i = 0; i < N; i++) for (u32 j = 0; j < N; j++) scanf(" %u", &mat.at(i, j));

    mat = mat.pow(B, 1000);

    for (u32 i = 0; i < N; i++)
    {
        for (u32 j = 0; j < N; j++) printf("%u ", mat.at(i, j));
        printf("\n");
    }
}