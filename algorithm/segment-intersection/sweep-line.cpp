#include <iostream>
#include "primitive.h"

Point *intersect(Segment *s1, Segment *s2)
{
    double x1 = s1->first->x, y1 = s1->first->y;
    double x2 = s1->second->x, y2 = s1->second->y;
    double x3 = s2->first->x, y3 = s2->first->y;
    double x4 = s2->second->x, y4 = s2->second->y;

    double det = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);

    if (fabs(det) < EPSILON)
        return nullptr;

    double x = ((x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4)) / det;
    double y = ((x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4)) / det;

    if (!(x < std::min(x1, x2) - EPSILON || x > std::max(x1, x2) + EPSILON ||
          x < std::min(x3, x4) - EPSILON || x > std::max(x3, x4) + EPSILON ||
          y < std::min(y1, y2) - EPSILON || y > std::max(y1, y2) + EPSILON ||
          y < std::min(y3, y4) - EPSILON || y > std::max(y3, y4) + EPSILON))
    {
        if (s1->first->x < s2->first->x)
            return new Point(x, y, s1, s2, 2);
        else
            return new Point(x, y, s2, s1, 2);
    }

    return nullptr;
}

void GetRandomSegment(int num)
{
    srand(time(0));
    int count = 1;
    for (int i = 0; i < num; i++)
    {
        Segment *temp = new Segment();
        Point *p1 = new Point(100 * (double)rand() / (double)RAND_MAX, 100 * rand() / (double)RAND_MAX);
        Point *p2 = new Point(100 * (double)rand() / (double)RAND_MAX, 100 * rand() / (double)RAND_MAX);
        p1->belong1 = temp;
        p2->belong1 = temp;
        if (p1->y > p2->y)
        {
            temp->first = p1;
            temp->second = p2;
            p2->index = BOTTOM;
        }
        else
        {
            temp->first = p2;
            temp->second = p1;
            p1->index = BOTTOM;
        }
        segment.push_back(temp);

        std::cout << count << " ";
        std::cout << p1->x << " " << p1->y << " ";
        std::cout << std::endl;
        count++;
        std::cout << count << " ";
        std::cout << p2->x << " " << p2->y << " ";
        std::cout << std::endl;
        count++;
    }
}

void HandleEvent(Point *event)
{
    if (event->index == INTERSECTION)
    {
        if (!intersect_point.empty() && IsSamePoint(event, intersect_point.back()))
            return;

        intersect_point.push_back(event);
        auto segment1 = event->belong1;
        auto segment2 = event->belong2;
        auto it1 = Curline.find(segment1->first->x);
        auto it2 = Curline.find(segment2->first->x);

        if (it1 != Curline.begin())
        {
            auto it3 = --it1;
            it1++;
            auto segment = intersect(it2->second, it3->second);

            if (segment && segment->y < event->y)
            {
                pq.push(segment);
            }
        }

        if (++it2 != Curline.end())
        {
            auto it4 = it2;
            it2--;
            auto segment = intersect(it1->second, it4->second);

            if (segment && segment->y < event->y)
                pq.push(segment);
        }
        else
            it2--;

        Curline.erase(it1);
        Curline.erase(it2);

        segment1->first->y = event->y;
        segment2->first->y = event->y;
        segment1->first->x = event->x + EPSILON;
        segment2->first->x = event->x - EPSILON;
        Curline[segment1->first->x] = segment1;
        Curline[segment2->first->x] = segment2;
    }
    else if (event->index == UP)
    {
        Curline[event->x] = event->belong1;

        auto it = Curline.find(event->x);
        decltype(it) left, right;

        if (++it == Curline.end())
        {
            it--;
        }
        else
        {
            right = it;
            it--;
            auto pt = intersect(right->second, it->second);

            if (pt)
                pq.push(pt);
        }

        if (it == Curline.begin())
        {
            // Do nothing
        }
        else
        {
            left = --it;
            it++;
            auto pt = intersect(left->second, it->second);

            if (pt)
                pq.push(pt);
        }
    }
    else
    {
        auto it = Curline.find(event->belong1->first->x);
        decltype(it) left, right;

        if (++it == Curline.end())
        {
            Curline.erase(--it);
            return;
        }
        else
        {
            right = it;
            it--;
        }

        if (it == Curline.begin())
        {
            Curline.erase(it);
            return;
        }
        else
        {
            left = --it;
            it++;
        }

        Curline.erase(it);
        auto pt = intersect(left->second, right->second);

        if (pt && pt->y < event->y)
        {
            pq.push(pt);
        }
    }
}

void FindIntersection()
{
    for (auto l : segment)
    {
        pq.push(l->first);
        pq.push(l->second);
    }

    while (!pq.empty())
    {
        auto temp = pq.top();
        pq.pop();
        HandleEvent(temp);
    }
    int cnt = 1;
    std::cout << "Output:" << std::endl;
    for (auto p : intersect_point)
    {
        std::cout << cnt << " " << p->x << " " << p->y << std::endl;
        cnt++;
    }
}

int main()
{
    GetRandomSegment(20);
    FindIntersection();

    system("pause");
}
