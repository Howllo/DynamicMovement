#pragma once

#include <fstream>

class PrintClass
{
public:
    PrintClass();
    
    /**
     * \brief Used to print character information based on Character Behavior.
     * \param characters Character object that will be used to access information to be printed.
     * \param outfile File stream to be printed to file.
     * \param deltaTime Delta time to be printed.
     */
    static void printCharacter(class Character* characters, std::ofstream &outfile, double deltaTime);
private:
    /**
     * \brief Used to format the file to be more readable for humans.
     * \param check Takes in a double that will be checked.
     * \param outfile Takes in a ofstream object to be changed based on check.
     */
    static void checkForZeroes(double check, std::ofstream& outfile);
};
