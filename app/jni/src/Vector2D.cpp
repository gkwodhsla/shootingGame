#include "Vector2D.h"
#include <cmath>
Vector2D operator+(const Vector2D& lhs, const Vector2D& rhs)
{
    return Vector2D(lhs.x + rhs.x, lhs.y + rhs.y);
}

Vector2D operator-(const Vector2D& lhs, const Vector2D& rhs)
{
    return Vector2D(lhs.x - rhs.x, lhs.y - rhs.y);
}


Vector2D::Vector2D(float x, float y):x(x), y(y)
{

}

Vector2D::Vector2D(const Vector2D &rhs)
{
    x = rhs.x;
    y = rhs.y;
}

Vector2D::Vector2D(Vector2D&& rhs) noexcept
{
    x = rhs.x;
    y = rhs.y;
}

void Vector2D::normalize()
{
    float len = getLength();
    if(len != 0.0f)
    {
        x /= len;
        y /= len;
    }
}

float Vector2D::getLength()
{
    return sqrtf(x*x + y*y);
}

float Vector2D::innerProduct(const Vector2D &rhs)
{
    return (x * rhs.x) + (y * rhs.y);
}

float Vector2D::outerProduct(const Vector2D &rhs)
{
    return (x * rhs.y) - (y * rhs.x);
}

void Vector2D::rotateVector(float degree)
{
    float radian = degree * (3.14f/180.0f);
    float cosValue = cos(radian);
    float sinValue = sin(radian);

    float newX = (x * cosValue) - (y * sinValue);
    float newY = (x * sinValue) + (y * cosValue);

    x = newX;
    y = newY;
}

Vector2D& Vector2D::operator=(const Vector2D &rhs)
{
    if(this == &rhs)
    {
        return *this;
    }
    x = rhs.x;
    y = rhs.y;
    return *this;
}

Vector2D& Vector2D::operator=(Vector2D&& rhs) noexcept
{
    if(this == &rhs)
    {
        return *this;
    }
    x = rhs.x;
    y = rhs.y;
    return *this;
}