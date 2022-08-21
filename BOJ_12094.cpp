#include <cstdio>
#include <malloc.h>
#include <memory.h>

typedef unsigned int u32;

class matrix
{
public:
    matrix(u32 size);
    matrix(const matrix& mat);
    ~matrix();
    void operator=(const matrix& mat);
    u32* operator[](const u32 & idx) { return arr[idx]; }
    u32 getMax() const;
    void setMax();
    bool isAbleUpSize() const;
    bool up();
    bool down();
    bool right();
    bool left();
    void print();

    u32** arr;
    u32 max;
    u32 size;
};

matrix::matrix(u32 _size) : size(_size), max(0)
{
    arr = new u32*[_size];
    for (u32 i = 0; i < _size; i++) arr[i] = new u32[_size]{ 0 };
}

matrix::matrix(const matrix& mat)
{
    size = mat.size;
    max = mat.max;

    arr = new u32*[size];
    for (u32 i = 0; i < size; i++)
    {
        arr[i] = new u32[size];

        memcpy(arr[i], mat.arr[i], size * sizeof(u32));
    }
}

matrix::~matrix()
{
    for (u32 i = 0; i < size; i++) delete[] arr[i];
    delete[] arr;
}

void matrix::operator=(const matrix& mat)
{
    if(mat.size != size)
    {
        for (u32 i = 0; i < size; i++) delete[] arr[i];
        delete[] arr;

        size = mat.size;
        max = mat.max;

        arr = new u32*[size];
        for (u32 i = 0; i < size; i++)
        {
            arr[i] = new u32[size];

            memcpy(arr[i], mat.arr[i], size * sizeof(u32));
        }
    }
    else
    {
        max = mat.max;

        for (u32 i = 0; i < size; i++)
        {
            memcpy(arr[i], mat.arr[i], size * sizeof(u32));
        }
    }
}

u32 matrix::getMax() const
{
    return max;
}

void matrix::setMax()
{
    for (u32 i = 0; i < size; i++)
    {
        for (u32 j = 0; j < size; j++)
        {
            max = (arr[i][j] > max)? arr[i][j] : max;
        }
    }
}

bool matrix::isAbleUpSize() const
{
    for (u32 i = 0; i < size; i++)
    {
        for (u32 j = 0; j < size; j++)
        {
            if(arr[i][j] > 1U)
            {
                return true;
            }
        }
    }

    return false;
}

bool matrix::up()
{
    bool flag = false;
    bool (*calculated)[size] = (bool (*)[size])calloc(size * size, sizeof(bool));
    u32 *zero_arr = new u32[size]{ 0 };

    for (u32 i = 1; i < size; i++)
    {
        for (u32 j = 0; j < size; j++)
        {
            if (arr[i][j] != 0)
            {
                for (int k = i - 1; k >= 0; k--)
                {
                    if(arr[k][j] != 0)
                    {
                        if(calculated[k][j] == false && arr[k][j] == arr[i][j])
                        {
                            arr[k][j] *= 2;
                            arr[i][j] = 0;

                            max = (arr[k][j] > max)? arr[k][j] : max;
                            calculated[k][j] = true;
                            flag = true;
                        }

                        break;
                    }
                }
            }
        }
    }

    for (u32 i = 1; i < size; i++)
    {
        for (u32 j = 0; j < size; j++)
        {
            if(arr[i][j] != 0)
            {
                for (; zero_arr[j] < i; zero_arr[j]++)
                {
                    if(arr[zero_arr[j]][j] == 0)
                    {
                        arr[zero_arr[j]][j] = arr[i][j];
                        arr[i][j] = 0;
                        zero_arr[j]++;
                        flag = true;

                        break;
                    }
                }
            }
        }
    }

    delete[] zero_arr;
    free(calculated);

    return flag;
}

bool matrix::down()
{
    bool flag = false;
    bool (*calculated)[size] = (bool (*)[size])calloc(size * size, sizeof(bool));
    u32 *zero_arr = new u32[size];
    for (u32 i = 0; i < size; i++) zero_arr[i] = size - 1;

    for (int i = size - 2; i >= 0; i--)
    {
        for (u32 j = 0; j < size; j++)
        {
            if (arr[i][j] != 0)
            {
                for (u32 k = i + 1; k < size; k++)
                {
                    if(arr[k][j] != 0)
                    {
                        if(calculated[k][j] == false && arr[k][j] == arr[i][j])
                        {
                            arr[k][j] *= 2;
                            arr[i][j] = 0;
                            max = (arr[k][j] > max)? arr[k][j] : max;

                            calculated[k][j] = true;
                            flag = true;
                        }

                        break;
                    }
                }
            }
        }
    }

    for (int i = size - 2; i >= 0; i--)
    {
        for (u32 j = 0; j < size; j++)
        {
            if(arr[i][j] != 0)
            {
                for (; zero_arr[j] > i; zero_arr[j]--)
                {
                    if(arr[zero_arr[j]][j] == 0)
                    {
                        arr[zero_arr[j]][j] = arr[i][j];
                        arr[i][j] = 0;
                        zero_arr[j]--;
                        flag = true;

                        break;
                    }
                }
            }
        }
    }

    delete[] zero_arr;
    free(calculated);

    return flag;
}

bool matrix::left()
{
    bool flag = false;
    bool (*calculated)[size] = (bool (*)[size])calloc(size * size, sizeof(bool));
    u32 *zero_arr = new u32[size]{ 0 };

    for (u32 i = 0; i < size; i++)
    {
        for (u32 j = 1; j < size; j++)
        {
            if (arr[i][j] != 0)
            {
                for (int k = j - 1; k >= 0; k--)
                {
                    if(arr[i][k] != 0)
                    {
                        if(calculated[i][k] == false && arr[i][k] == arr[i][j])
                        {
                            arr[i][k] *= 2;
                            arr[i][j] = 0;
                            max = (arr[i][k] > max)? arr[i][k] : max;

                            calculated[i][k] = true;
                            flag = true;
                        }

                        break;
                    }
                }
            }
        }
    }

    for (u32 i = 0; i < size; i++)
    {
        for (u32 j = 1; j < size; j++)
        {
            if(arr[i][j] != 0)
            {
                for (; zero_arr[i] < j; zero_arr[i]++)
                {
                    if(arr[i][zero_arr[i]] == 0)
                    {
                        arr[i][zero_arr[i]] = arr[i][j];
                        arr[i][j] = 0;
                        zero_arr[i]++;
                        flag = true;

                        break;
                    }
                }
            }
        }
    }

    delete[] zero_arr;
    free(calculated);

    return flag;
}

bool matrix::right()
{
    bool flag = false;
    bool (*calculated)[size] = (bool (*)[size])calloc(size * size, sizeof(bool));
    int *zero_arr = new int[size];
    for (u32 i = 0; i < size; i++) zero_arr[i] = size - 1;

    for (u32 i = 0; i < size; i++)
    {
        for (int j = size - 2; j >= 0; j--)
        {
            if (arr[i][j] != 0)
            {
                for (int k = j + 1; k < size; k++)
                {
                    if(arr[i][k] != 0)
                    {
                        if(calculated[i][k] == false && arr[i][k] == arr[i][j])
                        {
                            arr[i][k] *= 2;
                            arr[i][j] = 0;
                            max = (arr[i][k] > max)? arr[i][k] : max;

                            calculated[i][k] = true;
                            flag = true;
                        }

                        break;
                    }
                }
            }
        }
    }

    for (u32 i = 0; i < size; i++)
    {
        for (int j = size - 2; j >= 0; j--)
        {
            if(arr[i][j] != 0)
            {
                for (; zero_arr[i] > j; zero_arr[i]--)
                {
                    if(arr[i][zero_arr[i]] == 0)
                    {
                        arr[i][zero_arr[i]] = arr[i][j];
                        arr[i][j] = 0;
                        zero_arr[i]--;
                        flag = true;

                        break;
                    }
                }
            }
        }
    }

    delete[] zero_arr;
    free(calculated);

    return flag;
}

void matrix::print()
{
    for (u32 i = 0; i < size; i++)
    {
        for (u32 j = 0; j < size; j++)
        {
            printf("%u ", arr[i][j]);
        }
        printf("\n");
    }
}

u32 max = 0;
void getMaxNum(const matrix& mat, u32 count);
u32 pow(u32 a, u32 b);

int main()
{
    u32 N;

    scanf(" %u", &N);

    matrix mat(N);

    for (u32 i = 0; i < N; i++)
    {
        for (u32 j = 0; j < N; j++)
        {
            scanf(" %u", &mat[i][j]);
            max = (mat[i][j] > max)? mat[i][j] : max;
        }
    }

    mat.setMax();
    getMaxNum(mat, 10);

    printf("%u\n", max);
}

void getMaxNum(const matrix& mat, u32 count)
{
    if(count == 0)
    {
        max = (mat.getMax() > max)? mat.getMax() : max;
    }
    else
    {
        bool flag = ((mat.getMax() << count) > max)? true : false;

        if(flag)
        {
            matrix tmp = mat;
            if(tmp.up()) getMaxNum(tmp, count -1);
            else         getMaxNum(tmp, 0);

            tmp = mat;
            if(tmp.down()) getMaxNum(tmp, count - 1);
            else           getMaxNum(tmp, 0);

            tmp = mat;
            if(tmp.left()) getMaxNum(tmp, count - 1);
            else           getMaxNum(tmp, 0);

            tmp = mat;
            if(tmp.right()) getMaxNum(tmp, count - 1);
            else            getMaxNum(tmp, 0);
        }
    }
}