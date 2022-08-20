#include <cstdio>
#include <cmath>
#include <vector>

typedef int i32;
typedef unsigned int u32;
typedef long long i64;
typedef unsigned long long u64;

class Point
{
public:
    i64 x;
    i64 y;
private:
};

class Vector
{
public:
    Vector();
    Vector(i64 _x, i64 _y);
    Vector(Point _u, Point _v);
    double size() const;
    double length() const;
    Vector operator+(const Vector& v) const;
    Vector operator-(const Vector& v) const;
    Vector& operator+=(const Vector& v);
    Vector& operator-=(const Vector& v);

    i64 x;
    i64 y;
private:
};

Vector GetMinSumVector(const std::vector<Point>& point_vec);

int main()
{
    u64 T;

    scanf(" %llu", &T);

    while(T--)
    {
        u32 N;

        scanf(" %u", &N);

        std::vector<Point> point_vec;
        point_vec.reserve(N);

        for (size_t i = 0; i < N; i++)
        {
            i64 x, y;

            scanf(" %lld %lld", &x, &y);

            point_vec.push_back({x, y});
        }

        Vector get_vector = GetMinSumVector(point_vec);
        printf("%.12lf", get_vector.size());
    }
}

Vector::Vector() : x(0), y(0) {}
Vector::Vector(i64 _x, i64 _y) : x(_x), y(_y) {}
Vector::Vector(Point _u, Point _v) : x(_v.x - _u.x), y(_v.y - _u.y) {}

double Vector::size() const
{
    return std::sqrt((double)x * (double)x + (double)y * (double)y);
}

double Vector::length() const { return size(); }

Vector Vector::operator+(const Vector& v) const
{
    return Vector(x + v.x, y + v.y);
}

Vector Vector::operator-(const Vector& v) const
{
    return Vector(x - v.x, y - v.y);
}

Vector& Vector::operator+=(const Vector& v)
{
    x += v.x;
    y += v.y;
    return *this;
}

Vector& Vector::operator-=(const Vector& v)
{
    x -= v.x;
    y -= v.y;
    return *this;
}

Vector GetMinSumVector(const std::vector<Point>& point_vec)
{
    if(point_vec.size() % 2 != 0) throw("error");
    else if(point_vec.size() == 2)
    {
        return Vector(point_vec[0], point_vec[1]);
    }
    else
    {
        std::vector<Point> tmp_vec = point_vec;
        Vector lowest_length_vector = { 0x7FFFFFFF, 0x7FFFFFFF };

        Point u = tmp_vec.back();
        tmp_vec.pop_back();

        for (size_t i = 0; i < tmp_vec.size(); i++)
        {
            Point v = tmp_vec[i];
            Vector vector = { u, v };
            tmp_vec.erase(tmp_vec.begin() + i);


            Vector next_lowest_length_vector = GetMinSumVector(tmp_vec);
            Vector tmp_lowest_length_vector = ((vector + next_lowest_length_vector).size() < (vector - next_lowest_length_vector).size())? vector + next_lowest_length_vector : vector - next_lowest_length_vector;
            lowest_length_vector = (lowest_length_vector.length() < tmp_lowest_length_vector.size())? lowest_length_vector : tmp_lowest_length_vector;

            tmp_vec.insert(tmp_vec.begin() + i, v);
        }

        return lowest_length_vector;
    }
}