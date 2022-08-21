#include <cstdio>
#include <memory.h>

typedef unsigned int u32;

class point
{
public:
    point(const int& _x = 0, const int& _y = 0) : x(_x), y(_y) {}
    bool operator==(const point& p) const { return p.x == x && p.y == y; }
    bool operator!=(const point& p) const { return p.x != x || p.y != y; }
    bool operator<(const point& p) const { return (x != p.x)? x < p.x : y < p.y; }
    int x;
    int y;
};

class line
{
public:
    line(const point& _p1 = {0, 0}, const point& _p2= {0, 0}) : p1(_p1), p2(_p2) {}
    bool isCross(const line& l) const;
    bool operator<(const line& l) const { return (p1 != l.p1)? p1 < l.p1 : p2 < l.p2; }
    char ccw(const point& p3) const;

    point p1;
    point p2;
private:
    bool isPart(const point& p) const;
};

bool line::isCross(const line& l) const
{
    char l1_ccw = ccw(l.p1) * ccw(l.p2);
    char l2_ccw = l.ccw(p1) * l.ccw(p2);

    if(l1_ccw == 0 && l2_ccw == 0)
    {
        if(isPart(l.p1) || isPart(l.p2)) return true;
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

using namespace std;

int main()
{
    int x1, y1, x2, y2, x3, y3;

    scanf(" %d %d", &x1, &y1);
    scanf(" %d %d", &x2, &y2);
    scanf(" %d %d", &x3, &y3);

    printf("%d\n", line({x1, y1}, {x2, y2}).ccw({x3, y3}));
}