#pragma once

class VectorMath
{
   public:
    // X axis of the vector.
    double x;
    
    // Z axis of the vector.
    double z;

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
     * \brief Used for constructing a vector object with array.
     * \param axis Takes in a double array for the set X and Z axis.
     */
    VectorMath(double axis[]);

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
     * \brief Used to clone VectorMath.
     * \return Returns a VectorMath objects.
     */
    VectorMath* Clone();
};