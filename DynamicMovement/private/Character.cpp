/****************************************
 *
 * Author: Tony A. Hardiman Jr.
 * Assignment: Programming Assignment 1
 * Declaration: This program is entirely my own work.
 *
 ***************************************/

#include "Character.h"

Character::Character(Vector2* iposition)
{
    ID = 0;
    behavior = NONE;
    iPosition = iposition;
    iVelocity = nullptr;
    iLinear = nullptr;
    iOrientation = 0.0;
    iRotation = 0.0;
    iAngular = 0.0;
    maxVelocity = 0.0;
    maxAcceleration = 0.0;
    target = NONE;
    arrivalRadius = 0.0;
    slowingRadius = 0.0;
    timeToTarget = 0.0;
    hasCollided = false;
    pathToFollow = 0;
    pathOffset = 0.0;
}

Character::Character(int id, CharacterBehavior behavior, Vector2* iposition, Vector2* ivelocity, Vector2* ilinear,
                     double iorientation, double irotation, double iangular, double maxvelocity, double maxacceleration,
                     CharacterBehavior target, float arrivalradius, double slowingradius, double timetotarget, bool collision)
{
    ID = id;
    this->behavior = behavior;
    iPosition = iposition;
    iVelocity = ivelocity;
    iLinear = ilinear;
    iOrientation = iorientation;
    iRotation = irotation;
    iAngular = iangular;
    maxVelocity = maxvelocity;
    maxAcceleration = maxacceleration;
    this->target = target;
    arrivalRadius = arrivalradius;
    slowingRadius = slowingradius;
    timeToTarget = timetotarget;
    hasCollided = collision;

    // Unused
    this->pathToFollow = 0;
    this->pathOffset = 0.0;
}

Character::Character(int id, CharacterBehavior behavior, Vector2* iposition, Vector2* ivelocity, Vector2* ilinear,
    double iorientation, double iangular, double maxvelocity, double maxacceleration, int pathToFollow, double pathOffset,
    bool collision)
{
    ID = id;
    this->behavior = behavior;
    iPosition = iposition;
    iVelocity = ivelocity;
    iLinear = ilinear;
    iOrientation = iorientation;
    iAngular = iangular;
    maxVelocity = maxvelocity;
    maxAcceleration = maxacceleration;
    this->pathToFollow = pathToFollow;
    this->pathOffset = pathOffset;
    hasCollided = collision;

    // Unused
    iRotation = 0.0;
    this->target = NONE;
    arrivalRadius = 0.0;
    slowingRadius = 0.0;
    timeToTarget = 0.0;
}

Character::~Character()
{
    delete iPosition;
    delete iVelocity;
    delete iLinear;
}

int Character::getCharacterID() const
{
    return ID;
}

CharacterBehavior Character::getSteerBehavior()
{
    return behavior;
}

Vector2* Character::getPosition() const
{
    return iPosition;
}

Vector2* Character::getVelocity() const
{
    return iVelocity;
}

Vector2* Character::getLinear() const
{
    return iLinear;
}

double Character::getOrientation() const
{
    return iOrientation;
}

double Character::getRotation() const
{
    return iRotation;
}

double Character::getAngular() const
{
    return iAngular;
}

double Character::getMaxAcceleration() const
{
    return maxAcceleration;
}

double Character::getArrivalRadius() const
{
    return arrivalRadius;
}

double Character::getSlowingRadius() const
{
    return slowingRadius;
}

double Character::getMaxVelocity() const
{
    return maxVelocity;
}

double Character::getTimeToTarget() const
{
    return timeToTarget;
}

double Character::getPathOffset() const
{
    return pathOffset;
}

bool Character::getCollision() const
{
    return hasCollided;
}

void Character::setPosition(const Vector2 &newPosition)
{
    Vector2* temp = new Vector2(newPosition.x, newPosition.z);
    delete iPosition;
    iPosition = temp;
}

void Character::setLinear(const Vector2 &newLinear)
{
    Vector2* temp = new Vector2(newLinear.x, newLinear.z);
    delete iLinear;
    iLinear = temp;
}

void Character::setOrientation(double newOrientation)
{
    iOrientation = newOrientation;
}

void Character::setRotation(double newRotation)
{
    iRotation = newRotation;
}

void Character::setAngular(double newAngular)
{
    iAngular = newAngular;
}

void Character::setVelocity(const Vector2& newVelocity)
{
    Vector2* temp = new Vector2(newVelocity.x, newVelocity.z);
    delete iVelocity;
    iVelocity = temp;
}