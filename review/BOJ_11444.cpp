#include <iostream>
#include <memory.h>

typedef unsigned long long u64;
typedef unsigned int u32;

template<typename T>
class Matrix
{
public:
    Matrix(const size_t& __row_size, const size_t& __col_size);
    Matrix(const Matrix& __matrix);
    ~Matrix();
    Matrix& operator=(const Matrix& __matrix);
    T* operator[](const size_t& __row_index);
    const T* operator[](const size_t& __row_index) const;
    Matrix operator+(const Matrix& __matrix) const;
    // Matrix& operator+=(const Matrix& __matrix);
    Matrix operator*(const Matrix& __matrix) const;
    // Matrix& operator*=(const Matrix& __matrix);
    Matrix operator%(unsigned long long __m) const;
    Matrix pow(unsigned long long __n, unsigned long long __m = UINT64_MAX) const;
private:
    T** mat_arr;
    size_t row_size;
    size_t col_size;
};

u32 fib(const u64& n, const u64& m = UINT64_MAX);

int main()
{
    u64 n;

    std::ios_base::sync_with_stdio(false);

    std::cin >> n;
    std::cout << fib(n, 1000000007);
}



template <typename T>
Matrix<T>::Matrix(const size_t& __row_size, const size_t& __col_size)
{
    row_size = __row_size;
    col_size = __col_size;

    mat_arr = new T*[row_size];

    for (size_t i = 0; i < row_size; i++)
    {
        mat_arr[i] = new T[col_size];
    }
}

template <typename T>
Matrix<T>::Matrix(const Matrix& __matrix)
{
    row_size = __matrix.row_size;
    col_size = __matrix.col_size;

    mat_arr = new T*[row_size];

    for (size_t i = 0; i < row_size; i++)
    {
        mat_arr[i] = new T[col_size];
    }

    for (size_t i = 0; i < row_size; i++)
    {
        memcpy(mat_arr[i], __matrix.mat_arr[i], col_size * sizeof(T));
    }
}

template <typename T>
Matrix<T>::~Matrix()
{
    for (size_t i = 0; i < row_size; i++)
    {
        delete[] mat_arr[i];
    }

    delete[] mat_arr;
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix& __matrix)
{
    if(row_size != __matrix.row_size || col_size != __matrix.col_size)
    {
        for (size_t i = 0; i < row_size; i++)
        {
            delete[] mat_arr[i];
        }
        delete[] mat_arr;

        row_size = __matrix.row_size;
        col_size = __matrix.col_size;

        mat_arr = new T*[row_size];

        for (size_t i = 0; i < row_size; i++)
        {
            mat_arr[i] = new T[col_size];
        }
    }

    for (size_t i = 0; i < row_size; i++)
    {
        memcpy(mat_arr[i], __matrix.mat_arr[i], col_size * sizeof(T));
    }

    return *this;
}

template <typename T>
T* Matrix<T>::operator[](const size_t& __row_index)
{
    return mat_arr[__row_index];
}

template <typename T>
const T* Matrix<T>::operator[](const size_t& __row_index) const
{
    return mat_arr[__row_index];
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix& __matrix) const
{
    if (row_size != __matrix.row_size || col_size != __matrix.col_size)
    {
        throw("invalid size");
    }

    Matrix<T> result_matrix(*this);

    for (size_t r = 0; r < row_size; r++)
    {
        for (size_t c = 0; c < col_size; c++)
        {
            result_matrix[r][c] += __matrix[r][c];
        }
    }

    return result_matrix;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix& __matrix) const
{
    if (col_size != __matrix.row_size || col_size != __matrix.col_size)
    {
        throw("invalid size");
    }

    Matrix<T> result_matrix(row_size, __matrix.col_size);

    for (size_t r = 0; r < row_size; r++)
    {
        memset(result_matrix[r], 0x00, result_matrix.col_size * sizeof(T));
    }

    for (size_t r = 0; r < row_size; r++)
    {
        for (size_t c = 0; c < __matrix.col_size; c++)
        {
            for (size_t k = 0; k < col_size; k++)
            {
                result_matrix[r][c] += (*this)[r][k] * __matrix[k][c];
            }
        }
    }

    return result_matrix;
}

template <typename T>
Matrix<T> Matrix<T>::operator%(unsigned long long __m) const
{
    Matrix<T> result_matrix(*this);

    for (size_t r = 0; r < row_size; r++)
    {
        for (size_t c = 0; c < col_size; c++)
        {
            result_matrix[r][c] %= __m;
        }
    }

    return result_matrix;
}

template <typename T>
Matrix<T> Matrix<T>::pow(unsigned long long __n, unsigned long long __m) const
{
    if (row_size != col_size)
    {
        throw("invalid size");
    }

    Matrix<T> result_matrix(row_size, col_size);
    for (size_t i = 0; i < row_size; i++)
    {
        memset(result_matrix[i], 0x00, col_size * sizeof(T));
        result_matrix[i][i] = 1;
    }

    Matrix<T> r_matrix(*this);

    do
    {
        if(__n & 1) result_matrix = (result_matrix * r_matrix) % __m;
        r_matrix = r_matrix * r_matrix % __m;
    } while (__n >>= 1);
    
    return result_matrix;
}

u32 fib(const u64& n, const u64& m)
{
    Matrix<u64> mat(2, 2);

    mat[0][0] = 1, mat[0][1] = 1, mat[1][0] = 1, mat[1][1] = 0;

    mat = mat.pow(n, m);

    return mat[1][0];
}