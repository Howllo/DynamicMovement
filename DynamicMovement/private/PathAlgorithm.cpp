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

PathAlgorithm::PathAlgorithm()
{
    normalizedPoints = nullptr;
}

PathAlgorithm::PathAlgorithm(double x_in, double z_in)
{
    normalizedPoints = nullptr;
    pathPoints.push_back(new Vector2(x_in, z_in));
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

path_assemble* PathAlgorithm::pathAssemble(int pathID) // Confirmed Working
{
    const auto pathSegments = static_cast<unsigned int>(pathPoints.size() - 1);
    std::vector<double> pathDistance(pathSegments + 1); pathDistance[0] = 0.0;
    for(unsigned int i = 1; i < (pathSegments + 1); i++)
        pathDistance[i] = pathDistance[i - 1] + Vector2::distancePointPoint(pathPoints[i - 1], pathPoints[i]);
    std::vector<double> param(pathSegments + 1); param[0] = 0.0;
    for(unsigned int i = 1; i < (pathSegments + 1); i++)
        param[i] = pathDistance[i] / max(pathDistance);
    return new path_assemble(pathID, pathPoints, pathDistance, param, pathSegments);
}

Vector2 PathAlgorithm::closestPointSegment(Vector2* Q, Vector2* A, Vector2* B)// Should be Working it is simple.
{
    double T = Vector2::vectorDot( (*Q + *B), (*B - *A) ) / Vector2::vectorDot( (*B - *A), (*B - *A) );
    if( T <= 0) { return *A; }
    else if (T >= 1) { return *B; }
    else { return Vector2( *A + ((*B - *A) * T) ); }
}

Vector2* PathAlgorithm::pathGetPosition(PathAlgorithm* path, double param) // Not Working?
{
    const int i = std::max(0, static_cast<int>(Vector2::which(param, path->getAssemblePoint()->pathParam)));
    Vector2 A(path->pathPoints[i]);
    Vector2 B(path->pathPoints[i + 1]);
    const double T = (param - path->getAssemblePoint()->pathParam[i]) / (path->getAssemblePoint()->pathParam[i + 1] -
        path->getAssemblePoint()->pathParam[i]);
    return new Vector2(A + ((B - A) * T));
}

double PathAlgorithm::getParam(Vector2* charPosition) const
{
    double closestDistance = DBL_MAX;
    unsigned int closestSegment = INT_MAX;
    Vector2* closestPoint = new Vector2(0.0, 0.0);
    for(unsigned int i = 0; i < normalizedPoints->segments; i++)
    {
        Vector2 A(pathPoints[i]);
        Vector2 B(pathPoints[i + 1]);
        Vector2 checkPoint = closestPointSegment(charPosition, &A, &B);
        const double checkDistance = Vector2::distancePointPoint(charPosition, &checkPoint);
        if(checkDistance < closestDistance)
        {
            closestPoint->setPoint(&checkPoint);
            closestDistance = checkDistance;
            closestSegment = i;
        }
    }
    
    Vector2 A(pathPoints[closestSegment]);
    const double AParam = normalizedPoints->pathParam[closestSegment];
    Vector2 B(pathPoints[closestSegment + 1]);
    double BParam = normalizedPoints->pathParam[closestSegment + 1];
    const Vector2* C = closestPoint;
    double T = Vector2::vector_length(*C - A) / Vector2::vector_length(B - A);
    const double CParam = AParam + (T * (BParam - AParam));
    return CParam;
}

double PathAlgorithm::max(std::vector<double> dis)
{
    double largest = DBL_MIN;
    for(double di : dis)
    {
        if(di > largest)
            largest = di;
    }
    return largest;
}

void PathAlgorithm::setAssemblePoint(path_assemble* path)
{
    normalizedPoints = path;
}