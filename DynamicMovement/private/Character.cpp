/****************************************
*
 * Author: Tony A. Hardiman Jr.
 * Assignment: Programming Assignment 1
 * Declaration: This program is entirely my own work.
 *
 ***************************************/

#include "Character.h"

Character::Character(int id, CharacterBehavior behavior, VectorMath* iposition, VectorMath* ivelocity, VectorMath* ilinear,
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

VectorMath* Character::getPosition() const
{
    return iPosition;
}

VectorMath* Character::getVelocity() const
{
    return iVelocity;
}

VectorMath* Character::getLinear() const
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

bool Character::getCollision() const
{
    return hasCollided;
}

void Character::setPosition(VectorMath* newPosition)
{
    if(!newPosition) return;
    if(iPosition != newPosition)
        delete iPosition;
    iPosition = newPosition;
}

void Character::setLinear(VectorMath* newLinear)
{
    if(!newLinear) return;
    if(iLinear != newLinear)
        delete iLinear;
    iLinear = newLinear;
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

void Character::setVelocity(VectorMath* newVelocity)
{
    if(iVelocity == newVelocity)
        return;
    delete iVelocity;
    iVelocity = newVelocity;
}