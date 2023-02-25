/****************************************
 *
 * Author: Tony A. Hardiman Jr.
 * Assignment: Programming Assignment 2
 * Declaration: This program is entirely my own work.
 *
 ***************************************/

#include "PathAlgorithm.h"
#include <complex.h>
#include "Character.h"
#include "cmath"

PathAlgorithm::PathAlgorithm()
{
}

PathAlgorithm::PathAlgorithm(double x_in, double z_in)
{
    points.push_back(new VectorMath(x_in, z_in));
}

PathAlgorithm::~PathAlgorithm()
{
    while(!points.empty())
    {
        delete points.back();
        points.pop_back();
    }

    while(!normalizedPoints.empty())
    {
        delete points.back();
        points.pop_back();
    }
}

void PathAlgorithm::AddPath(double x_in, double z_in)
{
    points.push_back(new VectorMath(x_in, z_in));
}

VectorMath* PathAlgorithm::closestPointSegment(VectorMath* Q, VectorMath* A, VectorMath* B)
{
    double T =
        VectorMath::vectorDot(VectorMath::SubtractVectors(Q, A), VectorMath::SubtractVectors(B, A), true) /
        VectorMath::vectorDot(VectorMath::SubtractVectors(B, A), VectorMath::SubtractVectors(B, A), true);

    if( T <= 0) { return A; }
    else if (T >= 1) { return B; }
    else
    {
        VectorMath* temp = VectorMath::SubtractVectors(B, A);
        temp->MultiplyDouble(T);
        temp->AddVector(A);
        temp->tempObject = true;
        return temp;
    }
}

VectorMath* PathAlgorithm::pathGetPosition(PathAlgorithm* path, VectorMath* param)
{
    std::vector<VectorMath*> holderVector = path->getPointsOnGraph();
    int i = VectorMath::which(param, path->getPointsOnGraph());
    VectorMath* A = new VectorMath(holderVector[i]->x, holderVector[i]->z);
    VectorMath* B = new VectorMath(holderVector[i + 1]->x, holderVector[i + 1]->z);
    VectorMath* T = VectorMath::DivideVectors( VectorMath::SubtractVectors(param, holderVector[i + 1]),
        VectorMath::SubtractVectors(holderVector[i + 1], holderVector[i]), true );
    VectorMath* P = VectorMath::SubtractVectors(B, A);
    P->MultiplyVector(T);
    P->AddVector(A);
    delete A;
    delete B;
    return P;
}

VectorMath* PathAlgorithm::getParam(Character* character)
{
    double closestDistance = INT_MAX;
    unsigned int closestSegment = INT_MAX;
    VectorMath* closestPoint = new VectorMath();
    
    for(unsigned int i = 0; i < points.size(); i++)
    {
        VectorMath* pointOne = new VectorMath();
        VectorMath* pointTwo = new VectorMath();
        pointOne->setPoints(points[i]);
        if((i + 1) <= points.size())
            pointTwo->setPoints(points[i + 1]);
        
        VectorMath* checkPoint = closestPointSegment(character->getPosition(), pointOne, pointTwo);
        const double checkDistance = VectorMath::distancePointPoint(character->getPosition(), checkPoint);

        if(checkDistance < closestDistance)
        {
            closestPoint->setPoints(checkPoint);
            closestDistance = checkDistance;
            closestSegment = i;
        }

        if(checkPoint->tempObject)
            delete checkPoint;
        delete pointOne;
        delete pointTwo;
    }

    // Calculate Path param to closest point.
    return calculatePathParam(closestSegment, closestPoint);
}

VectorMath* PathAlgorithm::calculatePathParam(unsigned closestSegment, const VectorMath* closestPoint)
{
    VectorMath A;
    A.x = points[closestSegment]->x;
    A.z = points[closestSegment]->z;
    const VectorMath* AParam = points[closestSegment];
    
    VectorMath B;
    B.x = points[closestSegment + 1]->x;
    B.z = points[closestSegment + 1]->z;
    const VectorMath* BParam = points[closestSegment + 1];
    
    const VectorMath* C = closestPoint;
    VectorMath* CParam = VectorMath::SubtractVectors(BParam, AParam);
    
    VectorMath* D = VectorMath::SubtractVectors(C, A);
    VectorMath* E = VectorMath::SubtractVectors(B, A);
    double T = D->vector_length() / E->vector_length();

    CParam->MultiplyDouble(T);
    CParam->AddVector(AParam);
    
    delete D;
    delete E;
    return CParam;
}