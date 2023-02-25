/****************************************
 *
 * Author: Tony A. Hardiman Jr.
 * Assignment: Programming Assignment 1
 * Declaration: This program is entirely my own work.
 *
 ***************************************/

#include <iostream>
#include "Character.h"
#include "DynamicMovement.h"
#include "PrintClass.h"
#include <iomanip>
#include "SteeringOutput.h"
#include "PathAlgorithm.h"

enum ETestChar
{
    ETestContinue,
    ETestFlee,
    ETestSeek,
    ETestArrive,
    ETestPathFollowing,
};

// Prototypes
void createCharacterMovement(Character* v_character, Character* target, PathAlgorithm* _path, DynamicMovement* dynamicMovement,
    double deltaTime);
Character* createNewCharacter(ETestChar tChar);

int main(int argc, char* argv[])
{
    // Simulation
    const double stopTime = 125.0;
    const double deltaTime = 0.50;
    double currentDeltaTime = 0.0;
    auto* path = new PathAlgorithm();
    auto* dynamicMovement = new DynamicMovement();
    
    // Create File
    std::ofstream outfile;
    outfile.open("C:/temp/TrajectoryData_TonyH.txt");
    if(!outfile)
    {
        std::cout << "Error. Fail to open file." << std::endl; 
        return 0;
    }

    // Test Characters
    Character* followPath = createNewCharacter(ETestPathFollowing);

    // Path
    path->AddPath(0, 90);
    path->AddPath(-20, 65);
    path->AddPath(20, 40);
    path->AddPath(-40, 15);
    path->AddPath(40, -10);
    path->AddPath(-60, -35);
    path->AddPath(60, -60);
    path->AddPath(0, -85);
    
    // Main Loop
    while(currentDeltaTime <= stopTime)
    {
        if(currentDeltaTime == 0.0)
        {
            //PrintClass::printCharacter()
        }
        
        // Update Delta Time
        currentDeltaTime += deltaTime;
    }
    std::cout << "Finished printing!" << std::endl;
    outfile.close();
    delete path;
    delete followPath;
    delete dynamicMovement;
    return 0;
}

void createCharacterMovement(Character* v_character, Character* target, PathAlgorithm* _path, DynamicMovement* dynamicMovement,
    double deltaTime)
{
    // Calculate Data
    switch (v_character->getSteerBehavior())
    {
        case CONTINUE:
            dynamicMovement->dynamicUpdate(v_character, dynamicMovement->getSteeringContinue(v_character), deltaTime);
            break;
        case FLEE:
            dynamicMovement->dynamicUpdate(v_character, dynamicMovement->getSteeringFlee(v_character, target),deltaTime);
            break;
        case SEEK:
            dynamicMovement->dynamicUpdate(v_character, dynamicMovement->getSteeringSeek(v_character, target), deltaTime);
            break;
        case ARRIVE:
            dynamicMovement->dynamicUpdate(v_character, dynamicMovement->getSteeringArrive(v_character, target), deltaTime);
            break;
        case FOLLOW_PATH:
            dynamicMovement->dynamicUpdate(v_character, dynamicMovement->getSteeringFollowPath(v_character, _path), deltaTime);
            break;
        case NONE:
            std::cout << "Character: " << v_character->getCharacterID() << " is set to behavior NONE. Fix it." << std::endl;
            break;
    }
}

void createCharacterMovement(Character* v_character, PathAlgorithm* path, double deltaTime)
{
}

Character* createNewCharacter(ETestChar tChar)
{
    switch(tChar)
    {
        case ETestContinue:
            // Continue Character
             return new Character(2601, CONTINUE, new VectorMath(0.0, 0.0),
                new VectorMath(0.0, 0.0), new VectorMath(0.0, 0.0), 0.0, 0.0,
                0.0, 0.0, 0.0, NONE, 0.0, 0.0,
                0.0, false);
        case ETestFlee:
            return new Character(2602, FLEE, new VectorMath(-30.0, -50.0),
                new VectorMath(2.0, 7.0), new VectorMath(0.0, 0.0), 0.785398163397448,
                0.0, 0.0, 8.0, 1.5, CONTINUE, 0.0, 0.0,
                0.0, false);
        case ETestSeek:
            return new Character(2603, SEEK, new VectorMath(-50.0, 40.0),
                new VectorMath(0.0, 8.0), new VectorMath(0.0, 0.0), 4.71238898038469,
                0.0, 0.0, 8.0, 2.0, CONTINUE, 0.0, 0.0,
                0.0, false);
        case ETestArrive:
            return new Character(2604, ARRIVE, new VectorMath(50, 75),
                new VectorMath(-9.0, 4.0), new VectorMath(0.0, 0.0), 3.14159265358979,
                0.0, 0.0, 10.0, 2.0, CONTINUE, 4.0, 32,
                1.0, false);
        case ETestPathFollowing:
            return new Character(2701, FOLLOW_PATH, new VectorMath(20.0, 95.0),
                new VectorMath(0.0, 0.0), new VectorMath(0.0, 0.0), 0.0, 0.0,
                4, 2.0, 1.0, 0.04, false);
    }
    return nullptr;
}

#pragma region PROGRAM ASSIGNMENT 1
/*
    // Creating Character object array. Test objects: continueCharacter, fleeCharacter, seekCharacter, arriveCharacter
    std::vector<Character*> vCharacters = {continueCharacter, fleeCharacter, seekCharacter, arriveCharacter}; 

    // Setting up target.
    Character* target = continueCharacter;

 
for(const auto& v_character : vCharacters)
{
    // Time Step 0.
    if(currentDeltaTime == 0.0)
    {
        printCharacter(v_character, outfile, currentDeltaTime);
        continue;
    }

    // Movement
    createCharacterMovement(v_character, target, deltaTime);

    // Print
    printCharacter(v_character, outfile, currentDeltaTime);
}
 */
#pragma endregion 