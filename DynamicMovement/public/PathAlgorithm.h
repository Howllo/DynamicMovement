/****************************************
 *
 * Author: Tony A. Hardiman Jr.
 * Assignment: Programming Assignment 2
 * Declaration: This program is entirely my own work.
 *
 ***************************************/
#pragma once

#include <vector>
#include "VectorMath.h"

struct path_assemble
{
    int ID;
    double x;
    double z;
    double distance;
    VectorMath* param;
    int segment;
};

class PathAlgorithm
{
    std::vector<VectorMath*> points;
    std::vector<path_assemble*> normalizedPoints;
public:
    PathAlgorithm();
    PathAlgorithm(double x_in, double z_in);
    ~PathAlgorithm();

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
     * \brief To get the positon of a path corresponding to given path parameter.
     * \param path PathAlgorithm Object.
     * \param param Vector of the path.
     * \return Returns vector math.
     */
    static VectorMath* pathGetPosition(PathAlgorithm* path, VectorMath* param);
    
    /**
     * \brief Used to get the closest path to the character.
     * \param character Takes a character to get the position from.
     * \return Returns a struct of the path position.
     */
    VectorMath* getParam(class Character* character);

    // Getters
    std::vector<VectorMath*> getPointsOnGraph();
private:
    /**
     * \brief Used for getParam.
     * \param closestSegment Takes in a index that is closest point to the character. Use to access points vector.
     * \param closestPoint Takes in the closest point to the character.
     * \return Returns the closest point.
     */
    VectorMath* calculatePathParam(unsigned int closestSegment, const VectorMath* closestPoint);
};

inline std::vector<VectorMath*> PathAlgorithm::getPointsOnGraph()
{
    return points;
}