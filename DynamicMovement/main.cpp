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
#include <fstream>
#include <vector>
#include <iomanip>
#include "SteeringOutput.h"

// Prototypes
void checkForZeroes(double check, std::ofstream& outfile);
bool MemoryManagement(SteeringOutput* newOutput, SteeringOutput* oldOutput);
void printCharacter(Character* characters, std::ofstream &outfile, double deltaTime);

int main(int argc, char* argv[])
{
    //  Creating the main dynamic class to run simulation.
    auto* dynamicMovement = new DynamicMovement();

    // Simulation
    const double stopTime = 50.0;
    const double deltaTime = 0.50;
    double currentDeltaTime = 0.0;

    // Memory Management
    auto* conSteer = new SteeringOutput();
    auto* fleeSteer = new SteeringOutput();
    auto* seekSteer = new SteeringOutput();
    auto* arriveSteer = new SteeringOutput();
    
    // Continue Character
    auto* continueCharacter = new Character(2601, CONTINUE, new VectorMath(0.0, 0.0),
        new VectorMath(0.0, 0.0), new VectorMath(0.0, 0.0), 0.0, 0.0, 0.0,
        0.0, 0.0, NONE, 0.0, 0.0, 0.0, false);

    // Flee Character
    auto* fleeCharacter = new Character(2602, FLEE, new VectorMath(-30.0, -50.0),
        new VectorMath(2.0, 7.0), new VectorMath(0.0, 0.0), 0.785398163397448, 0.0,
        0.0, 8.0, 1.5, CONTINUE, 0.0, 0.0, 0.0, false);

    // Seek Character
    auto* seekCharacter = new Character(2603, SEEK, new VectorMath(-50.0, 40.0),
        new VectorMath(0.0, 8.0), new VectorMath(0.0, 0.0), 4.71238898038469, 0.0,
        0.0, 8.0, 2.0, CONTINUE, 0.0, 0.0, 0.0, false);

    // Arrive Character
    auto* arriveCharacter = new Character(2604, ARRIVE, new VectorMath(50, 75),
        new VectorMath(-9.0, 4.0), new VectorMath(0.0, 0.0), 3.14159265358979, 0.0,
        0.0, 10.0, 2.0, CONTINUE, 4.0, 32, 1.0, false);

    
    // Creating Character object array. Test objects: continueCharacter, fleeCharacter, seekCharacter, arriveCharacter
    std::vector<Character*> vCharacters = {continueCharacter, fleeCharacter, seekCharacter, arriveCharacter}; 

    // Setting up target.
    Character* target = continueCharacter;
    
    // Create File
    std::ofstream outfile;
    outfile.open("C:/temp/TrajectoryData_TonyH.txt");
    if(!outfile)
    {
        std::cout << "Error. Fail to open file." << std::endl; 
        return 0;
    }
    
    // Main Loop
    while(currentDeltaTime <= stopTime)
    {
        SteeringOutput* new_object;
        for(const auto& v_character : vCharacters)
        {
            // Time Step 0.
            if(currentDeltaTime == 0.0)
            {
                printCharacter(v_character, outfile, currentDeltaTime);
                continue;
            }

            // Calculate Data
            switch (v_character->getSteerBehavior())
            {
                case CONTINUE:
                    new_object = dynamicMovement->getSteeringContinue(v_character);
                    if(MemoryManagement(new_object, conSteer))
                        conSteer = new_object;
                    dynamicMovement->dynamicUpdate(v_character, conSteer, deltaTime);
                    break;
                case FLEE:
                    new_object = dynamicMovement->getSteeringFlee(v_character, target);
                    if(MemoryManagement(new_object, fleeSteer))
                        fleeSteer = new_object;
                    dynamicMovement->dynamicUpdate(v_character, fleeSteer,deltaTime);
                    break;
                case SEEK:
                    new_object = dynamicMovement->getSteeringSeek(v_character, target);
                    if(MemoryManagement(new_object, seekSteer))
                        seekSteer = new_object;
                    dynamicMovement->dynamicUpdate(v_character, seekSteer, deltaTime);
                    break;
                case ARRIVE:
                    new_object = dynamicMovement->getSteeringArrive(v_character, target);
                    if(MemoryManagement(new_object, arriveSteer))
                        arriveSteer = new_object;
                    dynamicMovement->dynamicUpdate(v_character, arriveSteer, deltaTime);
                    break;
                case NONE:
                    std::cout << "Character: " << v_character->getCharacterID() << " is set to behavior NONE. Fix it." << std::endl;
                    break;
            }

            // Print
            printCharacter(v_character, outfile, currentDeltaTime);
        }

        // Update Delta Time
        currentDeltaTime += deltaTime;
    }
    std::cout << "Finished printing!" << std::endl;
    outfile.close();
    return 0;
}

bool MemoryManagement(SteeringOutput* newOutput, SteeringOutput* oldOutput)
{
    if(!oldOutput || !newOutput || newOutput == oldOutput)
        return false;
    delete oldOutput;
    return true;
}

void checkForZeroes(double check, std::ofstream& outfile)
{
    if(check == 0.0)
        outfile << std::setprecision(0);
    else if(std::fmod(check, 1.0) == 0.0)
        outfile << std::setprecision(0);
    else if(std::fmod(check, 0.5) == 0.0)
        outfile << std::setprecision(1);
    else if(check < 0.0)
        outfile <<std::setprecision(14);
    else
        outfile <<std::setprecision(14);
}

void printCharacter(Character* characters, std::ofstream &outfile, double deltaTime)
{
    outfile << std::fixed << std::left;

    // Current Delta Time
    if(std::fmod(deltaTime, 1.0) != 0.0)
        outfile  << std::setprecision(1);
    else
        outfile << std::setprecision(0);
    outfile << deltaTime;
            
    outfile << std::setprecision(15);
    outfile << "," << characters->getCharacterID();
            
    checkForZeroes(characters->getPosition()->x, outfile);
    outfile << "," << characters->getPosition()->x;

    checkForZeroes(characters->getPosition()->z, outfile);
    outfile << "," << characters->getPosition()->z;
    
    checkForZeroes(characters->getVelocity()->x, outfile);
    outfile << "," << characters->getVelocity()->x;

    checkForZeroes(characters->getVelocity()->z, outfile);
    outfile << "," << characters->getVelocity()->z;

    checkForZeroes(characters->getLinear()->x, outfile);
    outfile << "," << characters->getLinear()->x;
            
    checkForZeroes(characters->getLinear()->z, outfile);
    outfile << "," << characters->getLinear()->z;
            
    checkForZeroes(characters->getOrientation(), outfile);
    outfile << "," << characters->getOrientation();

    checkForZeroes(characters->getSteerBehavior(), outfile);
    outfile << "," << characters->getSteerBehavior();

    if (!characters->getCollision())
        outfile << "," << "FALSE";
    else
        outfile << "," << "TRUE";
    outfile << std::endl;
}