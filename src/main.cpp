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
    int findConclusionInStatements(string conclusionName, int startingIndex);
    bool instantiateClause(ClauseItem & clause);
    bool processConclusion(int conclusionLocation);

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

bool BackChain::processConclusion(int conclusionLocation )
{
    int solution = 0;
    bool isValid = true;
    int location = 0;

    for (int premiseIter = 1; (isValid && statementList.at(conclusionLocation).premiseList.size()); premiseIter++)
    {
        conclusionLocation = findConclusionInStatements(statementList.at(conclusionLocation).premiseList.at(premiseIter).name, 1);
        
        if (conclusionLocation != 0)
        {
            isValid = processConclusion(conclusionLocation);
        }
        else
        {
            isValid = instantiateClause(statementList.at(conclusionLocation).premiseList.at(premiseIter));
        }
    }

    return isValid;
}

bool BackChain::instantiateClause(ClauseItem & clause)
{
    bool isValid = true;

    for (int clauseIter = 1; clauseIter < variableList.size(); clauseIter++)
    {

    }

    return isValid;

}

int BackChain::findConclusionInStatements(string conclusionName, int startingIndex)
{
    int location = 0;
    bool isFound = false;

    for (int listIter = startingIndex; (!isFound && listIter < statementList.size()); listIter++)
    {
        if (conclusionName == statementList.at(listIter).conclusion.name)
        {
            location = listIter;
            isFound = true;
        }
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

    vector<string> conclusionList; // must align with knowledge base and clause variable list

    //no need for conclusion stack, will actually be the recursive stack

    string conclusionToSolve = "";
    int conclusionLocation = 0;
    bool isSolvedStatement = false;

    cout << "Please enter a conclusion to solve: ";
    cin >> conclusionToSolve;

    for (int curConclusionIter = 1; (curConclusionIter < conclusionList.size() && !isSolvedStatement); curConclusionIter++)
    {
        conclusionLocation = findConclusionInStatements(conclusionToSolve, curConclusionIter);
        if (0 != conclusionLocation)
        {
            isSolvedStatement = processConclusion(conclusionLocation);
        }
    }

    if (isSolvedStatement)
    {
        //do something with conclusionLocation        
    }
    else
    {
        cout << "No valid Solutions";
    }

}

int main()
{
    BackChain backChain;
    backChain.populateLists();
    backChain.runBackwardChaining();
    
    return 0;
}