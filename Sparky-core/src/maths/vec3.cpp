#include "vec3.h"

using namespace sparky;
using namespace maths;

sparky::maths::vec3::vec3()
{
    x = y = z = 0.0f;
}

sparky::maths::vec3::vec3(const float& x, const float& y, const float& z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

vec3 & sparky::maths::vec3::add(const vec3 & other)
{
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

vec3 & sparky::maths::vec3::subtract(const vec3 & other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

vec3 & sparky::maths::vec3::multiply(const vec3 & other)
{
    x *= other.x;
    y *= other.y;
    z *= other.z;
    return *this;
}

vec3 & sparky::maths::vec3::divide(const vec3 & other)
{
    x /= other.x;
    y /= other.y;
    z /= other.z;
    return *this;
}

bool sparky::maths::vec3::equals(const vec3 & other)
{
    return this->x == other.x && this->y == other.y && this->z == other.z;
}

vec3 & sparky::maths::vec3::operator+=(const vec3 & other)
{
    return add(other);
}

vec3 & sparky::maths::vec3::operator-=(const vec3 & other)
{
    return subtract(other);
}

vec3 & sparky::maths::vec3::operator*=(const vec3 & other)
{
    return multiply(other);
}

vec3 & sparky::maths::vec3::operator/=(const vec3 & other)
{
    return divide(other);
}

bool sparky::maths::vec3::operator==(const vec3 & other)
{
    return equals(other);
}

bool sparky::maths::vec3::operator!=(const vec3 & other)
{
    return !equals(other);
}

std::ostream & sparky::maths::operator<<(std::ostream & stream, vec3 & vector)
{
    stream << "Vec3(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
    return stream;
}


vec3 sparky::maths::operator+(vec3 left, const vec3& right)
{
    return left.add(right);

}

vec3 sparky::maths::operator-(vec3 left, const vec3& right)
{
    return left.subtract(right);
}

vec3 sparky::maths::operator*(vec3 left, const vec3& right)
{
    return left.multiply(right);
}

vec3 sparky::maths::operator/(vec3 left, const vec3& right)
{
    return left.divide(right);
}

