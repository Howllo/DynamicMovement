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

SteeringOutput::SteeringOutput(VectorMath* linear, double angular)
{
    iLinear = linear;
    IAngular = angular;
}

SteeringOutput::~SteeringOutput()
{
    delete iLinear;
}

VectorMath* SteeringOutput::GetLinear()
{
    return iLinear;
}

double SteeringOutput::GetAngular()
{
    return IAngular;
}

void SteeringOutput::SetLinear(VectorMath* linear)
{
    if(!linear) return;
    if(iLinear != linear)
        delete iLinear;
    iLinear = linear;
}

void SteeringOutput::SetAngular(double angular)
{
    IAngular = angular;
}