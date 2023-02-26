/****************************************
 *
 * Author: Tony A. Hardiman Jr.
 * Assignment: Programming Assignment 1
 * Declaration: This program is entirely my own work.
 *
 ***************************************/

#include "SteeringOutput.h"

SteeringOutput::SteeringOutput()
{
    iLinear = nullptr;
    IAngular = 0.0;
}

SteeringOutput::SteeringOutput(Vector2* linear, double angular)
{
    iLinear = linear;
    IAngular = angular;
}

SteeringOutput::~SteeringOutput()
{
    delete iLinear;
}

Vector2* SteeringOutput::GetLinear()
{
    return iLinear;
}

double SteeringOutput::GetAngular()
{
    return IAngular;
}

void SteeringOutput::SetLinear(const Vector2& linear)
{
    Vector2* temp = new Vector2(linear.x, linear.z);
    delete iLinear;
    iLinear = temp;
}

void SteeringOutput::SetAngular(double angular)
{
    IAngular = angular;
}