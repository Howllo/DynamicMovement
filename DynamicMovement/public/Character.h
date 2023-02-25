﻿/****************************************
 *
 * Author: Tony A. Hardiman Jr.
 * Assignment: Programming Assignment 1
 * Declaration: This program is entirely my own work.
 *
 ***************************************/

#pragma once
#include "VectorMath.h"
#include "Character.h"

enum CharacterBehavior
{
    NONE = 0,
    CONTINUE = 1,
    SEEK = 6,
    FLEE = 7,
    ARRIVE = 8,
    FOLLOW_PATH = 11,
};

class Character
{
    int ID;
    CharacterBehavior behavior;
    VectorMath* iPosition;
    VectorMath* iVelocity;
    VectorMath* iLinear;
    double iOrientation;
    double iRotation;
    double iAngular;
    double maxVelocity;
    double maxAcceleration;
    CharacterBehavior target;
    float arrivalRadius;
    double slowingRadius;
    double timeToTarget;
    double pathToFollow;
    double pathOffset;
    bool hasCollided;
    
public:
    // Used for Path Following function.
    Character();
    
    // Programming Assignment 1 - Constructor
    Character(int id, CharacterBehavior behavior, VectorMath* iposition, VectorMath* ivelocity, VectorMath* ilinear,
        double iorientation, double irotation, double iangular, double maxvelocity, double maxacceleration,
        CharacterBehavior target, float arrivalradius, double slowingradius, double timetotarget, bool collision);

    // Programming Assignment 2 - Constructor
    Character(int id, CharacterBehavior behavior, VectorMath* iposition, VectorMath* ivelocity, VectorMath* ilinear,
              double iorientation, double iangular, double maxvelocity, double maxacceleration, double pathToFollow,
              double pathOffset, bool collision);
    ~Character();

    // Just bunch of Getters
    int getCharacterID() const;
    CharacterBehavior getSteerBehavior();
    VectorMath* getPosition() const;
    VectorMath* getVelocity() const;
    VectorMath* getLinear() const;
    double getOrientation() const;
    double getRotation() const;
    double getAngular() const;
    double getMaxAcceleration() const;
    double getArrivalRadius() const;
    double getSlowingRadius() const;
    double getMaxVelocity() const;
    double getTimeToTarget() const;
    double getPathOffset() const;
    bool getCollision() const;

    // Setters
    void setPosition(VectorMath* newPosition);
    void setLinear(VectorMath* newLinear);
    void setOrientation(double newOrientation);
    void setRotation(double newRotation);
    void setAngular(double newAngular);
    void setVelocity(VectorMath* newVelocity);
};