/****************************************
 *
 * Author: Tony A. Hardiman Jr.
 * Assignment: Programming Assignment 1
 * Declaration: This program is entirely my own work.
 *
 ***************************************/

#include <iostream>
#include <fstream>
#include <iomanip>
#include "Character.h"
#include "DynamicMovement.h"
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

enum ETest
{
    ETestPAOne,
    ETestPATwo,
    EDebug
};

// Prototypes
void createCharacterMovement(Character* v_character, const Character* target, PathAlgorithm* _path,
    DynamicMovement* dynamicMovement, double deltaTime);
Character* createNewCharacter(ETestChar tChar);
static void checkForZeroes(double check, std::ofstream& outfile);
static void printCharacter(Character* characters, std::ofstream &outfile, double deltaTime);
int programAssignmentOne();
int programAssignmentTwo();
void Debug();

int main(int argc, char* argv[])
{
    constexpr ETest test = EDebug;

    switch(test)
    {
        case ETestPAOne:
            return programAssignmentOne();
        case ETestPATwo:
            return programAssignmentTwo();
        case EDebug:
            Debug();
            break;
        default:  // NOLINT(clang-diagnostic-covered-switch-default)
            return 0;
    }
    return 0;
}

int programAssignmentTwo()
{
    // Simulation
    constexpr double deltaTime = 0.50;
    constexpr double simulatedSeconds = 125.0;
    double currentSimulatedSeconds = 0.0;
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
    path->AddPath(-20.0, 65);
    path->AddPath(20, 40);
    path->AddPath(-40, 15);
    path->AddPath(40, -10);
    path->AddPath(-60, -35);
    path->AddPath(60, -60);
    path->AddPath(0, -85);
    path->setAssemblePoint(path->pathAssemble(1));
    
    // Main Loop
    while(currentSimulatedSeconds <= simulatedSeconds)
    {
        if(currentSimulatedSeconds == 0.0)
        {
            printCharacter(followPath, outfile, currentSimulatedSeconds);
            currentSimulatedSeconds += deltaTime;
            continue;
        }
        createCharacterMovement(followPath, nullptr, path, dynamicMovement, deltaTime);
        printCharacter(followPath, outfile, currentSimulatedSeconds);
        
        // Update Delta Time
        currentSimulatedSeconds += deltaTime;
    }
    std::cout << "Finished printing!" << std::endl;
    outfile.close();
    delete path;
    delete followPath;
    delete dynamicMovement;
    return 0;
}

int programAssignmentOne()
{
    // Simulation
    constexpr double deltaTime = 0.50;
    constexpr double simulatedSeconds = 50.0;
    double currentSimulatedSeconds = 0.0;
    auto* dynamicMovement = new DynamicMovement();
    
    // Create File
    std::ofstream outfile;
    outfile.open("C:/temp/TrajectoryData_TonyH.txt");
    if(!outfile)
    {
        std::cout << "Error. Fail to open file." << std::endl; 
        return 0;
    }
    
    // Creating Character object array. Test objects: continueCharacter, fleeCharacter, seekCharacter, arriveCharacter
    std::vector<Character*> vCharacters = {
        createNewCharacter(ETestContinue),
        createNewCharacter(ETestFlee),
        createNewCharacter(ETestSeek),
        createNewCharacter(ETestArrive)
    }; 

    // Setting up target.
    Character* target = vCharacters[0];
    
    // Main Loop
    while(currentSimulatedSeconds <= simulatedSeconds)
    {
        for(const auto& v_character : vCharacters)
        {
            // Time Step 0.
            if(currentSimulatedSeconds == 0.0)
            {
                printCharacter(v_character, outfile, currentSimulatedSeconds);
                continue;
            }

            // Movement
            createCharacterMovement(v_character, target, nullptr, dynamicMovement, deltaTime);

            // Print
            printCharacter(v_character, outfile, currentSimulatedSeconds);
        }
        // Update Delta Time
        currentSimulatedSeconds += deltaTime;
    }
    std::cout << "Finished printing!" << std::endl;
    outfile.close();
    delete dynamicMovement;
    return 0;
}

void createCharacterMovement(Character* v_character, const Character* target, PathAlgorithm* _path,
    DynamicMovement* dynamicMovement, double deltaTime)
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

Character* createNewCharacter(ETestChar tChar)
{
    switch(tChar)
    {
        case ETestContinue:
             return new Character(2601, CONTINUE, new Vector2(0.0, 0.0),
                new Vector2(0.0, 0.0), new Vector2(0.0, 0.0), 0.0, 0.0,
                0.0, 0.0, 0.0, NONE, 0.0, 0.0,
                0.0, false);
        case ETestFlee:
            return new Character(2602, FLEE, new Vector2(-30.0, -50.0),
                new Vector2(2.0, 7.0), new Vector2(0.0, 0.0), 0.785398163397448,
                0.0, 0.0, 8.0, 1.5, CONTINUE, 0.0, 0.0,
                0.0, false);
        case ETestSeek:
            return new Character(2603, SEEK, new Vector2(-50.0, 40.0),
                new Vector2(0.0, 8.0), new Vector2(0.0, 0.0), 4.71238898038469,
                0.0, 0.0, 8.0, 2.0, CONTINUE, 0.0, 0.0,
                0.0, false);
        case ETestArrive:
            return new Character(2604, ARRIVE, new Vector2(50, 75),
                new Vector2(-9.0, 4.0), new Vector2(0.0, 0.0), 3.14159265358979,
                0.0, 0.0, 10.0, 2.0, CONTINUE, 4.0, 32,
                1.0, false);
        case ETestPathFollowing:
            return new Character(2701, FOLLOW_PATH, new Vector2(20.0, 95.0),
                new Vector2(0.0, 0.0), new Vector2(0.0, 0.0), 0.0, 0.0,
                4, 2.0, 1, 0.04, false);
    }
    return nullptr;
}

void Debug()
{
    Vector2* T = new Vector2(5.0, 5.0);
    Vector2* D = new Vector2(4.0, 4.0);
    Vector2 V(*T - *D);
    V.printVector();
    V.setPoint(*T * *D);
    V.printVector();
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