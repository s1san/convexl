#include <iostream>
#include <algorithm>
#include <cmath>
#include <stdlib.h>

const int N = 1e5 + 5;

int n, cnt;

struct Point
{
    double x;
    double y;
} p[N], ch[N];

double dis(Point a, Point b)
{
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double cross(Point a, Point b, Point c)
{
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

bool cmp(Point a, Point b)
{
    return a.x != b.x ? a.x < b.x : a.y < b.y;
}

void Andrew()
{
    std::sort(p + 1, p + n + 1, cmp);

    for (int i = 1; i <= n; i++)
    {
        while (cnt > 1 && cross(ch[cnt - 1], ch[cnt], p[i]) <= 0)
            cnt--;
        ch[++cnt] = p[i];
    }

    int t = cnt;
    for (int i = n - 1; i >= 1; i--)
    {
        while (cnt > t && cross(ch[cnt - 1], ch[cnt], p[i]) <= 0)
            cnt--;
        ch[++cnt] = p[i];
    }
}

int main()
{
    std::cin >> n;
    for (int i = 1; i <= n; i++)
        std::cin >> p[i].x >> p[i].y;

    Andrew();

    for (int i = 1; i < cnt; i++)
        std::cout << i << " : " << ch[i].x << " , " << ch[i].y << std::endl;

    system("pause");

    return 0;
}