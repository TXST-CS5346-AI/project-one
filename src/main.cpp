#pragma warning(disable : 4996)

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#define INT 1
#define STRING 2
#define FLOAT 3

using namespace std;

class ClauseItem
{
public:
    ClauseItem();
    ClauseItem(string nameP, string valueP, int typeP);
    void operator=(const ClauseItem& srcClause);
    string name;
    string value;
    int type;
};

ClauseItem::ClauseItem()
{
    name = "NULL";
    value = "NULL";
    type = STRING;
}

ClauseItem::ClauseItem(string nameP, string valueP, int typeP)
{
    name = nameP;
    value = valueP;
    type = typeP;
}

void ClauseItem::operator=(const ClauseItem& srcClause)
{
    name = srcClause.name;
    value = srcClause.value;
    type = srcClause.type;
}



class Statement
{
public:
    Statement();
    Statement(ClauseItem conclusionP, vector<ClauseItem> &premiseListP);
    ClauseItem conclusion;
    vector<ClauseItem> premiseList;
};
Statement::Statement()
{
    conclusion.name = "NULL";
    conclusion.value = "NULL";
    conclusion.type = STRING;
    premiseList.push_back(ClauseItem());
}
Statement::Statement(ClauseItem conclusionP, vector<ClauseItem> &premiseListP)
{
    conclusion = conclusionP;
    premiseList = premiseListP;
}

class VariableListItem
{
public:
    VariableListItem(string nameP, bool instantiatedP, string valueP, string descriptionP, int typeP);
    string name;
    bool instantiated;
    string value;
    string description;
    int type;
};
VariableListItem::VariableListItem(string nameP, bool instantiatedP, string valueP, string descriptionP, int typeP)
{
    name = nameP;
    instantiated = instantiatedP;
    value = valueP;
    description = descriptionP;
    type = typeP;
}

class BackChain
{
public:
    void populateLists();
    void runBackwardChaining();
    int findValidConclusionInStatements(string conclusionName, int startingIndex, string stringToMatch);
    bool instantiatePremiseClause(ClauseItem & clause);
    bool processConclusion(int conclusionLocation, string valueToMatch);
    bool processPremiseList(Statement & statement, string stringToMatch);


    vector<Statement> statementList;
    vector<VariableListItem> variableList;
};



void BackChain::populateLists()
{
    statementList.push_back(Statement());
    variableList.push_back(VariableListItem("Empty", false, "", "This is an error string", STRING));
   
    //from the knowledge base transform each statement as follows:
    //for each statement in the knowledge base:
    //  get the conclusion name from the statement.
    //  append name to conclusion list (can have duplicates).
    //  append name to clause list variable(can have duplicates).
    //  for each premise clause in the statement:
    //      append it to the clause variable list
    //

}

bool BackChain::processConclusion(int conclusionLocation, string valueToMatch)
{
    int solution = 0;
    bool isValid = true;
    int location = 0;

    for (int premiseIter = 1; (isValid && statementList.at(conclusionLocation).premiseList.size()); premiseIter++)
    {
        conclusionLocation = findValidConclusionInStatements(statementList.at(conclusionLocation).premiseList.at(premiseIter).name, 1, "");
        
        if (conclusionLocation != 0)
        {
            isValid = processConclusion(conclusionLocation, valueToMatch);
        }
        else
        {
            isValid = instantiatePremiseClause(statementList.at(conclusionLocation).premiseList.at(premiseIter));
        }
    }

    return isValid;
}

bool BackChain::processPremiseList(Statement & statement, string stringToMatch)
{
    int solution = 0;
    bool isValid = true;
    int location = 0;
    int conclusionLocation = 0;
    string valueToMatch = "";

        for (int premiseIter = 1; (isValid && statement.premiseList.size()); premiseIter++)
        {
            //go through the entire list and see if there is a valid one
            conclusionLocation = findValidConclusionInStatements(statementList.at(conclusionLocation).premiseList.at(premiseIter).name, 1,
                                 statementList.at(conclusionLocation).premiseList.at(premiseIter).value);

            //is a conclusion but not valid
            if (conclusionLocation == -1)
            {
                isValid = false;
            }

            //is a conclusion and valid
            if (conclusionLocation >= 0)
            {
                isValid = true;
                //This may be partially wrong, might already have done this...
                //valueToMatch = statementList.at(conclusionLocation).premiseList.at(premiseIter).value;
                //isValid = processConclusion(conclusionLocation, valueToMatch);
            }
            
            //not a conclusion
            if(conclusionLocation == 0)
            {
                isValid = instantiatePremiseClause(statementList.at(conclusionLocation).premiseList.at(premiseIter));
            }
        }

    return true;
}

bool BackChain::instantiatePremiseClause(ClauseItem & clause)
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
                cout << variableList.at(premiseClauseIter).description;
                cin >> variableList.at(premiseClauseIter).value;
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


    for (int conclusionIter = startingIndex; (conclusionIter < statementList.size() && !isValid ); conclusionIter++)
    {
        if (conclusionName == statementList.at(conclusionIter).conclusion.name)
        {
            isConclusion = true;
            
            if (stringToMatch != statementList.at(conclusionIter).conclusion.value || stringToMatch == "DONTCARE")
            {
                isValid = processPremiseList(statementList.at(conclusionIter), stringToMatch);

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

void displayResults(int conclusion)
{
    // find the appropriate result string from the knowledge base 
    // and display it.
    if (0 == conclusion)
    {
        cout << "No conclusion was able to be made.";
    }
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
        if (conclusionLocation >= 0)
        {

            cout << "conclusion is valid";
        }

        //not a conclusion
        if (conclusionLocation == 0)
        {
            cout << "no conclusion";
        }

}

int main()
{
    BackChain backChain;
    backChain.populateLists();
    backChain.runBackwardChaining();
    
    return 0;
}