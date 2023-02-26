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
    tempObject = false;
}

Vector2::Vector2(const double x_in, const double z_in)
{
    x = x_in;
    z = z_in;
    tempObject = false;
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

Vector2* Vector2::vector_normalize()
{
    if(vector_length() != 0.0)
    {
        return new Vector2(x / vector_length(), z / vector_length());
    }
    return new Vector2(0, 0);
}

void Vector2::MultiplyVector(Vector2* v)
{
    x *= v->x;
    z *= v->z;
}

Vector2* Vector2::min(Vector2* param, double charOffset)
{
    Vector2* temp = new Vector2(0.0, 0.0);
    double x_test = param->x + charOffset;
    double z_test = param->z + charOffset;
    double new_x =  fmin(1, x_test);
    double new_z = fmin(1, z_test);
    temp->x = new_x;
    temp->z = new_z;
    return temp;
}

int Vector2::which(Vector2* param, std::vector<Vector2*> pathParam)
{
    for(unsigned int i = 0; i < pathParam.size(); i++)
    {
        if(fabs(param->x - pathParam[i]->x) < DBL_EPSILON && fabs(param->z - pathParam[i]->z) < DBL_EPSILON)
            return static_cast<int>(i);
    }
    return 0;
}

double Vector2::vectorDot(Vector2 p1, Vector2 p2)
{
    return (p1.x * p2.x) + (p1.z * p2.z);
}

double Vector2::distancePointPoint(const Vector2* A, const Vector2* B)
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