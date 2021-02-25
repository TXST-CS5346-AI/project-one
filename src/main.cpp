#pragma warning(disable : 4996)

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "ClauseItem.h"
#include "Statement.h"
#include "BackChain.h"
#include "ForwardChain.h"
#include "VariableListItem.h"

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

int main()
{

    cout << "Welcome to the Automobile Diagnostic Program." << endl;
    cout << "This is the server side of the program." << endl;
    cout << "You can run this program in command line mode or with a GUI" << endl;
    cout << "Select your option ( 1 - GUI mode, any other is command line mode): ";


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

