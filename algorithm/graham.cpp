#include <iostream>
#include <algorithm>
#include <cmath>
#include <stack>
#include <stdlib.h>

const int N = 1e5 + 5;

int n, top;
int st[N];

struct Point
{
    double x;
    double y;
    double ang;

    Point operator-(const Point &p) const { return {x - p.x, y - p.y}; }
} p[N];

double dis(Point p1, Point p2)
{
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

bool cmp(Point p1, Point p2)
{
    if (p1.ang == p2.ang)
    {
        return dis(p1, p[1]) < dis(p2, p[1]);
    }
    return p1.ang < p2.ang;
}

double cross(Point p1, Point p2)
{
    return p1.x * p2.y - p1.y * p2.x;
}

void Graham()
{
    std::sort(p + 1, p + n + 1, cmp);

    for (int i = 2; i <= n; i++)
    {
        if (p[i].y < p[1].y || (p[i].y == p[1].y && p[i].x < p[1].x))
            std::swap(p[1], p[i]);
    }

    for (int i = 2; i <= n; i++)
        p[i].ang = atan2(p[i].y - p[1].y, p[i].x - p[1].x);

    std::sort(p + 2, p + n + 1, cmp);
    st[++top] = 1;
    for (int i = 2; i <= n; i++)
    {
        while (top >= 2 && cross(p[st[top]] - p[st[top - 1]], p[i] - p[st[top]]) < 0)
            top--;
        st[++top] = i;
    }
}

int main()
{
    std::cin >> n;
    for (int i = 1; i <= n; i++)
        std::cin >> p[i].x >> p[i].y;

    Graham();

    for (int i = 1; i <= top; i++)
        std::cout << i << " : " << p[st[i]].x << " , " << p[st[i]].y << std::endl;

    system("pause");

    return 0;
}