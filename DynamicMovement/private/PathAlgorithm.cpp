/****************************************
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
    ID = 0;
    segments = 0;
}

PathAlgorithm::~PathAlgorithm()
{
    while(!points.empty())
    {
        delete points.back();
        points.pop_back();
    }
}

void PathAlgorithm::AddPath(double x_in, double z_in)
{
    points.push_back(new Vector2(x_in, z_in));
}

void PathAlgorithm::pathAssemble(int pathID)
{
    ID = pathID;
    segments = static_cast<unsigned int>(points.size() - 1);
    
    // Creating Distance
    pathDistance.push_back(0.0);
    for(unsigned int i = 1; i < (segments + 1); i++)
        pathDistance.push_back(pathDistance[i - 1] + Vector2::distancePointPoint(points[i - 1], points[i]));
    
    // Creating Normalize
    param.push_back(0.0);
    for(unsigned int i = 1; i < (segments + 1); i++)
        param.push_back(pathDistance[i] / Vector2::max(DBL_MIN, &pathDistance));
}

Vector2 PathAlgorithm::closestPointSegment(const Vector2* Q, const Vector2* A, const Vector2* B)
{
    const double T = Vector2::vectorDot( (*Q - *A), (*B - *A) ) / Vector2::vectorDot( (*B - *A), (*B - *A) );
    if( T <= 0) return *A; 
    if (T >= 1) return *B; 
    return Vector2( *A + ((*B - *A) * T) );
}

Vector2* PathAlgorithm::pathGetPosition(const PathAlgorithm* path, const double param)
{
    const unsigned int i = Vector2::max(0, Vector2::which(param, path->param));
    Vector2 A(path->points[i]);
    Vector2 B(path->points[i + 1]);
    const double T = (param - path->param[i]) / (path->param[i + 1] - path->param[i]);
    return new Vector2(A + (B - A) * T);
}

double PathAlgorithm::getParam(const PathAlgorithm* path, const Vector2* position)
{
    double closestDistance = DBL_MAX;
    unsigned int closestSegment = 0;    // Working
    auto* closestPoint = new Vector2(0.0, 0.0);
    
    for(unsigned int i = 0; i < path->segments; i++)
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
    const double    AParam = path->param[closestSegment];
    Vector2         B(path->getPathPoints()[closestSegment + 1]);
    const double    BParam = path->param[closestSegment + 1];
    const Vector2*  C = closestPoint;
    const double    T = Vector2::vector_length(*C - A) / Vector2::vector_length(B - A);
    const double    CParam = AParam + (T * (BParam - AParam));
    
    return          CParam;
}

std::vector<Vector2*> PathAlgorithm::getPathPoints() const 
{
    return points;
}