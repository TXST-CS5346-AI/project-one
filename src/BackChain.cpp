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
    variableList.push_back(VariableListItem("Empty", false, "", "This is an error string", STRING));
    variableList.push_back(VariableListItem("DEGREE", false, "", "Do you have a degree YES or NO: ", STRING));
    variableList.push_back(VariableListItem("DISCOVERY", false, "", "Do you have a discovery YES or NO: ", STRING));
    variableList.push_back(VariableListItem("EXPERIENCE", false, "", "Enter years of experience: ", INT));
    variableList.push_back(VariableListItem("GRADE", false, "", "Enter your GPA: ", INT));

/*
    vector<ClauseItem> pOne;
    pOne.push_back(ClauseItem("NULL", "NULL", STRING));
    pOne.push_back(ClauseItem("DEGREE", "NO", STRING));
    vector<ClauseItem> pTwo;
    pTwo.push_back(ClauseItem("NULL", "NULL", STRING));
    pTwo.push_back(ClauseItem("DEGREE", "YES", STRING));
    vector<ClauseItem> pThree;
    pThree.push_back(ClauseItem("NULL", "NULL", STRING));
    pThree.push_back(ClauseItem("DEGREE", "YES", STRING));
    pThree.push_back(ClauseItem("DISCOVERY", "YES", STRING));
    vector<ClauseItem> pFour;
    pFour.push_back(ClauseItem("NULL", "NULL", STRING));
    pFour.push_back(ClauseItem("QUALIFY", "YES", INT));
    pFour.push_back(ClauseItem("GRADE", "2", INT));
    pFour.push_back(ClauseItem("EXPERIENCE", "4", INT));
    vector<ClauseItem> pFive;
    pFive.push_back(ClauseItem("NULL", "NULL", STRING));
    pFive.push_back(ClauseItem("QUALIFY", "YES", STRING));
    pFive.push_back(ClauseItem("GRADE", "2", INT));
    pFive.push_back(ClauseItem("EXPERIENCE", "1", INT));
    vector<ClauseItem> pSix;
    pSix.push_back(ClauseItem("NULL", "NULL", STRING));
    pSix.push_back(ClauseItem("QUALIFY", "YES", STRING));
    pSix.push_back(ClauseItem("GRADE", "4", INT));

    ruleSystem.kBase.push_back(Statement(ClauseItem("POSITION", "NO", STRING), pOne));
    ruleSystem.kBase.push_back(Statement(ClauseItem("QUALIFY", "YES", STRING), pTwo));
    ruleSystem.kBase.push_back(Statement(ClauseItem("POSITION", "RESEARCH", STRING), pThree));
    ruleSystem.kBase.push_back(Statement(ClauseItem("POSITION", "SERVICEENGINEER", STRING), pFour));
    ruleSystem.kBase.push_back(Statement(ClauseItem("POSITION", "NO", STRING), pFive));
    ruleSystem.kBase.push_back(Statement(ClauseItem("POSITION", "PRODUCTENGINEER", STRING), pSix));
  */  
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
            //This may be partially wrong, might already have done this...
            //valueToMatch = statementList.at(conclusionLocation).premiseList.at(premiseIter).value;
            //isValid = processConclusion(conclusionLocation, valueToMatch);
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


/*
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
        cout << "Result is " << knowledgeBase.at(conclusionLocation).conclusion.value << endl;
        cout << "conclusion is valid";
    }

    //not a conclusion
    if (conclusionLocation == 0)
    {
        cout << "no conclusion";
    }

}
*/