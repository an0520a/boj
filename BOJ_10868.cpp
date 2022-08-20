#include <cstdio>
#include <string>
#include <exception>
#include <memory.h>

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;


class SegmentTree_error : public std::exception
{
public:
    SegmentTree_error(const std::string &_errorMessage) : errorMessage("SegmentTree error : " + _errorMessage) {}
    const char *what() const throw() override { return errorMessage.c_str(); }

private:
    std::string errorMessage;
};

template<typename T>
class ADD
{
public:
    T operator()(const T& x, const T& y){ return x + y; }
};

template<typename T, typename Ops = ADD<T>>
class SegmentTree
{
public:
    SegmentTree(T *arr, const size_t &size); // SegmentTree(T* arr, const size_t& size)
    SegmentTree(T *arr, const size_t &size, const Ops &op); // SegmentTree(T* arr, const size_t& size, const Ops& op)
    T getVal(const size_t& begin, const size_t& end);
    const T &at(const size_t &index) const;
    void change(const size_t &index, const T &val);

private:
    T *tree;
    T *arr;
    Ops op;
    size_t sizeArr, size, depth;
    T init(const size_t& index, const size_t& begin, const size_t& end);
    T getVal_cmp(const size_t& left, const size_t& right, const size_t& idx, const size_t& begin, const size_t& end);
    size_t getLeftIndex(const size_t &index);
    size_t getRightIndex(const size_t& index);
    T getLeft(const size_t &index);
    T getRight(const size_t &index);
    T changeCMP(const size_t begin, const size_t &end, const size_t &treeIndex, const size_t &index, const T &val);
};

template <typename T, typename Ops>
SegmentTree<T, Ops>::SegmentTree(T *_arr, const size_t &_size) : sizeArr(_size)
{
    arr = new T[_size];
    memcpy(arr, _arr, sizeArr * sizeof(T));

    depth = 0;
    size = 0;
    for (size_t i = _size; i; i >>= 1) depth++, size = (size << 1) | 1;
    depth++;
    size = (size << 1) | 1;

    tree = new T[size];
    init(0, 0, sizeArr - 1);
}

template <typename T, typename Ops>
SegmentTree<T, Ops>::SegmentTree(T *_arr, const size_t &_size, const Ops &_op) : sizeArr(_size)
{
    arr = new T[_size];
    op = _op;

    memcpy(arr, _arr, sizeArr * sizeof(T));

    depth = 0;
    size = 0;
    for (size_t i = _size; i; i >>= 1) depth++, size = (size << 1) | 1;
    size = (size << 1) | 1;

    tree = new T[size];
    init(0, 0, sizeArr - 1);
}

template <typename T, typename Ops>
T SegmentTree<T, Ops>::init(const size_t &index, const size_t &begin, const size_t &end)
{
    T tmp;
    if (begin == end) tmp = tree[index] = arr[begin];
    else tmp = tree[index] = op(init(getLeftIndex(index), begin, (begin + end) / 2), init(getRightIndex(index), ((begin + end) / 2) + 1, end));

    return tmp;
}

template <typename T, typename Ops>
size_t SegmentTree<T, Ops>::getLeftIndex(const size_t &index) { return (index << 1) + 1; }

template <typename T, typename Ops>
size_t SegmentTree<T, Ops>::getRightIndex(const size_t &index) { return (index << 1) + 2; }

template <typename T, typename Ops>
T SegmentTree<T, Ops>::getLeft(const size_t &index) { return tree[(index << 1) + 1]; }

template <typename T, typename Ops>
T SegmentTree<T, Ops>::getRight(const size_t &index) { return tree[(index << 1) + 2]; }

template <typename T, typename Ops>
T SegmentTree<T, Ops>::getVal(const size_t &begin, const size_t &end)
{
    if (begin > end || end >= sizeArr) throw SegmentTree_error("invaild index");
    else                               return getVal_cmp(0, sizeArr - 1, 0, begin, end);
}

template <typename T, typename Ops>
T SegmentTree<T, Ops>::getVal_cmp(const size_t &left, const size_t &right, const size_t &idx, const size_t &begin, const size_t &end)
{
    if (left == begin && right == end)
        return tree[idx];
    else
    {
        if (begin <= (left + right) / 2 && end >= ((left + right) / 2) + 1)
        {
            T x = getVal_cmp(left, (left + right) / 2, getLeftIndex(idx), begin, (left + right) / 2);
            T y = getVal_cmp(((left + right) / 2) + 1, right, getRightIndex(idx), ((left + right) / 2) + 1, end);
            return op(x, y);
        }
        else if (begin <= (left + right) / 2) return getVal_cmp(left, (left + right) / 2, getLeftIndex(idx), begin, end);
        else if (end >= ((left + right) / 2) + 1) return getVal_cmp(((left + right) / 2) + 1, right, getRightIndex(idx), begin, end);
    }

    throw SegmentTree_error("getVAl ERROR");
}

template <typename T, typename Ops>
const T &SegmentTree<T, Ops>::at(const size_t &index) const { if(index < sizeArr) return arr[index]; else throw SegmentTree_error("Out of Bound"); }

template <typename T, typename Ops>
void SegmentTree<T, Ops>::change(const size_t &index, const T& val)
{
    if(arr[index] == val) return;
    else changeCMP(0, sizeArr - 1, 0, index, val);
}

template <typename T, typename Ops>
T SegmentTree<T, Ops>::changeCMP(const size_t begin, const size_t &end, const size_t &treeIndex, const size_t &index, const T &val)
{
    if(begin == index && end == index) return tree[treeIndex] = val;
    else
    {
        T x;

        if(index <= (begin + end) / 2) return tree[treeIndex] = op(changeCMP(begin, (begin + end) / 2, getLeftIndex(treeIndex), index, val), getRight(treeIndex));
        else                           return tree[treeIndex] = op(changeCMP(((begin + end) / 2) + 1, end, getRightIndex(treeIndex), index, val), getLeft(treeIndex));
    }
}

class ops{ public : constexpr u32 operator()(const u32& x, const u32& y){ return (x < y)? x : y; }};

int main()
{
    u32 N, M;

    scanf(" %u %u", &N, &M);

    u32* arr = new u32[N];
    for (u32 i = 0; i < N; i++) scanf(" %u", arr + i);
    SegmentTree<u32, ops> tree(arr, N);

    for (u32 i = 0; i < M; i++)
    {
        u32 a, b;
        scanf(" %u %u", &a, &b);

        printf("%u\n", tree.getVal(a - 1, b - 1));
    }

    delete[] arr;
}