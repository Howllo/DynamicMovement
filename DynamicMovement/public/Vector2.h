/****************************************
 *
 * Author: Tony A. Hardiman Jr.
 * Assignment: Programming Assignment 1
 * Declaration: This program is entirely my own work.
 *
 ***************************************/

#pragma once
#include <ostream>
#include <vector>

class Vector2
{
    friend class PathAlgorithm;
    friend class DynamicMovement;
   public:
    // X axis of the vector.
    double x;
    
    // Z axis of the vector.
    double z;

    Vector2(Vector2* in);
    
    /**
     * \brief Used for constructing a vector object without array.
     * \param x_in Takes in a double coordinate for the X axis.
     * \param z_in Takes in a double coordinate for the Z axis.
     */
    Vector2(double x_in, double z_in);

    /**
     * \brief Used for temporary requirements.
     * \param VM Takes in VectorMath Object to set points.
     */
     void setPoint(Vector2* VM);
 
    /**
     * \brief Used to get the length using parthenon theorem.
     * \return Returns a double of the parthenon theorem.
     */
    double vector_length();

    /**
     * \brief Used to get the length using parthenon theorem.
     * \param v Takes in a vector address to computer the length.
     * \return Returns a double of the parthenon theorem.
     */
    static double vector_length(const Vector2 &v);
    
    /**
     * \brief Use to normalize the vector.
     * \return Returns a instantiated vector.
     */
    Vector2* vector_normalize();

    /**
     * \brief Used to get the same X/Z coordinate of a object in pathParam.
     * \param param Takes in a the entire path to compare.
     * \param pathParam Takes in the path param vector to be processed.
     * \return Returns the index of the object that is the same as param.
     */
    static unsigned int which(double param, const std::vector<double>& pathParam);
    
    /**
     * \brief Used to get the distance between two point.
     * \param p1 Takes in a VectorMath object for point one.
     * \param p2 Takes in a VectorMath object for point one.
     * \return Returns double of a dot product in 2D.
     */
    static double vectorDot(Vector2 p1, Vector2 p2);

    /**
     * \brief Used to calculate the distance between two points.
     *              (B.X - A.Z)^2 + (B.Z - A.Z)^2
     * \param A Takes in a point A VectorMath.
     * \param B Takes in a point B VectorMath.
     * \return Returns the distance between the two points.
     */
    static double distancePointPoint(const Vector2* A, const Vector2* B);

    // Operator Overload
    Vector2 operator-(const Vector2 &right) const;
    Vector2 operator-(const double &right) const;
    Vector2 operator+(const Vector2 &right) const;
    Vector2 operator+(const double &right) const;
    Vector2 operator*(const Vector2 &right) const;
    Vector2 operator*(const double &right) const;
    Vector2 operator/(const Vector2 &right) const;
    Vector2 operator/(const double &right) const;
    Vector2& operator=(const Vector2&right);
    Vector2& operator+=(const Vector2 &right);
    Vector2& operator+=(const double &right);
    Vector2& operator*=(const Vector2 &right);
    Vector2& operator*=(const double &right);
    Vector2& operator/=(const Vector2 &right);
    Vector2& operator/=(const double &right);
    bool operator==(const Vector2 &right) const;

    /**
     * \brief Used to clone Vector2 objects.
     * \return Returns a NEW cloned object.
     */
    Vector2* Clone();
    
    // For Debugging only.
    void printVector();
};