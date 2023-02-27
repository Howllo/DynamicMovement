/****************************************
 *
 * Author: Tony A. Hardiman Jr.
 * Assignment: Programming Assignment 1
 * Declaration: This program is entirely my own work.
 *
 ***************************************/

#include "Vector2.h"
#include <cmath>
#include <iostream>
#include "PathAlgorithm.h"

Vector2::Vector2(Vector2* v)
{
    x = v->x;
    z = v->z;
}

Vector2::Vector2(const double x_in, const double z_in)
{
    x = x_in;
    z = z_in;
}

void Vector2::setPoint(Vector2* VM)
{
    x = VM->x;
    z = VM->z;
}

double Vector2::vector_length()
{
    return sqrt(pow(x, 2) + pow(z, 2));
}

double Vector2::vector_length(const Vector2& v)
{
    return sqrt(pow(v.x, 2) + pow(v.z, 2));
}

Vector2* Vector2::vector_normalize()
{
    if(vector_length() != 0.0)
    {
        return new Vector2(x / vector_length(), z / vector_length());
    }
    return new Vector2(0, 0);
}

unsigned int Vector2::which(double param, const std::vector<double>& pathParam)
{
    for(unsigned int i = 0; i < pathParam.size(); i++)
    {
        if(param > pathParam[i])
            return i;
    }
    return 0;
}

double Vector2::vectorDot(Vector2 p1, Vector2 p2)
{
    return (p1.x * p2.x) + (p1.z * p2.z);
}

double Vector2::distancePointPoint(const Vector2* A, const Vector2* B)  // Working
{
    return sqrt( pow((B->x - A->x), 2) + pow((B->z - A->z), 2) );
}

Vector2 Vector2::operator-(const Vector2& right) const
{
    Vector2 T(this->x - right.x, this->x - right.z);
    return T;
}

Vector2 Vector2::operator-(const double& right) const
{
    Vector2 T(this->x - right, this->z - right);
    return T;
}

Vector2 Vector2::operator+(const Vector2& right) const
{
    Vector2 T(this->x + right.x, this->x + right.z);
    return T;
}

Vector2 Vector2::operator+(const double& right) const
{
    Vector2 T(this->x + right, this->z + right);
    return  T;
}

Vector2 Vector2::operator*(const Vector2& right) const
{
    Vector2 T(this->x * right.x, this->x * right.z);
    return T;
}

Vector2 Vector2::operator*(const double& right) const
{
    Vector2 T(this->x * right, this->x * right);
    return T;
}

Vector2 Vector2::operator/(const Vector2& right) const
{
    Vector2 T(this->x / right.x, this->x / right.z);
    return T;
}

Vector2 Vector2::operator/(const double& right) const
{
    Vector2 T(this->x / right, this->x / right);
    return T;
}

Vector2& Vector2::operator=(const Vector2& right)
{
    this->x = right.x;
    this->z = right.x;
    return *this;
}

Vector2& Vector2::operator+=(const Vector2& right)
{
    x *= right.x;
    z *= right.z;
    return *this;
}

Vector2& Vector2::operator+=(const double& right)
{
    x += right;
    z += right;
    return *this;
}

Vector2& Vector2::operator*=(const Vector2& right)
{
    x *= right.x;
    z *= right.z;
    return *this;
}

Vector2& Vector2::operator*=(const double& right)
{
    x *= right;
    z *= right;
    return *this;
}

Vector2& Vector2::operator/=(const Vector2& right)
{
    x /= right.x;
    z /= right.z;
    return *this;
}

Vector2& Vector2::operator/=(const double& right)
{
    x /= right;
    z /= right;
    return *this;
}

bool Vector2::operator==(const Vector2& right) const
{
    if(fabs(this->x - right.x)  < DBL_EPSILON && fabs(this->z - right.z) < DBL_EPSILON)
        return true;
    return false;
}

void Vector2::printVector()
{
    std::cout << "X is " << x << " Z is " << z << std::endl;
}