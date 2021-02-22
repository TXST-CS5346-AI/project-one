#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include "ClauseItem.h"
#include "VariableListItem.h"
#include "Statement.h"
#include "BackChain.h"
#include "KnowledgeBase.h"

using namespace std;

void BackChain::populateLists()
{
    ruleSystem.kBase.push_back(Statement());
    //ruleSystem.populateKnowledgeBase("knowledgeBase.txt");
    ruleSystem.populateKnowledgeBase("carKnowledgeBase.txt");

    variableList.push_back(VariableListItem("Empty", false, "", "This is an error string", STRING));

    populateVariableList("variablesList.csv");

}


//TEMPORARY - THIS NEEDS TO HAVE SOME ERROR CHECKING - dTorr implemented to test things.
void BackChain::populateVariableList(std::string fileName)
{
    string csvLine;

    string name;
    string prompt = " ";
    int type = 1;
    int startParseLocation = 0;
    int endParseLocation = 0;

    ifstream variableListFile;
    variableListFile.open(fileName);
    
    while (!variableListFile.eof())
    {
        getline(variableListFile, csvLine);

        startParseLocation = 0;
        endParseLocation = csvLine.find(',', startParseLocation);
        name = csvLine.substr(startParseLocation, endParseLocation);

        cout << name << endl;

        startParseLocation = endParseLocation + 1;
        endParseLocation = csvLine.find(',', startParseLocation);
        prompt = csvLine.substr(startParseLocation, endParseLocation);

        startParseLocation = endParseLocation + 1;
        endParseLocation = csvLine.find(',', startParseLocation);

        variableList.push_back(VariableListItem(name, false, "", prompt, type));
    }


}

bool BackChain::processPremiseList(Statement& statement, string stringToMatch)
{
    int solution = 0;
    bool isValid = true;
    int location = 0;
    int conclusionLocation = 0;
    string valueToMatch = "";

    for (int premiseIter = 1; (isValid && premiseIter < statement.premiseList.size()); premiseIter++)
    {

        //go through the entire list and see if there is a valid one
        conclusionLocation = findValidConclusionInStatements(statement.premiseList.at(premiseIter).name, 1,
            statement.premiseList.at(premiseIter).value);

        //is a conclusion but not valid
        if (conclusionLocation == -1)
        {
            isValid = false;
        }

        //is a conclusion and valid
        if (conclusionLocation > 0)
        {
            isValid = true;
        }

        //not a conclusion
        if (conclusionLocation == 0)
        {
            isValid = instantiatePremiseClause(statement.premiseList.at(premiseIter));
        }
    }

    return isValid;
}

bool BackChain::instantiatePremiseClause(ClauseItem& clause)
{
    bool isValid = false;
    bool isFound = false;

    for (int premiseClauseIter = 1; (!isFound && premiseClauseIter < variableList.size()); premiseClauseIter++)
    {
        if (clause.name == variableList.at(premiseClauseIter).name)
        {
            isFound = true;

            if (!variableList.at(premiseClauseIter).instantiated)
            {
                std::cout << variableList.at(premiseClauseIter).description;
                std::cin >> variableList.at(premiseClauseIter).value;
                variableList.at(premiseClauseIter).instantiated = true;
            }

            if (variableList.at(premiseClauseIter).value == clause.value)
            {
                //there will be another method call here, since we need more than just equal to comparisons.
                isValid = true;
            }
        }
    }
    
    return isValid;
}

int BackChain::findValidConclusionInStatements(string conclusionName, int startingIndex, string stringToMatch)
{
    int location = 0;
    bool isConclusion = false;
    bool isValid = false;
    for (int conclusionIter = startingIndex; (conclusionIter < ruleSystem.kBase.size() && !isValid); conclusionIter++)
    {
        if (conclusionName == ruleSystem.kBase.at(conclusionIter).conclusion.name)
        {
            isConclusion = true;

            if (stringToMatch == ruleSystem.kBase.at(conclusionIter).conclusion.value || stringToMatch == "DONTCARE")
            {
                isValid = processPremiseList(ruleSystem.kBase.at(conclusionIter), stringToMatch);

                if (isValid)
                {
                    location = conclusionIter;
                }
            }
        }
    }

    if (isConclusion && !isValid)
    {
        location = -1;
    }

    return location;
}


//Need to replace couts...
void BackChain::runBackwardChaining()
{
    //TODO - need knowledge base representation

    //no need for conclusion stack, will actually be the recursive stack

    string conclusionToSolve = "";
    int conclusionLocation = 0;
    bool isSolvedStatement = false;

    cout << "Please enter a conclusion to solve: ";
    cin >> conclusionToSolve;

    conclusionLocation = findValidConclusionInStatements(conclusionToSolve, 1, "DONTCARE");

    //is a conclusion but not valid
    if (conclusionLocation == -1)
    {
        cout << "conclusion is NOT valid";
    }

    //is a conclusion and valid
    if (conclusionLocation > 0)
    {
        cout << "Result is " << ruleSystem.kBase.at(conclusionLocation).conclusion.value << endl;
        cout << "conclusion is valid";
    }

    //not a conclusion
    if (conclusionLocation == 0)
    {
        cout << "no conclusion";
    }

}