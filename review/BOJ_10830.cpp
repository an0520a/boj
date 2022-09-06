#include <iostream>
#include <memory.h>

typedef unsigned int u32;
typedef unsigned long long u64;

class Matrix
{
public:
    Matrix(const size_t& _row_size, const size_t& _col_size);
    Matrix(const Matrix& _Matrix);
    ~Matrix();
    Matrix& operator=(const Matrix& _Matrix);
    u32* operator[](const size_t& _row_idx);
    Matrix operator*(const Matrix& _Matrix) const;
    Matrix operator%(const u32& mod) const;
    Matrix pow(u64 y, const u32& mod = 0xFFFFFFFF) const;
    std::pair<u32, u32> size() const;
private:
    size_t row_size;
    size_t col_size;
    u32** arr;
};

Matrix::Matrix(const size_t& _row_size, const size_t& _col_size) : row_size(_row_size), col_size(_col_size), arr(new u32*[row_size])
{
    for (size_t i = 0; i < row_size; i++)
    {
        arr[i] = new u32[col_size];
    }
}

Matrix::Matrix(const Matrix& _Matrix) : row_size(_Matrix.row_size), col_size(_Matrix.col_size), arr(new u32*[_Matrix.row_size])
{
    for (size_t i = 0; i < row_size; i++)
    {
        arr[i] = new u32[col_size];
        memcpy(arr[i], _Matrix.arr[i], col_size * sizeof(u32));
    }
}

Matrix::~Matrix()
{
    for (size_t i = 0; i < row_size; i++)
    {
        delete[] arr[i];
    }

    delete[] arr;
}

Matrix& Matrix::operator=(const Matrix& _Matrix)
{
    delete[] arr;

    row_size = _Matrix.row_size;
    col_size = _Matrix.col_size;
    arr = new u32*[row_size];

    for (size_t i = 0; i < row_size; i++)
    {
        arr[i] = new u32[col_size];
        memcpy(arr[i], _Matrix.arr[i], col_size * sizeof(u32));
    }

    return *this;
}

u32* Matrix::operator[](const size_t& _row_idx)
{
    return arr[_row_idx];
}

Matrix Matrix::operator*(const Matrix& _Matrix) const
{
    Matrix return_val(row_size, _Matrix.col_size);

    for (size_t i = 0; i < row_size; i++)
    {
        for (size_t j = 0; j < _Matrix.col_size; j++)
        {
            return_val[i][j] = 0;

            for (size_t k = 0; k < col_size; k++)
            {
                return_val[i][j] += arr[i][k] * _Matrix.arr[k][j];
            }
        }
    }

    return return_val;
}

Matrix Matrix::operator%(const u32& mod) const
{
    Matrix return_val = *this;

    for (size_t i = 0; i < row_size; i++)
    {
        for (size_t j = 0; j < col_size; j++)
        {
            return_val[i][j] %= mod;
        }
    }

    return return_val;
}

Matrix Matrix::pow(u64 y, const u32& mod) const
{
    if(row_size != col_size) throw("error");

    Matrix return_val(row_size, row_size);
    Matrix round_val = *this;

    for (size_t i = 0; i < row_size; i++)
    {
        memset(return_val.arr[i], 0, row_size * sizeof(u32));
        return_val[i][i] = 1;
    }

    do
    {
        if(y & 1) return_val = return_val * round_val % mod;
        round_val = round_val * round_val % mod;
    } while (y >>= 1);

    return return_val;
}

std::pair<u32, u32> Matrix::size() const
{
    return {row_size, col_size};
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    u32 N;
    u64 B;

    std::cin >> N >> B;

    Matrix A(N, N);

    for (size_t i = 0; i < N; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            std::cin >> A[i][j];
        }
    }

    Matrix pow_A = A.pow(B, 1000);

    for (size_t i = 0; i < pow_A.size().first; i++)
    {
        for (size_t j = 0; j < pow_A.size().second; j++)
        {
            std::cout << pow_A[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}