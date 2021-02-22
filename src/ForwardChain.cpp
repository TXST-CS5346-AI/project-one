
#include <iostream>
#include <string>
#include <vector>
#include <queue>

#include "ForwardChain.h"
#include "Statement.h"
#include "VariableListItem.h"
#include "ClauseItem.h"
#include"KnowledgeBase.h"


//================================================================================
//
//
//================================================================================
void ForwardChain::copyVariableList
(const std::vector<VariableListItem> & srcVariableList)
{
    //do start at 0 in this case, might as well copy over the NULL.
    for (int VarListiter = 0; VarListiter < srcVariableList.size(); VarListiter++)
    {
        variableList.push_back(srcVariableList.at(VarListiter));
        variableList.back().populateStatementIndex(ruleSystem);
    }

    VariableListItem quickCheck("QUALIFY", true, "YES", "Do they qualify: ", STRING);
    quickCheck.statementIndex.push_back(4);
    quickCheck.statementIndex.push_back(5);
    quickCheck.statementIndex.push_back(6);

    variableList.push_back(quickCheck);

}

void ForwardChain::copyKnowledgeBase(const KnowledgeBase& srcKnowledgeBase)
{
    //do start at 0 in this case, might as well copy over the NULL.
    for (int kBaseIter = 0; kBaseIter < srcKnowledgeBase.kBase.size(); kBaseIter++)
    {
        ruleSystem.kBase.push_back(srcKnowledgeBase.kBase.at(kBaseIter));
    }
}

void ForwardChain::runForwardChaining()
{
    ClauseItem queueTopPtr;
    int variableListEntry;

    // Need to determine start of our chain, perhaps just the is the car broken one...
    // This will be removed when we get in our actual KB..
    // Working on that right now...
    conclusionVariableQueue.push(ClauseItem("DEGREE", "YES", STRING));

    while (!conclusionVariableQueue.empty())
    {
        queueTopPtr = conclusionVariableQueue.front();
        std::cout << "Processing " << queueTopPtr.name << std::endl;
        conclusionVariableQueue.pop();

        //get the matching entry in the variable list, the value does not matter at this time.
        variableListEntry = getMatchingVariableListEntry(queueTopPtr.name);


        //go through the variable list's inverted index of statements and push any valid conclusions.
        //make sure to prompt for entry of any non instantiated.
        //maybe turn this into a function?
        bool isValid = false;
        int curStatement;
        if (variableListEntry != -1)
        {
            for (int variableListIter = 1; variableListIter < variableList.at(variableListEntry).statementIndex.size(); variableListIter++)
            {
                //           = The matching variable list entry  . The individual statment number
                curStatement = variableList.at(variableListEntry).statementIndex.at(variableListIter);
                if (true == processPremiseList(ruleSystem.kBase.at(curStatement).premiseList))
                {
                    conclusionVariableQueue.push(ruleSystem.kBase.at(curStatement).conclusion);
                }
            }
        }
        //probably do not need this exactly...
        /*
        for (int statementIter = 1; statementIter < ruleSystem.kBase.size(); statementIter++)
        {
            //This is a problem...
            if (true == processPremiseList(ruleSystem.kBase.at(statementIter).premiseList))
            {
                std::cout << "Pushing " << ruleSystem.kBase.at(statementIter).conclusion.name << "to queue of size: " << conclusionVariableQueue.size() << std::endl;
                conclusionVariableQueue.push(ruleSystem.kBase.at(statementIter).conclusion);
                
            }
        }
        */
    }

    std::cout << "The final conclusion is " << queueTopPtr.name << " with a value of " << queueTopPtr.value << std::endl;
}

//We know it has the matching conclusion or prompt when this is called.
//For each entry in the premise list, make sure it is valid.
bool ForwardChain::processPremiseList(std::vector<ClauseItem>& premiseList)
{
    bool isValid = true;

    for (int premiseIter = 1; (isValid && premiseIter < premiseList.size()); premiseIter++)
    {
        isValid = instantiatePremiseClause(premiseList.at(premiseIter));
    }
    return isValid;
}

//For the premise clause found in the statement, make sure it matches the variable list one.
bool ForwardChain::instantiatePremiseClause(ClauseItem& clause)
{
    bool isFound = false;

    for (int varListIter = 1; ( !isFound && varListIter < variableList.size()); varListIter++)
    {
        if (variableList.at(varListIter).instantiated
            && clause.name == variableList.at(varListIter).name
            && clause.value == variableList.at(varListIter).value)
        {
            isFound = true;
        }
    }
    return isFound;
}

int ForwardChain::getMatchingVariableListEntry(std::string entryName)
{
    int matchingEntryIndex = -1;
    bool isFound = false;

    for (int variableListIter = 1; (!isFound && variableListIter < variableList.size()); variableListIter++)
    {
        if (entryName == variableList.at(variableListIter).name)
        {
            isFound = true;
            matchingEntryIndex = variableListIter; 
        }
    }

    return matchingEntryIndex;
}


