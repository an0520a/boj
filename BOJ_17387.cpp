#include <cstdio>
#include <memory.h>

typedef unsigned int u32;
typedef long long    i64;

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
        else                                                             return false;
    }

    return l1_ccw <= 0 && l2_ccw <= 0;
}

char line::ccw(const point& p3) const
{
    i64 S = (i64)(p2.x - p1.x) * (i64)(p3.y - p1.y) - (i64)(p2.y - p1.y) * (i64)(p3.x - p1.x);

    if     (S > 0)  return  1;
    else if(S == 0) return  0;
    else            return -1; 
}

bool line::isPart(const point& p) const
{
    return (((p1.x <= p.x && p.x <= p2.x) || (p2.x <= p.x && p.x <= p1.x)) && ((p1.y <= p.y && p.y <= p2.y) || (p2.y <= p.y && p.y <= p1.y)));
}

using namespace std;

int main()
{
    line l1, l2;

    scanf(" %d %d %d %d", &l1.p1.x, &l1.p1.y, &l1.p2.x, &l1.p2.y);
    scanf(" %d %d %d %d", &l2.p1.x, &l2.p1.y, &l2.p2.x, &l2.p2.y);

    printf("%u\n", (l1.isCross(l2))? 1 : 0);
}