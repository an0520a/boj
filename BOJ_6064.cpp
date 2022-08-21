#include <iostream>

using namespace std;

typedef long long i64;

i64 CRT(i64 m1, i64 m2, i64 a1, i64 a2);
i64 gcd(i64 a, i64 b);
pair<i64, i64> EEA(i64 a, i64 b);

int main()
{
    i64 n;
    scanf(" %lld", &n);

    while(n--)
    {
        i64 m1, m2, a1, a2;
        scanf(" %lld %lld %lld %lld", &m1, &m2, &a1, &a2);
        printf("%lld\n", CRT(m1, m2, a1, a2));
    }
}

i64 CRT(i64 m1, i64 m2, i64 a1, i64 a2)
{
    i64 g = gcd(m1, m2);
    i64 l = m1 * m2 / g;
    i64 result; 

    if (a1 == a2) return a1;
    if (m1 == a1 && m2 == a2) return l;

    i64 a = (a2 - a1 + m2) % m2;
    if (a % g != 0) return -1;
    i64 r = a / g;
    pair<i64, i64> EEA_result = EEA(m1, m2);
    i64 s = EEA_result.first;
    i64 k1 = s * r;

    return ((m1 * k1 + a1) % l + l) % l;
}

pair<i64, i64> EEA(i64 a, i64 b)
{
    if (b == 0) return {1, 0};

    i64 r, q1, q2;
    i64 s1, t1, s2, t2;

    s1 = 1, t1 = 0;
    q1 = a / b;
    r = a % b;

    a = b;
    b = r;
    s2 = 0, t2 = 1;
    if (b == 0) return {0, 1};
    q2 = a / b;
    r = a % b;

    while (true)
    {
        a = b;
        b = r;
        s1 = s1 - q1 * s2, t1 = t1 - q1 * t2;
        if (b == 0) return {s1, t1};
        q1 = a / b;
        r = a % b;

        a = b;
        b = r;
        s2 = s2 - q2 * s1, t2 = t2 - q2 * t1;
        if (b == 0) return {s2, t2};
        q2 = a / b;
        r = a % b;
    }
}

i64 gcd(i64 a, i64 b)
{
    while (b != 0)
    {
        i64 r = a % b;
        a = b, b = r;
    }

    return a;
}