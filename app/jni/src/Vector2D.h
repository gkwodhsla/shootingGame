#pragma once


class Vector2D
{
public:
    Vector2D() = default;
    Vector2D(float x, float y);
    Vector2D(const Vector2D& rhs);
    virtual ~Vector2D() = default;

    void normalize();
    float getLength();

    float innerProduct(const Vector2D& rhs);
    float outerProduct(const Vector2D& rhs);
    void rotateVector(float degree);

    Vector2D& operator=(const Vector2D& rhs);
    friend Vector2D operator+(const Vector2D& lhs, const Vector2D& rhs);
    friend Vector2D operator-(const Vector2D& lhs, const Vector2D& rhs);

public:
    float x = 0.0f;
    float y = 0.0f;
};

Vector2D operator+(const Vector2D& lhs, const Vector2D& rhs);
Vector2D operator-(const Vector2D& lhs, const Vector2D& rhs);