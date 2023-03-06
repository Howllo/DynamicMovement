﻿/****************************************
 *
 * Author: Tony A. Hardiman Jr.
 * Assignment: Programming Assignment 2
 * Declaration: This program is entirely my own work.
 *
 ***************************************/

#include "../public/PathAlgorithm.h"
#include "../public/Vector2.h"

PathAlgorithm::PathAlgorithm()
{
    normalizedPoints = nullptr;
}

PathAlgorithm::~PathAlgorithm()
{
    while(!pathPoints.empty())
    {
        delete pathPoints.back();
        pathPoints.pop_back();
    }
    delete normalizedPoints;
}

void PathAlgorithm::AddPath(double x_in, double z_in)
{
    pathPoints.push_back(new Vector2(x_in, z_in));
}

path_assemble* PathAlgorithm::pathAssemble(int pathID) const
{
    const auto pathSegments = static_cast<unsigned int>(pathPoints.size() - 1);
    std::vector<double>* pathDistance = rep(0.0, pathSegments + 1);
    for(unsigned int i = 1; i < (pathSegments + 1); i++)
        (*pathDistance)[i] = (*pathDistance)[i - 1] + Vector2::distancePointPoint(pathPoints[i - 1], pathPoints[i]);
    std::vector<double>* param = rep(0.0, pathSegments + 1);
    for(unsigned int i = 1; i < (pathSegments + 1); i++)
        (*param)[i] = (*pathDistance)[i] / Vector2::max(DBL_MIN, pathDistance);
    return new path_assemble(pathID, pathPoints, pathDistance, param, pathSegments);
}

Vector2 PathAlgorithm::closestPointSegment(const Vector2* Q, Vector2* A, Vector2* B)
{
    const double T = Vector2::vectorDot( (*Q - *B), (*B - *A) ) / Vector2::vectorDot( (*B - *A), (*B - *A) );
    if( T <= 0) { return *A; }
    else if (T >= 1) { return *B; }
    else { return Vector2( *A + ((*B - *A) * T) ); }
}

Vector2* PathAlgorithm::pathGetPosition(const PathAlgorithm* path, const double param)
{
    const path_assemble* p_Assemble = path->getAssemblePoint();
    const unsigned int i = Vector2::max(0, Vector2::which(param, p_Assemble->pathParam));
    Vector2 A(path->pathPoints[i]);
    Vector2 B(path->pathPoints[i + 1]);
    const double T = (param - p_Assemble->pathParam[i]) / (p_Assemble->pathParam[i + 1] - p_Assemble->pathParam[i]);
    return new Vector2(A + ((B - A) * T));
}

double PathAlgorithm::getParam(const PathAlgorithm* path, const Vector2* position)
{
    const auto* path_assemble = path->getAssemblePoint();
    double closestDistance = DBL_MAX;
    unsigned int closestSegment = 0;
    auto* closestPoint = new Vector2(0.0, 0.0);
    
    for(unsigned int i = 0; i < path_assemble->segments; i++)
    {
        Vector2 A(path->getPathPoints()[i]);
        Vector2 B(path->getPathPoints()[i + 1]);
        Vector2 checkPoint(closestPointSegment(position, &A, &B));
        const double checkDistance = Vector2::distancePointPoint(position, &checkPoint);
        if(checkDistance < closestDistance)
        {
            closestPoint->setPoint(&checkPoint);
            closestDistance = checkDistance;
            closestSegment = i;
        }
    }
    
    Vector2         A(path->getPathPoints()[closestSegment]);
    const double    AParam = path_assemble->pathParam[closestSegment];
    Vector2         B(path->getPathPoints()[closestSegment + 1]);
    const double    BParam = path_assemble->pathParam[closestSegment + 1];
    const Vector2*  C = closestPoint;
    const double    T = Vector2::vector_length(*C - A) / Vector2::vector_length(B - A);
    const double    CParam = AParam + (T * (BParam - AParam));
    
    return          CParam;
}

std::vector<Vector2*> PathAlgorithm::getPathPoints() const 
{
    return pathPoints;
}

void PathAlgorithm::setAssemblePoint(path_assemble* path)
{
    normalizedPoints = path;
}

path_assemble* PathAlgorithm::getAssemblePoint() const
{
    return normalizedPoints;
}

std::vector<double>* PathAlgorithm::rep(double in_data, unsigned int size)
{
    auto* rVector = new std::vector<double>;
    for(unsigned int i = 0; i < size; i++)
        rVector->push_back(in_data);
    return rVector;
}