#include <cstdio>
#include <memory.h>

typedef unsigned int u32;

class point
{
public:
    point(const int& _x = 0, const int& _y = 0) : x(_x), y(_y) {}
    int x;
    int y;
};

class line
{
public:
    line(const point& _p1 = {0, 0}, const point& _p2= {0, 0}) : p1(_p1), p2(_p2) {}
    bool isCross(const line& l) const;

    point p1;
    point p2;
private:
    char ccw(const point& p3) const;
    bool isPart(const point& p) const;
};

bool line::isCross(const line& l) const
{
    char l1_ccw = ccw(l.p1) * ccw(l.p2);
    char l2_ccw = l.ccw(p1) * l.ccw(p2);

    if(l1_ccw == 0 && l2_ccw == 0)
    {
        if(isPart(l.p1) || isPart(l.p2) || l.isPart(p1) || l.isPart(p2)) return true;
        else                             return false;
    }

    return l1_ccw <= 0 && l2_ccw <= 0;
}

char line::ccw(const point& p3) const
{
    int S = (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);

    if     (S > 0)  return  1;
    else if(S == 0) return  0;
    else            return -1; 
}

bool line::isPart(const point& p) const
{
    return (((p1.x <= p.x && p.x <= p2.x) || (p2.x <= p.x && p.x <= p1.x)) && ((p1.y <= p.y && p.y <= p2.y) || (p2.y <= p.y && p.y <= p1.y)));
}

template <typename T>
class Node
{
public:
    Node(T _val = (T)NULL) : val(_val), parent(nullptr) {}
    Node* find();
    T val;
    Node* parent;
};


template <typename T>
Node<T>* Node<T>::find()
{
    if(parent == nullptr) return this;
    else                  return parent = parent->find();
}


using namespace std;

int main()
{
    u32 N;

    scanf(" %u", &N);

    Node<line>* arr = new Node<line>[N];
    u32* size = new u32[N]{ 0 };
    // u32 size[30] = { 0 };

    for (u32 i = 0; i < N; i++)
    {
        int x1, y1, x2, y2;

        scanf(" %d %d %d %d", &x1, &y1, &x2, &y2);

        arr[i].val = {{x1, y1}, {x2, y2}};
    }

    for (u32 i = 0; i < N; i++)
    {
        for (u32 j = i + 1; j < N; j++)
        {
            Node<line> *root_i = arr[i].find(), *root_j = arr[j].find();

            if(root_i != root_j && arr[i].val.isCross(arr[j].val))
            {
                (*root_j).parent = root_i;
            }
        }
    }


    for (u32 i = 0; i < N; i++)
    {
        size[arr[i].find() - arr]++;
    }

    u32 max = 0;
    u32 count = 0;
    for (u32 i = 0; i < N; i++)
    {
        max = (size[i] > max)? size[i] : max;
        if(size[i]) count++;
    }

    printf("%u\n", count);
    printf("%u\n", max);
}