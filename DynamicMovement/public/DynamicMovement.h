/****************************************
 *
 * Author: Tony A. Hardiman Jr.
 * Assignment: Programming Assignment 1
 * Declaration: This program is entirely my own work.
 *
 ***************************************/

#pragma once

class DynamicMovement
{
    const double stopVelocity = 0.02;
    class SteeringOutput* conSteer;
    SteeringOutput* fleeSteer;
    SteeringOutput* seekSteer;
    SteeringOutput* arriveSteer;
    SteeringOutput* followSteer;
public:
    DynamicMovement();
    ~DynamicMovement();
    
    /**
     * \brief Used to update the character position through steering object and delta time.
     * \param character Takes in a character to be moved.
     * \param steering Takes in a SteeringObject to change the objects movement.
     * \param deltaTime Takes in a time scale as delta time.
     */
    void dynamicUpdate(class Character* character, SteeringOutput* steering, double deltaTime);
 
    /**
     * \brief Use to get movement of the continue character object.
     * \param character Takes in a character object.
     * \return Returns steering output object.
     */
    SteeringOutput* getSteeringContinue(const Character* character);

    /**
     * \brief Gets the dynamic movement of the character seek.
     * \param character Takes in a character object that is trying to get to target.
     * \param target Take is a character that is used as point reference.
     * \return Returns SteeringOutput object.
     */
    SteeringOutput* getSteeringSeek(const Character* character, const Character* target);

    /**
     * \brief Used to get the movement for the character flee.
     * \param character Takes in a character object that will be doing the flee'ing from the target.
     * \param target Take in a character object that will be one that the character object is moving away from.
     * \return Returns a SteeringOutput object.
     */
    SteeringOutput* getSteeringFlee(const Character* character, const Character* target);

    /**
     * \brief Used to get the movement for the character arrive.
     * \param character Takes in a character object that will be doing the arrival to the target.
     * \param target Take in a character object that will be one that is approached by arrival character.
     * \return Returns a SteeringOuput object.
     */
    SteeringOutput* getSteeringArrive(const Character* character, const Character* target);

    /**
     * \brief Used to move character along a path.
     * \param character Takes in a character object to move.
     * \param path Takes in a path object to move the character.
     * \return Returns a steering output object.
     */
    SteeringOutput* getSteeringFollowPath(const Character* character, class PathAlgorithm* path);

private:
    /**
     * \brief Use for memory management to prevent a steer object memory leak.
     * \param newOutput Takes in a new steer object to be compared to old steer object.
     * \param oldOutput Uses the old steer object be compared.
     */
    static bool MemoryManagement(const SteeringOutput* newOutput, const SteeringOutput* oldOutput);

    /**
     * \brief Used to check the behavior of the character object to reduce the size of function.
     * \param character Takes in a character to get the behavior of the character.
     * \param newSteer Takes in a the new steer object to be sent to memory management.
     */
    void checkCharacterBehavior(Character* character, SteeringOutput* newSteer);
};
