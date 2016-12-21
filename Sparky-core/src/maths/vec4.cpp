#include "vec4.h"
#include "maths.h"

using namespace sparky;
using namespace maths;

sparky::maths::vec4::vec4(const float& x, const float& y, const float& z, const float& w)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

vec4 & sparky::maths::vec4::add(const vec4 & other)
{
    x += other.x;
    y += other.y;
    z += other.z;
    w += other.w;
    return *this;
}

vec4 & sparky::maths::vec4::subtract(const vec4 & other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
    w -= other.w;
    return *this;
}

vec4 & sparky::maths::vec4::multiply(const vec4 & other)
{
    x *= other.x;
    y *= other.y;
    z *= other.z;
    w *= other.w;
    return *this;
}

vec4 & sparky::maths::vec4::divide(const vec4 & other)
{
    x /= other.x;
    y /= other.y;
    z /= other.z;
    w /= other.w;
    return *this;
}

bool sparky::maths::vec4::equals(const vec4 & other)
{
    return this->x == other.x && this->y == other.y&& this->z == other.z&& this->w == other.w;
}

vec4 & sparky::maths::vec4::operator+=(const vec4 & other)
{
    return add(other);
}

vec4 & sparky::maths::vec4::operator-=(const vec4 & other)
{
    return subtract(other);
}

vec4 & sparky::maths::vec4::operator*=(const vec4 & other)
{
    return multiply(other);
}

vec4 & sparky::maths::vec4::operator/=(const vec4 & other)
{
    return divide(other);
}

bool sparky::maths::vec4::operator==(const vec4 & other)
{
    return equals(other);
}

bool sparky::maths::vec4::operator!=(const vec4 & other)
{
    return !equals(other);
}

std::ostream & sparky::maths::operator<<(std::ostream & stream, vec4 & vector)
{
    stream << "Vec4(" << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << ")";
    return stream;
}


vec4 sparky::maths::operator+(vec4 left, const vec4& right)
{
    return left.add(right);

}

vec4 sparky::maths::operator-(vec4 left, const vec4& right)
{
    return left.subtract(right);
}

vec4 sparky::maths::operator*(vec4 left, const vec4& right)
{
    return left.multiply(right);
}

vec4 sparky::maths::operator/(vec4 left, const vec4& right)
{
    return left.divide(right);
}

