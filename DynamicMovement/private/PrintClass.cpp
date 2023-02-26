#include "PrintClass.h"
#include <iomanip>
#include "Character.h"

PrintClass::PrintClass()
{
}

void PrintClass::checkForZeroes(double check, std::ofstream& outfile)
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

void PrintClass::printCharacter(Character* characters, std::ofstream &outfile, double deltaTime)
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