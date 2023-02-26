/****************************************
 *
 * Author: Tony A. Hardiman Jr.
 * Assignment: Programming Assignment 2
 * Declaration: This program is entirely my own work.
 *
 ***************************************/

#include "PathAlgorithm.h"
#include "Vector2.h"
#include <complex>
#include "Character.h"

PathAlgorithm::PathAlgorithm()
{
}

PathAlgorithm::PathAlgorithm(double x_in, double z_in)
{
    points.push_back(new Vector2(x_in, z_in));
}

PathAlgorithm::~PathAlgorithm()
{
    while(!points.empty())
    {
        delete points.back();
        points.pop_back();
    }

    /*while(!normalizedPoints.empty())
    {
        delete points.back();
        points.pop_back();
    }*/
}

void PathAlgorithm::AddPath(double x_in, double z_in)
{
    points.push_back(new Vector2(x_in, z_in));
}

path_assemble* PathAlgorithm::pathAssemble(int pathID, double x_in, double z_in)
{
    unsigned long long pathSegment = 0;
    if(!points.empty())
        pathSegment = points.size() - 1;
    return new path_assemble();
}

Vector2* PathAlgorithm::closestPointSegment(Vector2* Q, Vector2* A, Vector2* B)
{
    double T = Vector2::vectorDot(*Q - *B, (*B - *A)) / Vector2::vectorDot(*B - *A, *B - *A);

    if( T <= 0) { return A; }
    else if (T >= 1) { return B; }
    else
    {
        Vector2* temp = new Vector2( (*B - *A) );
        *temp *= T;
        *temp += *A;
        temp->tempObject = true;
        return temp;
    }
}

Vector2* PathAlgorithm::pathGetPosition(PathAlgorithm* path, Vector2* param)
{
    std::vector<Vector2*> holderVector = path->getPointsOnGraph();
    int i = Vector2::which(param, path->getPointsOnGraph());
    Vector2* A = new Vector2(holderVector[i]->x, holderVector[i]->z);
    Vector2* B = new Vector2(holderVector[i + 1]->x, holderVector[i + 1]->z);
    Vector2* T = new Vector2(0.0, 0.0);
    *T = (*param - *holderVector[i]) / (*holderVector[i + 1] - *holderVector[i]);
    auto* P = new Vector2(0.0, 0.0);
    *P *= *A + (*T * (*B - *A));
    
    delete A;
    delete B;
    return P;
}

Vector2* PathAlgorithm::getParam(Character* character)
{
    double closestDistance = INT_MAX;
    unsigned int closestSegment = INT_MAX;
    Vector2* closestPoint = new Vector2(0.0, 0.0);
    
    for(unsigned int i = 0; i < points.size(); i++)
    {
        Vector2* pointOne = new Vector2(0.0, 0.0);
        Vector2* pointTwo = new Vector2(0.0, 0.0);
        pointOne->setPoint(points[i]);
        if((i + 1) < points.size())
            pointTwo->setPoint(points[i + 1]);
        
        Vector2* checkPoint = closestPointSegment(character->getPosition(), pointOne, pointTwo);
        const double checkDistance = Vector2::distancePointPoint(character->getPosition(), checkPoint);

        if(checkDistance < closestDistance)
        {
            closestPoint->setPoint(checkPoint);
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

Vector2* PathAlgorithm::calculatePathParam(unsigned closestSegment, const Vector2* closestPoint)
{
    Vector2 A(0.0, 0.0);
    A.x = points[closestSegment]->x;
    A.z = points[closestSegment]->z;
    const Vector2* AParam = points[closestSegment];
    
    Vector2 B(0.0, 0.0);
    B.x = points[closestSegment + 1]->x;
    B.z = points[closestSegment + 1]->z;
    const Vector2* BParam = points[closestSegment + 1];
    
    const Vector2* C = closestPoint;
    Vector2* CParam = new Vector2(*BParam - *AParam);
    Vector2 D(*C - A);
    Vector2 E(B - A);
    double T = D.vector_length() / E.vector_length();
    *CParam = *AParam + (*BParam - *AParam) * T;
    return CParam;
}