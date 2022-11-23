#pragma once
#include <math.h>

#define PI 3.141592

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

        Vector2(float x, float y)
        {
            this->x = x;
            this->y = y;
        }

        Vector2(const Vector2& other) = default;
        Vector2() = default;
        ~Vector2() = default;

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

    namespace math
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
        {
            return v1.x * v2.x + v1.y * v2.y;
        }

        inline float Cross(Vector2 v1, Vector2 v2)
        {
            return v1.x * v2.y - v1.y * v2.x;
        }
    };
}
