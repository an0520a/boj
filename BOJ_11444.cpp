#include <stdio.h>
#include <malloc.h>

typedef unsigned int u32;
typedef unsigned long long u64;

class Matrix_2x2
{
public:
    Matrix_2x2();
    Matrix_2x2(u64 _a, u64 _b, u64 _c, u64 _d);
    u64 a, b;
    u64 c, d;

    inline Matrix_2x2 operator*(const Matrix_2x2& x);
    inline Matrix_2x2 operator%(const u64& m);
};

Matrix_2x2::Matrix_2x2() : a(0), b(0), c(0), d(0) {}

Matrix_2x2::Matrix_2x2(u64 _a, u64 _b, u64 _c, u64 _d) : a(_a), b(_b), c(_c), d(_d) {}

Matrix_2x2 Matrix_2x2::operator*(const Matrix_2x2& x)
{
    Matrix_2x2 tmp;
    tmp.a = a * x.a + b * x.c;
    tmp.b = a * x.b + b * x.d;
    tmp.c = c * x.a + d * x.c;
    tmp.d = c * x.b + d * x.d;

    return tmp;
}

Matrix_2x2 Matrix_2x2::operator%(const u64& m)
{
    return Matrix_2x2(a % m, b % m, c % m, d % m);
}

u32 fib(u64 n);

int main()
{
    u64 n;
    scanf(" %llu", &n);

    printf("%u\n", fib(n));
}

u32 fib(u64 n)
{
    if (n == 0) return 0;

    u64 k = n;
    Matrix_2x2 ret(1, 1, 1, 0);
    Matrix_2x2 result(1, 0, 0, 1);

    do
    {
        if(k & 1) result = (ret * result) % 1000000007;
        ret = (ret * ret) % 1000000007;
    } while (k >>= 1);
    
    return result.c;
}