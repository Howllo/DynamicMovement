/****************************************
 *
 * Author: Tony A. Hardiman Jr.
 * Assignment: Programming Assignment 1
 * Declaration: This program is entirely my own work.
 *
 ***************************************/

#pragma once
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

    Vector2(const Vector2* in);
    
    /**
     * \brief Used for constructing a vector object without array.
     * \param x_in Takes in a double coordinate for the X axis.
     * \param z_in Takes in a double coordinate for the Z axis.
     */
    Vector2(double x_in, double z_in);

    /**
    * \brief Used for setting X and Z points.
    * \param VM Takes in VectorMath Object to set points.
    */
    void setPoint(const Vector2* VM);

    /**
     * \brief Used for setting X and Z points.
     * \param v Takes in Vector2 Object to set points.
     */
    void setPoint(const Vector2& v);
    
    /**
     * \brief Used to get the length using parthenon theorem.
     * \return Returns a double of the parthenon theorem.
     */
    double vector_length() const;
    
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
    Vector2* vector_normalize() const;

    /**
     * \brief Use to normalize the vector.
     * \return Returns a instantiated vector.
     */
    static Vector2* vector_normalize(const Vector2* v);
    
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

    /**
     * \brief Used to get the same X/Z coordinate of a object in pathParam.
     * \param param Takes in a the entire path to compare.
     * \param pathParam Takes in the path param vector to be processed.
     * \return Returns the index of the object that is the same as param.
     */
    static std::vector<unsigned int> which(double param, const std::vector<double>& pathParam);
    
    /**
       * \brief Used to finds the smallest unsigned int and returns it.
       * \param f_n First number to be search.
       * \param s_n Second number to be search.
       * \return Returns either f_n or s_n as a double.
       */
    static double min(double f_n, double s_n);
    
    /**
     * \brief Used to finds the largest unsigned int and returns it.
     * \param smallest Used as a base-line for searching the largest.
     * \param in_search The vector that will be searched for the largest number.
     * \return Returns the largest double in the vector.
     */
    static double max(double smallest, const std::vector<double>* in_search);
    
    /**
     * \brief Used to finds the largest unsigned int and returns it.
     * \param smallest Used as a base-line for searching the largest.
     * \param in_search The vector that will be searched for the largest.
     * \return Returns the largest unsigned int in the vector.
     */
    static unsigned int max(unsigned int smallest, const std::vector<unsigned int>& in_search);
    
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
    
    // For Debugging only.
    void printVector() const;
};