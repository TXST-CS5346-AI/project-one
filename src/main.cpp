#pragma warning(disable : 4996)

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "ClauseItem.hpp"
#include "Statement.hpp"
#include "BackChain.hpp"
#include "ForwardChain.hpp"
#include "VariableListItem.hpp"

using namespace std;

void displayResults(int conclusion)
{
    // find the appropriate result string from the knowledge base 
    // and display it.
    if (0 == conclusion)
    {
        cout << "No conclusion was able to be made.";
    }
}

void diagnose(BackChain& backChain)
{
    backChain.runBackwardChaining();
}

void repair(ForwardChain & forwardChain)
{
    forwardChain.runForwardChaining();
}

int main(int argc, char* argv[])
{

    cout << "Welcome to the Automobile Diagnostic Program." << endl;
    
    if (argc == 2 && (argv[1] == "-h" || argv[1] == "-help")) 
    {
        cout << "To use this program, please read the instructions below and re-launch." << endl;
        cout << "Additional details for building and execution are also available in the README.md file." << endl;
    }


    //Need to separate MVC here...
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

