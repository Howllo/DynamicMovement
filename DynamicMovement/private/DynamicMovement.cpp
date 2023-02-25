/****************************************
 *
 * Author: Tony A. Hardiman Jr.
 * Assignment: Programming Assignment 1
 * Declaration: This program is entirely my own work.
 *
 ***************************************/

#include "../public/DynamicMovement.h"
#include "../public/SteeringOutput.h"
#include "../public/PathAlgorithm.h"
#include "../public/Character.h"
#include <cmath>
#include <iostream>

DynamicMovement::DynamicMovement()
{
    conSteer = new SteeringOutput();
    fleeSteer  = new SteeringOutput();
    seekSteer  = new SteeringOutput();
    arriveSteer = new SteeringOutput();
    followSteer = new SteeringOutput();
}

DynamicMovement::~DynamicMovement()
{
    delete conSteer;
    delete fleeSteer;
    delete seekSteer;
    delete arriveSteer;
    delete followSteer;
}

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

SteeringOutput* DynamicMovement::getSteeringFollowPath(Character* character, PathAlgorithm* path)
{
    VectorMath* currentParam = path->getParam(character);
    VectorMath* targetParam = VectorMath::min(currentParam, character->getPathOffset());
    Character* target = new Character();
    target->setPosition(PathAlgorithm::pathGetPosition(path, targetParam));
    return getSteeringSeek(character, target);
}

void DynamicMovement::MemoryManagement(SteeringOutput* newOutput, SteeringOutput* oldOutput)
{
    if(!oldOutput || !newOutput || newOutput == oldOutput)
        return;
    delete oldOutput;
}

void DynamicMovement::checkCharacterBehavior(Character* character, SteeringOutput* newSteer)
{
    switch(character->getSteerBehavior())
    {
        case CONTINUE:
            MemoryManagement(newSteer, conSteer);
            conSteer = newSteer;
            break;
        case FLEE:
            MemoryManagement(newSteer, fleeSteer);
            fleeSteer = newSteer;
            break;
        case SEEK:
            MemoryManagement(newSteer, seekSteer);
            seekSteer = newSteer;
            break;
        case ARRIVE:
            MemoryManagement(newSteer, arriveSteer);
            seekSteer = newSteer;
            break;
        case FOLLOW_PATH:
            MemoryManagement(newSteer, followSteer);
            followSteer = newSteer;
            break;
        case NONE:
            std::cout << "Character: " << character->getCharacterID() << " is set to behavior NONE. Fix it." << std::endl;
        break;
    }
}