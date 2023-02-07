/****************************************
*
 * Author: Tony A. Hardiman Jr.
 * Assignment: Programming Assignment 1
 * Declaration: This program is entirely my own work.
 *
 ***************************************/

#include "VectorMath.h"
#include <cmath>
#include <iostream>

VectorMath::VectorMath()
{
    x = 0.0;
    z = 0.0;
}

VectorMath::VectorMath(const double x_in, const double z_in)
{
    x = x_in;
    z = z_in;
}

VectorMath::VectorMath(double axis[])
{
    x = axis[0];
    z = axis[1];
}

double VectorMath::vector_length()
{
    return sqrt(pow(x, 2) + pow(z, 2));
}

VectorMath* VectorMath::vector_normalize()
{
    if(vector_length() != 0.0)
    {
        return new VectorMath(x / vector_length(), z / vector_length());
    }
    return new VectorMath(0, 0);
}

void VectorMath::AddVector(const VectorMath* n)
{
    if(!n) return;
    x += n->x;
    z += n->z;
}

void VectorMath::SubtractVector(const VectorMath* n)
{
    if(!n) return;
    x -= n->x;
    z -= n->z;
}

void VectorMath::SubtractVector(const VectorMath* v, const VectorMath* n)
{
    if(!n || !v) return;
    x = v->x - n->x;
    z = v->z - n->z;
}

void VectorMath::MultiplyDouble(double incoming)
{
    x *= incoming;
    z *= incoming;
}

void VectorMath::DivideDouble(double incoming)
{
    x /= incoming;
    z /= incoming;
}

VectorMath* VectorMath::Clone()
{
    return new VectorMath(x, z);
}