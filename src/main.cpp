#pragma warning(disable : 4996)

#include <iostream>
#include <fstream> 
#include <string.h>
#include <cstdlib> 

#include "ClauseItem.hpp"
#include "Statement.hpp"
#include "BackChain.hpp"
#include "ForwardChain.hpp"
#include "VariableListItem.hpp"


/**
 * diagnose - as per project requirements, diagnose function emplyes Backward chaining
 * This is how we allow for diagnosing what issue the vehicle has. 
 *
 * @param BackChain& backChain - a BackChain instance
 *
 * @return none
 *
 */
void diagnose(BackChain& backChain)
{
    backChain.runBackwardChaining();
}


/**
 * repair - as per project requirements, repair function employs Forward Chaining
 * This is how we recommend a repair given an issue. 
 *
 * @param ForwardChain& forwardChain
 *
 * @return none
 */
void repair(ForwardChain& forwardChain)
{
    forwardChain.runForwardChaining();
}


/**
 * main - main function which serves as the entry point into the application.
 * User will be greeted with a welcome message. 
 *
 * If they invoke the program with -h or -help, a help menu with a set of instructions will 
 * be printed to the console. It is also recommended to review the README.md file in the project 
 * root directory. 
 *
 * @param int argc - the count of the number of command line arguments provided
 * @param char* argv[] - array holding the arguments provided during program invocation  
 *
 * @return EXIT_SUCCESS 0 
 *
 */
int main(int argc, char* argv[])
{
    std::cout << "Welcome to the Automobile Diagnostic Program." << std::endl;
    std::cout << "Authors: David Torrente, Randall Henderson, Borislav Sabotinov" << std::endl;
 
    if (argc == 2 && (strcmp(argv[1], "-h") || strcmp(argv[1], "-help"))) 
    {
        std::cout << "To use this program, please read the instructions below and re-launch." << std::endl;
        std::cout << "Additional details for building and execution are also available in the README.md file." << std::endl;
        std::cout << "First, the variablesList.csv and knowledgeBase.txt files will be processed to create an instance of the knowledge base" << std::endl;
        std::cout << "Next, the user will be prompted for a conclusion to solve." << std::endl;
        std::cout << "Valid choices are: issue, repair." << std::endl;

        return EXIT_SUCCESS;
    }


    BackChain backChain;
    backChain.populateLists();


    diagnose(backChain);

    ForwardChain forwardChain;
    forwardChain.copyKnowledgeBase(backChain.ruleSystem);
    forwardChain.copyVariableList(backChain.variableList);
    forwardChain.addIntermediateConclusions(backChain.intermediateConclusionList);

    repair(forwardChain);

    return EXIT_SUCCESS;
}

