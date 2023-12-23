#include <iostream>
#include <cstdlib>

#include "Vector2D.h"

bool collision(vec2 v1, vec2 v2, vec2 v3, vec2 point)
{
    vec2 v12 = v2 - v1;
    vec2 v23 = v3 - v2;
    vec2 v31 = v1 - v3;

    if (cross(v12, point - v1) > 0 && cross(v23, point - v2) > 0 && cross(v31, point - v3) > 0)
        return true;

    return false;
}

std::vector<vec2> triangulate(std::vector<vec2> points)
{
    std::vector<vec2> triangles;
    std::vector<vec2> origins = points;

    if (points.size() < 3)
        return triangles;

    bool found = true;

    while (points.size() != 0)
    {
        if (!found)
            return triangles;

        found = false;

        for (int i = 0; i < points.size() - 2; i++)
        {
            if (!found)
            {
                bool ret = false;
                if (cross(points[i + 1] - points[i], points[i + 2] - points[i + 1]) < 0)
                {
                    ret = true;
                    for (int j = 0; j < origins.size(); j++)
                    {
                        if (collision(points[i + 2], points[i + 1], points[i], origins[j]))
                            ret = false;
                    }
                }

                if (ret)
                {
                    found = true;

                    triangles.push_back(points[i]);
                    triangles.push_back(points[i + 1]);
                    triangles.push_back(points[i + 2]);

                    std::vector<vec2> temp;
                    for (int j = 0; j < points.size(); j++)
                    {
                        if (j != i + 1)
                            temp.push_back(points[j]);
                    }
                    points = temp;
                }
            }
        }
    }

    return triangles;
}

int main()
{
    std::vector<vec2> polygon;
    polygon.push_back({1, 1});
    polygon.push_back({1, 0});
    polygon.push_back({0, 1});
    polygon.push_back({0, 0});

    std::vector<vec2> points = triangulate(polygon);

    std::cout << points.size() << std::endl;

    for (int i = 0, cnt = 1; i < points.size(); i += 3, cnt++)
    {
        std::cout << cnt << ": (" << points[i].x << ", " << points[i].y << ")"
                  << "  (" << points[i + 1].x << ", " << points[i + 1].y << ")"
                  << "  (" << points[i + 2].x << ", " << points[i + 2].y << ")"
                  << std::endl;
    }

    system("pause");

    return 0;
}