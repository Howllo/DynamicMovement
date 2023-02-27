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
    // Memory Management.
    checkCharacterBehavior(character, steering);
    
    // Character Position.
    character->setPosition( *character->getPosition() + (*character->getVelocity() * deltaTime) );

    // Character Orientation
    character->setOrientation( character->getOrientation() + (character->getRotation() * deltaTime) );

    // Character Velocity
    character->setVelocity( *character->getVelocity() + (*steering->GetLinear() * deltaTime));

    // Character Rotation
    character->setRotation(character->getRotation() + (steering->GetAngular() * deltaTime));

    // Character Linear / Angular
    character->setLinear(*steering->GetLinear());
    character->setAngular(steering->GetAngular());

    // Check Jitter
    if(character->getVelocity()->vector_length() < stopVecloity) { character->setVelocity(*new Vector2(0, 0)); }

    // Check Max Velocity
    if(character->getVelocity()->vector_length() > character->getMaxVelocity())
    {
        character->setVelocity(*character->getVelocity()->vector_normalize() * character->getMaxVelocity());
    }
}

SteeringOutput* DynamicMovement::getSteeringContinue(Character* character)
{
    return new SteeringOutput(new Vector2(character->getLinear()->x, character->getLinear()->z), character->getAngular());
}

SteeringOutput* DynamicMovement::getSteeringSeek(Character* character, Character* target)
{
    auto* result = new SteeringOutput(new Vector2(0.0, 0.0), 0.0);
    result->SetLinear(*target->getPosition() - *character->getPosition());
    result->SetLinear(*result->GetLinear()->vector_normalize());
    result->SetLinear(*result->GetLinear() * character->getMaxAcceleration());
    result->SetAngular(0.0);
    return result;
}

SteeringOutput* DynamicMovement::getSteeringFlee(Character* character, Character* target)
{
    auto* result = new SteeringOutput(new Vector2(0.0, 0.0), 0.0);
    result->SetLinear(*character->getPosition() - *target->getPosition());
    result->SetLinear(*result->GetLinear()->vector_normalize());
    result->SetLinear(*result->GetLinear() * character->getMaxAcceleration());
    result->SetAngular(0.0);
    return  result;
}

SteeringOutput* DynamicMovement::getSteeringArrive(Character* character, Character* target)
{
    auto* result = new SteeringOutput(new Vector2(0.0, 0.0), 0.0);
    auto* direction = new Vector2( *target->getPosition() - *character->getPosition());
    const double distance = direction->vector_length();
    double arrivalSpeed = 0.0;
    
    if(distance < character->getArrivalRadius())
        arrivalSpeed = 0.0;
    else if(distance > character->getSlowingRadius())
        arrivalSpeed = character->getMaxVelocity();
    else
        arrivalSpeed = (character->getMaxVelocity() * distance) / character->getSlowingRadius();

    // Setting up arrival vector.
    Vector2* arrival_velocity = new Vector2(*direction->vector_normalize() * arrivalSpeed);
    result->SetLinear(*arrival_velocity - *character->getVelocity() / character->getTimeToTarget());
    
    if(result->GetLinear()->vector_length() > character->getMaxAcceleration())
    {
        result->SetLinear(*result->GetLinear()->vector_normalize());
        *result->GetLinear() *= character->getMaxAcceleration();
    }
    delete direction;
    return result;
}

SteeringOutput* DynamicMovement::getSteeringFollowPath(Character* character, PathAlgorithm* path)
{
    currentParam = path->getParam(character->getPosition());
    double targetParam = currentParam + character->getPathOffset();
    auto* target = new Character(PathAlgorithm::pathGetPosition(path, targetParam));
    return getSteeringSeek(character, target);
}

void DynamicMovement::MemoryManagement(const SteeringOutput* newOutput, const SteeringOutput* oldOutput)
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
            arriveSteer = newSteer;
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