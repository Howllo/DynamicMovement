/****************************************
 *
 * Author: Tony A. Hardiman Jr.
 * Assignment: Programming Assignment 2
 * Declaration: This program is entirely my own work.
 *
 ***************************************/

#pragma once
#include <vector>

class PathAlgorithm
{
    // Random ID for the path.
    int ID;

    // Points on the graphs with both X and Z.
    std::vector<class Vector2*> points;

    // Distance between segments.
    std::vector<double> pathDistance;

    // Normalized Points. 0 - 1
    std::vector<double> param;

    // Total segments on the graph.
    unsigned int segments;
public:
    PathAlgorithm();
    ~PathAlgorithm();

    /**
     * \brief Used to add a new path to the object. 
     * \param x_in Takes in a double x coordinate.
     * \param z_in Takes in a double z coordinate.
     */
    void AddPath(double x_in, double z_in);

    /**
     * \brief Assemble a complete data structure.
     * \param pathID Takes in a ID.
     */
    void pathAssemble(int pathID);
    
    /**
     * \brief Used to find closest segment.
     * \param Q VectorMath Object as a query point.
     * \param A Segment endpoint.
     * \param B Segment endpoint.
     * \return Returns closest segment to query point in 2D.
     */
    static Vector2 closestPointSegment(const Vector2* Q,const Vector2* A, const Vector2* B);

    /**
     * \brief To get the position of a path corresponding to given path parameter.
     * \param path Main path algorithm.
     * \param param Takes in double of current target param.
     * \return Returns vector2.
     */
    static Vector2* pathGetPosition(const PathAlgorithm* path, const double param);
    
    /**
     * \brief Used to get the closest path to the character.
     * \param path Takes in a Path Algorithm object.
     * \param position Takes in a character vector2 position
     * \return Returns a double.
     */
    static double getParam(const PathAlgorithm* path, const Vector2* position);

    /**
     * \brief Used to get the path points from path.
     * \return Returns the vector2 array of path points.
     */
    std::vector<Vector2*> getPathPoints() const;
};