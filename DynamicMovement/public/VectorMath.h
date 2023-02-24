#pragma once

class VectorMath
{
   public:
    // X axis of the vector.
    double x;
    
    // Z axis of the vector.
    double z;

    // Keep track of temp object. Used for closestPointSegment tracking.
    // This is to keep from accidentally deleting in use object.
    bool tempObject;
 
    /**
    * \brief Used for creating new vector objects with out large parameter from subtractions, adding, or multiplication. 
    */
    VectorMath();
    
    /**
     * \brief Used for constructing a vector object without array.
     * \param x_in Takes in a double coordinate for the X axis.
     * \param z_in Takes in a double coordinate for the Z axis.
     */
    VectorMath(double x_in, double z_in);

    /**
     * \brief Used for temporary requirements.
     * \param VM Takes in VectorMath Object to set points.
     */
     void setPoints(VectorMath* VM);
 
    /**
     * \brief Used to get the length using parthenon theorem.
     * \return Returns a double of the parthenon theorem.
     */
    double vector_length();

    /**
     * \brief Use to normalize the vector.
     * \return Returns a instantiated vector.
     */
    VectorMath* vector_normalize();

    /**
     * \brief Used to add two vectors together.
     *        this += n.
     * \param n Takes in a vector to be added.
     */
    void AddVector(const VectorMath* n);

    /**
     * \brief Used as a static function to add two vectors.
     * \param v Takes in a first vector to be added.
     * \param n Takes in a second vector to be added.
     * \return Returns a NEW vector object.
     */
    static VectorMath* AddTwoVectors(const VectorMath* v, const VectorMath* n);
 
    /**
     * \brief Used to subtract objects.
     *        this -= n
     * \param n Takes in a vector object to be subtracted.
     */
    void SubtractVector(const VectorMath* n);

    /**
    * \brief Use to get the difference between two vector objects for creation of a new vector object.
    *        results = v - n 
    * \param v First vector object that is being subtracted from.
    * \param n Second vector object that is being subtracted.
    */
    void SubtractVector(const VectorMath* v, const VectorMath* n);

    /**
     * \brief Use to get the difference between two vector objects for creation of a new vector object.
     *        results = v - n 
     * \param v First vector object that is being subtracted from.
     * \param n Second vector object that is being subtracted.
     * \return Returns a NEW VectorMath object.
     */
    static VectorMath* SubtractVectors(const VectorMath* v, const VectorMath* n);
    
    /**
     * \brief Used for multiplication of the X and Z coordinates.
     *        this *= incoming
     * \param incoming Takes in a double to be multiplied.
     */
    void MultiplyDouble(double incoming);

    /**
     * \brief Used to divide X and Z by the incoming double.
     *        this /= incoming
     * \param incoming Takes in double to be divided by.
     */
    void DivideDouble(double incoming);

    /**
     * \brief Used to get the distance between two point.
     * \param p1 Takes in a VectorMath object for point one.
     * \param p2 Takes in a VectorMath object for point one.
     * \param deleteObjects If true P1 and P2 will be deleted.
     * \return Returns double of a dot product in 2D.
     */
    static double vectorDot(VectorMath* p1, VectorMath* p2, bool deleteObjects);
 
    /**
     * \brief Used to clone VectorMath.
     * \return Returns a VectorMath objects.
     */
    VectorMath* Clone();
};