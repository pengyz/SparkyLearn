#include "vec2.h"

using namespace sparky;
using namespace maths;

sparky::maths::Vec2::Vec2()
{
    x = y = 0.0f;
}

sparky::maths::Vec2::Vec2(const float& x, const float& y)
{
    this->x = x;
    this->y = y;
}

Vec2 & sparky::maths::Vec2::add(const Vec2 & other)
{
    x += other.x;
    y += other.y;
    return *this;
}

Vec2 & sparky::maths::Vec2::subtract(const Vec2 & other)
{
    x -= other.x;
    y -= other.y;
    return *this;
}

Vec2 & sparky::maths::Vec2::multiply(const Vec2 & other)
{
    x *= other.x;
    y *= other.y;
    return *this;
}

Vec2 & sparky::maths::Vec2::divide(const Vec2 & other)
{
    x /= other.x;
    y /= other.y;
    return *this;
}

bool sparky::maths::Vec2::equals(const Vec2 & other)
{
    return this->x == other.x && this->y == other.y;
}

Vec2 & sparky::maths::Vec2::operator+=(const Vec2 & other)
{
    return add(other);
}

Vec2 & sparky::maths::Vec2::operator-=(const Vec2 & other)
{
    return subtract(other);
}

Vec2 & sparky::maths::Vec2::operator*=(const Vec2 & other)
{
    return multiply(other);
}

Vec2 & sparky::maths::Vec2::operator/=(const Vec2 & other)
{
    return divide(other);
}

bool sparky::maths::Vec2::operator==(const Vec2 & other)
{
    return equals(other);
}

bool sparky::maths::Vec2::operator!=(const Vec2 & other)
{
    return !equals(other);
}

std::ostream & sparky::maths::operator<<(std::ostream & stream, Vec2 & vector)
{
    stream << "vec2(" << vector.x << ", " << vector.y << ")";
    return stream;
}


Vec2 sparky::maths::operator+(Vec2 left, const Vec2& right)
{
    return left.add(right);

}

Vec2 sparky::maths::operator-(Vec2 left, const Vec2& right)
{
    return left.subtract(right);
}

Vec2 sparky::maths::operator*(Vec2 left, const Vec2& right)
{
    return left.multiply(right);
}

Vec2 sparky::maths::operator/(Vec2 left, const Vec2& right)
{
    return left.divide(right);
}

