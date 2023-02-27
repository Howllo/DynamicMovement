/****************************************
 *
 * Author: Tony A. Hardiman Jr.
 * Assignment: Programming Assignment 2
 * Declaration: This program is entirely my own work.
 *
 ***************************************/
#pragma once

#include <vector>

struct path_assemble
{
    path_assemble(int id, std::vector<class Vector2*> point, std::vector<double> d, std::vector<double> p,
        unsigned int totalSegments)
    {
        ID = id;

        for(auto i : point)
        {
            points.push_back(i);
        }

        for(auto i : d)
        {
            pathDistance.push_back(i);
        }

        for(auto i: p)
        {
            pathParam.push_back(i);
        }
        segments = totalSegments;
    }

    // Random ID for the graph.
    int ID;

    // Points on the graphs with both X and Z.
    std::vector<Vector2*> points;

    // Distance between segments.
    std::vector<double> pathDistance;

    // Normalized Points. 0 - 1
    std::vector<double> pathParam;

    // Total segments on the graph.
    unsigned int segments;
};

class PathAlgorithm
{
private:
    std::vector<Vector2*> pathPoints;
    path_assemble* normalizedPoints;
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
     * \brief Assemble a complete data structure.
     * \param pathID Takes in a ID.
     * \return Return a path assemble structure.
     */
    path_assemble* pathAssemble(int pathID);
    
    /**
     * \brief Used to find closest segment.
     * \param Q VectorMath Object as a query point.
     * \param A Segment endpoint.
     * \param B Segment endpoint.
     * \return Returns closest segment to query point in 2D.
     */
    static Vector2 closestPointSegment(Vector2* Q, Vector2* A, Vector2* B);

    /**
     * \brief To get the position of a path corresponding to given path parameter.
     * \param path Main path algorithm.
     * \param param Takes in double of current target param.
     * \return Returns vector2.
     */
    static Vector2* pathGetPosition(PathAlgorithm* path, double param);
    
    /**
     * \brief Used to get the closest path to the character.
     * \param charPosition Takes in a character vector2 position
     * \return Returns a double.
     */
    double getParam(Vector2* charPosition) const;
    
    /**
     * \brief Sets the normalized points.
     * \param path Takes in path assemble structure.
     */
    void setAssemblePoint(path_assemble* path);
    
    /**
     * \brief Used to get path assemble.
     * \return Returns the address of the path assemble.
     */
    path_assemble* getAssemblePoint();
private:
    /**
     * \brief Used to ifnd the largest double and returns it.
     * \param dis Find the largest double in the vector array.
     * \return Returns the largest double in the vector.
     */
    double max(std::vector<double> dis);
};

inline path_assemble* PathAlgorithm::getAssemblePoint()
{
    return normalizedPoints;
}