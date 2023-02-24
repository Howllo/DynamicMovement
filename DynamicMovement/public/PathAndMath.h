#pragma once

#include <vector>
#include "VectorMath.h"

class PathAndMath
{
    std::vector<VectorMath*> points;
public:
    PathAndMath();
    PathAndMath(double x_in, double z_in);
    ~PathAndMath();

    /**
     * \brief Used to add a new path to the object. 
     * \param x_in Takes in a double x coordinate.
     * \param z_in Takes in a double z coordinate.
     */
    void AddPath(double x_in, double z_in);

    /**
     * \brief Used to find closest segment.
     * \param Q VectorMath Object as a query point.
     * \param A Segment endpoint.
     * \param B Segment endpoint.
     * \return Returns closest segment to query point in 2D.
     */
    VectorMath* closestPointSegment(VectorMath* Q, VectorMath* A, VectorMath* B);
    
    /**
     * \brief Used to get the closest path to the character.
     * \param character Takes a character to get the position from.
     * \return Returns a struct of the path position.
     */
    VectorMath* getParam(class Character* character);

    /**
     * \brief Used to calculate the distance between two points.
     *              (B.X - A.Z)^2 + (B.Z - A.Z)^2
     * \param A Takes in a point A VectorMath.
     * \param B Takes in a point B VectorMath.
     * \return Returns the distance between the two points.
     */
    double distancePointPoint(const VectorMath* A, const VectorMath* B) const;
};