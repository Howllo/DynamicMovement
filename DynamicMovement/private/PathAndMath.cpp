#include "PathAndMath.h"
#include "Character.h"
#include "cmath"

PathAndMath::PathAndMath()
{
}

PathAndMath::PathAndMath(double x_in, double z_in)
{
    points.push_back(new VectorMath(x_in, z_in));
}

PathAndMath::~PathAndMath()
{
    while(!points.empty())
    {
        delete points.back();
        points.pop_back();
    }
}

void PathAndMath::AddPath(double x_in, double z_in)
{
    points.push_back(new VectorMath(x_in, z_in));
}

VectorMath* PathAndMath::closestPointSegment(VectorMath* Q, VectorMath* A, VectorMath* B)
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

VectorMath* PathAndMath::getParam(Character* character)
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
        const double checkDistance = distancePointPoint(character->getPosition(), checkPoint);

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

    VectorMath P;
    P.x = static_cast<double>(closestSegment);
    P.z = static_cast<double>(closestSegment);
    
}

double PathAndMath::distancePointPoint(const VectorMath* A, const VectorMath* B) const
{
    return sqrt( pow((B->x - A->x), 2) + pow((B->z - A->z), 2) );
}