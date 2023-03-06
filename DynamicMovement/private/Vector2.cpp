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

Vector2::Vector2(const Vector2* in)
{
    x = in->x;
    z = in->z;
}

Vector2::Vector2(const double x_in, const double z_in)
{
    x = x_in;
    z = z_in;
}

void Vector2::setPoint(const Vector2* VM)
{
    x = VM->x;
    z = VM->z;
}

void Vector2::setPoint(const Vector2& v)
{
    x = v.x;
    z = v.z;
}

double Vector2::vector_length() const
{
    return sqrt(pow(x, 2) + pow(z, 2));
}

double Vector2::vector_length(const Vector2& v)
{
    return sqrt(pow(v.x, 2) + pow(v.z, 2));
}

Vector2* Vector2::vector_normalize() const
{
    if(vector_length() != 0.0)
    {
        return new Vector2(x / vector_length(), z / vector_length());
    }
    return new Vector2(0, 0);
}

Vector2* Vector2::vector_normalize(const Vector2* v)
{
    if(vector_length(*v) != 0.0)
    {
        return new Vector2(v->x/ vector_length(*v), v->z / vector_length(*v));
    }
    return new Vector2(0, 0);
}

double Vector2::vectorDot(Vector2 p1, Vector2 p2)
{
    return p1.x * p2.x + p1.z * p2.z;
    
}

double Vector2::distancePointPoint(const Vector2* A, const Vector2* B)  // Working
{
    return sqrt( pow((B->x - A->x), 2) + pow((B->z - A->z), 2) );
}

std::vector<unsigned int> Vector2::which(double param, const std::vector<double>& pathParam)
{
    std::vector<unsigned int> r_vector; 
    for(unsigned int i = 0; i < pathParam.size(); i++)
    {
        if(param > pathParam[i])
            r_vector.push_back(i);
    }
    return r_vector;
}

double Vector2::min(double f_n, double s_n)
{
    if(f_n < s_n)
        return f_n;
    return s_n;
}

double Vector2::max(const double smallest, const std::vector<double>* in_search)
{
    double largest = smallest;
    for(const double i : *in_search)
    {
        if(i > largest)
            largest = i;
    }
    return largest;
}

unsigned int Vector2::max(const unsigned int smallest, const std::vector<unsigned int>& in_search)
{
    unsigned int largest = smallest;
    for(const unsigned int i : in_search)
    {
        if(i > largest)
            largest = i;
    }
    return largest;
}

Vector2 Vector2::operator-(const Vector2& right) const
{
    Vector2 T(this->x - right.x, this->z - right.z);
    return T;
}

Vector2 Vector2::operator-(const double& right) const
{
    Vector2 T(this->x - right, this->z - right);
    return T;
}

Vector2 Vector2::operator+(const Vector2& right) const
{
    Vector2 T(this->x + right.x, this->z + right.z);
    return T;
}

Vector2 Vector2::operator+(const double& right) const
{
    Vector2 T(this->x + right, this->z + right);
    return  T;
}

Vector2 Vector2::operator*(const Vector2& right) const
{
    Vector2 T(this->x * right.x, this->z * right.z);
    return T;
}

Vector2 Vector2::operator*(const double& right) const
{
    Vector2 T(this->x * right, this->z * right);
    return T;
}

Vector2 Vector2::operator/(const Vector2& right) const
{
    Vector2 T(this->x / right.x, this->z / right.z);
    return T;
}

Vector2 Vector2::operator/(const double& right) const
{
    Vector2 T(this->x / right, this->z / right);
    return T;
}

Vector2& Vector2::operator=(const Vector2& right)
{
    this->x = right.x;
    this->z = right.z;
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

void Vector2::printVector() const
{
    std::cout << "X is " << x << ". | Z is " << z << "." << std::endl;
}