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
#include "PathAlgorithm.h"
#include <cfloat>

VectorMath::VectorMath()
{
    x = 0.0;
    z = 0.0;
    tempObject = false;
}

VectorMath::VectorMath(const double x_in, const double z_in)
{
    x = x_in;
    z = z_in;
    tempObject = false;
}

void VectorMath::setPoints(VectorMath* VM)
{
    x = VM->x;
    z = VM->z;
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

VectorMath* VectorMath::AddTwoVectors(const VectorMath* v, const VectorMath* n)
{
    if(!v || !n) return nullptr;
    VectorMath* temp = new VectorMath();
    
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

VectorMath* VectorMath::SubtractVectors(const VectorMath* v, const VectorMath* n)
{
    auto* temp = new VectorMath();
    if(!n || !v) return nullptr;
    temp->x = v->x - n->x;
    temp->z = v->z - n->z;
    return temp;
}

VectorMath* VectorMath::SubtractVectors(const VectorMath* v, const VectorMath n)
{
    auto* temp = new VectorMath();
    if(!v) return nullptr;
    temp->x = v->x - n.x;
    temp->z = v->z - n.z;
    return temp;
}

VectorMath* VectorMath::SubtractVectors(const VectorMath& v, const VectorMath& n)
{
    auto* temp = new VectorMath();
    temp->x = v.x - n.x;
    temp->z = v.z - n.z;
    return temp;
}

void VectorMath::MultiplyDouble(double incoming)
{
    x *= incoming;
    z *= incoming;
}

void VectorMath::MultiplyVector(VectorMath* v)
{
    x *= v->x;
    z *= v->z;
}

void VectorMath::DivideDouble(double incoming)
{
    x /= incoming;
    z /= incoming;
}

VectorMath* VectorMath::DivideVectors(VectorMath* v, VectorMath* n, bool deleteObjects)
{
    VectorMath* T = new VectorMath();
    T->x = v->x / n->x;
    T->z = v->z / n->z;
    if(deleteObjects)
    {
        delete v;
        delete n;
    }
    return T;
}

VectorMath* VectorMath::min(VectorMath* param, double charOffset)
{
    VectorMath* temp = new VectorMath();
    double x_test = param->x + charOffset;
    double z_test = param->z + charOffset;
    double new_x =  fmin(1, x_test);
    double new_z = fmin(1, z_test);
    temp->x = new_x;
    temp->z = new_z;
    return temp;
}

int VectorMath::which(VectorMath* param, std::vector<VectorMath*> pathParam)
{
    for(int i = 0; i < pathParam.size(); i++)
    {
        if(param->x == pathParam[i]->x && param->z == pathParam[i]->z)
            return i;
    }
    return 0;
}

double VectorMath::vectorDot(VectorMath* p1, VectorMath* p2, bool deleteObjects)
{
    const double T = (p1->x * p2->x) + (p1->z * p2->z);
    if(deleteObjects)
    {
        delete p1;
        delete p2;
    }
    return T;
}

double VectorMath::distancePointPoint(const VectorMath* A, const VectorMath* B)
{
    return sqrt( pow((B->x - A->x), 2) + pow((B->z - A->z), 2) );
}

VectorMath* VectorMath::Clone()
{
    return new VectorMath(x, z);
}