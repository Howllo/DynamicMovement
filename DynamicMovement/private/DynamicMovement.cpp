/****************************************
*
 * Author: Tony A. Hardiman Jr.
 * Assignment: Programming Assignment 1
 * Declaration: This program is entirely my own work.
 *
 ***************************************/

#include "DynamicMovement.h"
#include "Character.h"
#include "SteeringOutput.h"
#include <cmath>
#include <iostream>

void DynamicMovement::dynamicUpdate(Character* character, SteeringOutput* steering, const double deltaTime)
{
    // Character Position.
    VectorMath* pVec = new VectorMath(character->getVelocity()->x, character->getVelocity()->z);
    pVec->MultiplyDouble(deltaTime);
    character->getPosition()->AddVector(pVec);
    delete pVec;

    // Character Orientation
    character->setOrientation( character->getOrientation() + (character->getRotation() * deltaTime) );

    // Character Velocity
    pVec = new VectorMath(steering->GetLinear()->x, steering->GetLinear()->z);
    pVec->MultiplyDouble(deltaTime);
    character->getVelocity()->AddVector(pVec);
    delete pVec;

    // Character Rotation
    character->setRotation(character->getRotation() + (steering->GetAngular() * deltaTime));

    // Character Linear / Angular
    character->setLinear(steering->GetLinear()->Clone());
    character->setAngular(steering->GetAngular());

    // Check Jitter
    if(character->getVelocity()->vector_length() < stopVecloity) { character->setVelocity(new VectorMath(0, 0)); }

    // Check Max Velocity
    if(character->getVelocity()->vector_length() > character->getMaxVelocity())
    {
        character->setVelocity(character->getVelocity()->vector_normalize());
        character->getVelocity()->MultiplyDouble(character->getMaxVelocity());
    }
}

SteeringOutput* DynamicMovement::getSteeringContinue(Character* character)
{
    return new SteeringOutput(new VectorMath(character->getLinear()->x, character->getLinear()->z), character->getAngular());
}

SteeringOutput* DynamicMovement::getSteeringSeek(Character* character, Character* target)
{
    auto* result = new SteeringOutput(new VectorMath(0.0, 0.0), 0.0);

    // Create a new Vector object to store new information.
    VectorMath* vector_math = new VectorMath();
    vector_math->SubtractVector(target->getPosition(), character->getPosition());
    result->SetLinear(vector_math->vector_normalize());
    result->GetLinear()->MultiplyDouble(character->getMaxAcceleration());
    
    result->SetAngular(0.0);
    delete vector_math;
    return result;
}

SteeringOutput* DynamicMovement::getSteeringFlee(Character* character, Character* target)
{
    auto* result = new SteeringOutput(new VectorMath(0.0, 0.0), 0.0);

    // Create a new Vector object to store new information.
    auto* vector_math = new VectorMath();
    vector_math->SubtractVector(character->getPosition(), target->getPosition());
    result->SetLinear(vector_math->vector_normalize());
    result->GetLinear()->MultiplyDouble(character->getMaxAcceleration());
    
    result->SetAngular(0.0);
    delete vector_math;
    return  result;
}

SteeringOutput* DynamicMovement::getSteeringArrive(Character* character, Character* target)
{
    auto* result = new SteeringOutput(new VectorMath(0.0, 0.0), 0.0);
    auto* direction = new VectorMath();
    direction->SubtractVector(target->getPosition(),character->getPosition());
    const double distance = direction->vector_length();
    double arrivalSpeed = 0.0;
    
    if(distance < character->getArrivalRadius())
        arrivalSpeed = 0.0;
    else if(distance > character->getSlowingRadius())
        arrivalSpeed = character->getMaxVelocity();
    else
        arrivalSpeed = (character->getMaxVelocity() * distance) / character->getSlowingRadius();

    // Setting up arrival vector.
    VectorMath* arrival_velocity = direction->vector_normalize();
    arrival_velocity->MultiplyDouble(arrivalSpeed);
    arrival_velocity->SubtractVector(character->getVelocity());
    arrival_velocity->DivideDouble(character->getTimeToTarget());
    result->SetLinear(arrival_velocity);
    
    if(result->GetLinear()->vector_length() > character->getMaxAcceleration())
    {
        result->SetLinear(result->GetLinear()->vector_normalize());
        result->GetLinear()->MultiplyDouble(character->getMaxAcceleration());
    }
    delete direction;
    return result;
}

SteeringOutput* DynamicMovement::getSteeringFollowPath(Character* character, PathAndMath* path)
{
    
}