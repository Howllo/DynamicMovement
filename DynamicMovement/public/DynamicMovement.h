#pragma once

class DynamicMovement
{
    double stopVecloity = 0.02;
 
public:
    void dynamicUpdate(class Character* character, class SteeringOutput* steering, double deltaTime);
 
    /**
     * \brief Use to get movement of the continue character object.
     * \param character Takes in a character object.
     * \return Returns steering output object.
     */
    SteeringOutput* getSteeringContinue(Character* character);

    /**
     * \brief Gets the dynamic movement of the character seek.
     * \param character Takes in a character object that is trying to get to target.
     * \param target Take is a character that is used as point reference.
     * \return Returns SteeringOutput object.
     */
    SteeringOutput* getSteeringSeek(Character* character, Character* target);

    /**
     * \brief Used to get the movement for the character flee.
     * \param character Takes in a character object that will be doing the flee'ing from the target.
     * \param target Take in a character object that will be one that the character object is moving away from.
     * \return Returns a SteeringOutput object.
     */
    SteeringOutput* getSteeringFlee(Character* character, Character* target);

    /**
     * \brief Used to get the movement for the character arrive.
     * \param character Takes in a character object that will be doing the arrival to the target.
     * \param target Take in a character object that will be one that is approached by arrival character.
     * \return Returns a SteeringOuput object.
     */
    SteeringOutput* getSteeringArrive(Character* character, Character* target);
};
