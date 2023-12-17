#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <cstring>
#include <vector>
#include <queue>
#include <map>

#define EPSILON 1e-4
#define UP 0
#define BOTTOM 1
#define INTERSECTION 2

struct Point
{
    double x;
    double y;
    struct Segment *belong1;
    struct Segment *belong2;
    int index;

    Point(double _x = 0., double _y = 0., Segment *s1 = nullptr, Segment *s2 = nullptr, int idx = 0) : x(_x), y(_y), belong1(s1), belong2(s2), index(idx){};
    static bool cmp(Point *p1, Point *p2)
    {
        return p1->y < p2->y;
    }
};

struct Segment
{
    Point *first;
    Point *second;
};

std::priority_queue<Point *, std::vector<Point *>, decltype(&Point::cmp)> pq(&Point::cmp);

std::map<double, Segment *> Curline;
std::vector<Segment *> segment;
std::vector<Point *> intersect_point;

bool IsSamePoint(Point *p1, Point *p2)
{
    if (fabs(p1->x - p2->x) < EPSILON && fabs(p1->y - p2->y) < EPSILON)
        return true;
    return false;
}

bool IsNewPoint(Point *)
{
    return 1;
}