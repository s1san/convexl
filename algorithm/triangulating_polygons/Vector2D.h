#ifndef VECTOR_2D_H
#define VECTOR_2D_H

#include <cmath>
#include <vector>

struct Vector2D
{
    double x;
    double y;

    Vector2D(double _x, double _y) : x(_x), y(_y) {}

    Vector2D operator+(const Vector2D &other) const
    {
        return {x + other.x, y + other.y};
    }

    Vector2D operator-(const Vector2D &other) const
    {
        return {x - other.x, y - other.y};
    }
};

double dot(const Vector2D &v1, const Vector2D &v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

double cross(const Vector2D &v1, const Vector2D &v2)
{
    return v1.x * v2.y - v1.y * v2.x;
}

double magnitude(const Vector2D &v)
{
    return std::sqrt(v.x * v.x + v.y * v.y);
}

double distance(const Vector2D &v1, const Vector2D &v2)
{
    return magnitude(v1 - v2);
}

using vec2 = Vector2D;

#endif // VECTOR_2D_H
