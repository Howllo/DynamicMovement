/****************************************
 *
 * Author: Tony A. Hardiman Jr.
 * Assignment: Programming Assignment 1
 * Declaration: This program is entirely my own work.
 *
 ***************************************/

#pragma once
#include "Vector2.h"

class SteeringOutput
{
private:
    Vector2* iLinear;
    double IAngular;
public:
     /**
      * \brief Used if there needs to be objects that are calculated before placing into steering output.
      */
     SteeringOutput();

     /**
     * \brief Constructor is used if there is VectorMath, and Angular to be placed in the object.
     * \param linear Takes in a VectorMath objects to be used for linear X, and Z.
     * \param angular Takes in angular double to be used for angular.
     */
    SteeringOutput(Vector2* linear, double angular);
 
    /**
     * \brief Destroys any left over reference to VectorMath.
     */
    ~SteeringOutput();

    /**
     * \brief Used to get the object from steering output.
     * \return Returns the Steering Ouput VectorMath object.
     */
    Vector2* GetLinear();

    /**
     * \brief Used get the double angular from steering output object.
     * \return Returns double of angular from steering output object.
     */
    double GetAngular();

    /**
     * \brief Sets the linear object within the steering ouput object. Deletes the previous vector object.
     * \param linear Takes in a vector object to be used as linear.
     */
    void SetLinear(const Vector2& linear);

    /**
     * \brief Set the angular double within the steering output object.
     * \param angular Takes in a double to set the angular of the steering output.
     */
    void SetAngular(double angular);
};