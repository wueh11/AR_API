#pragma once
#define PI 3.14159265f

#include <cmath>
#include <algorithm>

namespace ya
{
    struct Vector2
    {
        static Vector2 Zero;
        static Vector2 One;
        static Vector2 Right;
        static Vector2 Left;
        static Vector2 Up;
        static Vector2 Down;

        float x;
        float y;

        Vector2() = default;
        ~Vector2() = default;

        Vector2(const Vector2&) = default;
        Vector2& operator=(const Vector2&) = default;

        Vector2(Vector2&&) = default;
        Vector2& operator=(Vector2&&) = default;

        Vector2 operator-()
        {
            return Vector2(-x, -y);
        }

        bool operator==(const Vector2& other)
        {
            return x == other.x && y == other.y;
        }

        bool operator!=(const Vector2& other)
        {
            return x != other.x || y != other.y;
        }

        Vector2& operator +=(const Vector2& other)
        {
            x += other.x;
            y += other.y;

            return *this;
        }

        Vector2& operator -=(const Vector2& other)
        {
            x -= other.x;
            y -= other.y;

            return *this;
        }

        Vector2& operator *=(const float value)
        {
            x *= value;
            y *= value;

            return *this;
        }

        Vector2& operator +=(const float value)
        {
            x += value;
            y += value;

            return *this;
        }

        Vector2 operator +(const Vector2& other)
        {
            Vector2 temp;
            temp.x = x + other.x;
            temp.y = y + other.y;

            return temp;
        }

        Vector2 operator -(const Vector2& other)
        {
            Vector2 temp;
            temp.x = x - other.x;
            temp.y = y - other.y;

            return temp;
        }

        Vector2 operator *(const Vector2& other)
        {
            Vector2 temp;
            temp.x = x * other.x;
            temp.y = y * other.y;

            return temp;
        }

        Vector2 operator*(const float& value)
        {
            Vector2 temp;
            temp.x = x * value;
            temp.y = y * value;

            return temp;
        }

        Vector2 operator /(const float value)
        {
            Vector2 temp;
            temp.x = x / value;
            temp.y = y / value;

            return temp;
        }

        constexpr Vector2(float _x, float _y) noexcept
            : x(_x)
            , y(_y)
        {

        }
        explicit Vector2(_In_reads_(2) const float* pArray)  noexcept
            : x(pArray[0])
            , y(pArray[1])
        {

        }

        float Length()
        {
            return sqrtf(x * x + y * y);
        }

        Vector2& Normalize()
        {
            float length = Length();
            x /= length;
            y /= length;

            return *this;
        }

        void Clear()
        {
            x = 0.0f;
            y = 0.0f;
        }
    };
    typedef Vector2 Pos;
    typedef Vector2 Size;
}

namespace ya::math
{
    /* x도 = x * π / 180라디안
    x라디안 = x * 180 / π도*/
    inline float DegreeToRadian(float degree)
    {
        return degree * PI / 180.0f;
    }

    inline float RadianToDegree(float radian)
    {
        return radian * (180.0f / PI);
    }

    inline Vector2 Rotate(const Vector2 v, float degree)
    {
        Vector2 ret = Vector2::Zero;
        float radian = DegreeToRadian(degree);
        ret.x = v.x * cosf(radian) - v.y * sinf(radian);
        ret.y = v.x * sinf(radian) + v.y * cosf(radian);

        return ret;
    }

    inline float Dot(Vector2& v1, Vector2& v2)
    { /// 내적
        return v1.x * v2.x + v1.y * v2.y;
    }

    inline float Cross(Vector2 v1, Vector2 v2)
    {
        return v1.x * v2.y - v1.y * v2.x;
    }

    inline float lerp(float p1, float p2, float t)
    { /// 선형보간법
        return (1 - t) * p1 + t * p2;
    }

    inline Vector2 lerpv(Vector2 v1, Vector2 v2, float t)
    {
        Vector2 temp;
        temp.x = lerp(v1.x, v2.x, t);
        temp.y = lerp(v1.y, v2.y, t);

        return temp;
    }

    inline int Random(int max, int min = 0)
    {
        return rand() % ((max - min) + min + 1);
    }
}