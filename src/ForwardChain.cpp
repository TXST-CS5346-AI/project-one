#include <iostream>

#include "ForwardChain.hpp"

/**
 * Member Function | ForwardChain | copyVariableList
 *
 * Summary: Copies over all values that were used to find the backward chaining
 *          conclusion from the clause variable list. This is part one of two.
 *          The second part will also bring over the intermediate conclusions.
 *
 * @param  const vector<VariableListItem>& srcVariableList:    The variable
 *                  list to be copied over. Each element is copied with the
 *                  current values instantiated by backward chaining.
 *
 */
void ForwardChain::copyVariableList(const std::vector<VariableListItem> &srcVariableList)
{
    //do start at 0 in this case, might as well copy over the NULL.
    for (int varListiter = 0; varListiter < srcVariableList.size(); varListiter++)
    {
        variableList.push_back(srcVariableList.at(varListiter));
        variableList.back().populateStatementIndex(ruleSystem);
    }
}

/**
 * Member Function | ForwardChain | addIntermediateConclusions
 *
 * Summary: Takes the intermediate conclusion list that was populated during
 *          backward chaining and adds it to the clause variable list. This is 
 *          needed due to forward chaining requiring all premise items to be in
 *          the clause variable list, which is different from backward chaining.
 *
 * @param  const vector<VariableListItem>& srcConclusionVariableList:  The
 *                  additional conclusion variable list items to copy into the
 *                  forward chaining clause variable list.
 *
 */
void ForwardChain::addIntermediateConclusions(const std::vector<VariableListItem> &srcConclusionVariableList)
{
    //do start at 0 in this case, might as well copy over the NULL.
    for (int conclListIter = 0; conclListIter < srcConclusionVariableList.size(); conclListIter++)
    {
        variableList.push_back(srcConclusionVariableList.at(conclListIter));
        variableList.back().populateStatementIndex(ruleSystem);
    }
}

/**
 * Member Function | ForwardChain | copyKnowledgeBase
 *
 * Summary: Copy the internal representation of the knowledge base over to be used
 *          inforward chaining.
 *
 * @param  const KnowledgeBase& srcKnowledgeBase:  The internal representation
 *          of the knowledge base to be used. Similar to what was done for 
 *          back chaining. 
 */
void ForwardChain::copyKnowledgeBase(const KnowledgeBase &srcKnowledgeBase)
{
    //do start at 0 in this case, might as well copy over the NULL.
    for (int kBaseIter = 0; kBaseIter < srcKnowledgeBase.kBase.size(); kBaseIter++)
    {
        ruleSystem.kBase.push_back(srcKnowledgeBase.kBase.at(kBaseIter));
    }
}

/**
 * Member Function | ForwardChain | runForwardChaining
 *
 * Summary: Entry point for running forward chaining. This is expected to run
 *          after backward chaining, as part of the suggested fix step.
 *
 */
void ForwardChain::runForwardChaining()
{
    ClauseItem queueTopPtr;
    int variableListEntry;
    int initialRepairEntry;

    queueTopPtr.name = "inconclusive";
    queueTopPtr.value = "no valid solution.";

    std::cout << std::endl
              << std::endl
              << "Now running forward chain" << std::endl;

    // Start the chain by looking for the very first prompt, does it have an issue.
    // Note that this will also prevent forward chaining from running if the user
    // entered in a bad value to resolve while back chaining.
    initialRepairEntry = getMatchingVariableListEntry("has_issue");

    if (variableList.at(initialRepairEntry).instantiated)
    {
        conclusionVariableQueue.push(ClauseItem(variableList.at(initialRepairEntry).name,
                                                variableList.at(initialRepairEntry).value,
                                                variableList.at(initialRepairEntry).type));
    }

    while (!conclusionVariableQueue.empty())
    {
        queueTopPtr = conclusionVariableQueue.front();
        std::cout << "Processing " << queueTopPtr.name << std::endl;
        // Note that this is the only location where the queue is reduced.
        conclusionVariableQueue.pop();

        //get the matching entry in the variable list, the value does not matter at this time.
        variableListEntry = getMatchingVariableListEntry(queueTopPtr.name);

        //go through the variable list's inverted index of statements and push any valid conclusions.
        //make sure to prompt for entry of any non instantiated.
        if (variableListEntry != -1)
        {
            processStatementIndex(variableListEntry);
        }
    }

    std::cout << "The final conclusion is - " << queueTopPtr.name << " - with a value of: " << queueTopPtr.value << std::endl;
}

/**
 * Member Function | ForwardChain | processStatementIndex
 *
 * Summary: Runs through an inverted index of the current variable list entry and
 *          checks to see which statements are to be processed due to its value.
 *          This step is part of the BFS, where each matching item
 *          is added to the queue for this particular entry before it is 
 *          popped off the queue and the next one is processed.
 *
 *  @param int variableListEntry: A numeric value of which variable list entry 
 *          is being processed. 
 *
 *  @return    None - note that this is indeed the case since the queue will be 
 *              added to if there is a valid value. If it is not valid, it is not
 *              added.
 */
void ForwardChain::processStatementIndex(int variableListEntry)
{
    int curStatement = 0;

    for (int variableListIter = 1; variableListIter < variableList.at(variableListEntry).statementIndex.size(); variableListIter++)
    {
        //           = The matching variable list entry  . The individual statment number
        curStatement = variableList.at(variableListEntry).statementIndex.at(variableListIter);
        if (true == processPremiseList(ruleSystem.kBase.at(curStatement).premiseList))
        {
            // Everything matched up, so move forward on adding it to the queue to be
            // processed.
            conclusionVariableQueue.push(ruleSystem.kBase.at(curStatement).conclusion);
        }
    }
}

/**
 * Member Function | ForwardChain | processPremiseList
 *
 * Summary: Takes a conclusion name and value and tries to find a statement
 *          that matches up to both. If it finds one and the recursive stack
 *          is done, that will be the solution. If the stack is not empty,
 *          that means that we just completed an intermediate step in the process.
 *
 * @param  vector<ClauseItem>& premiseList: the premise list of a particular
 *                      statement.
 *
 * @return bool isValid: Specifies if the premise clauses were all found
 *                  to be valid for a particular statement..
 *
 */
bool ForwardChain::processPremiseList(std::vector<ClauseItem> &premiseList)
{
    bool isValid = true;

    for (int premiseIter = 1; (isValid && premiseIter < premiseList.size()); premiseIter++)
    {
        isValid = instantiatePremiseClause(premiseList.at(premiseIter));
    }
    return isValid;
}

/**
 * Member Function | ForwardChain | instantiatePremiseClause
 *
 * Summary: Takes a single clause and verifies that it has been instantiated and
 *          that it matches up to the back chaining portion of diagnostics.
 *          Note that this varies slightly from back chaining and the typical
 *          behavior of the instantiation step.
 *
 * Preconditions: Backchaining has been ran and the variable list is populated
 *                  with the needed results.
 *
 * @param  string  conclusionName: The name of a conclusion to match up to. Used
 *                                  As the first part in checking if a statement
 *                                  is valid or not.
 *
 * @return isFound:    Specifies if the incoming clause is found within the 
 *                      variable list. 
 */
bool ForwardChain::instantiatePremiseClause(const ClauseItem &clause)
{
    bool isFound = false;

    // Look through the variable list and see if this particular clause has a valid match.
    for (int varListIter = 1; (!isFound && varListIter < variableList.size()); varListIter++)
    {
        if (variableList.at(varListIter).instantiated && clause.name == variableList.at(varListIter).name && clause.value == variableList.at(varListIter).value)
        {
            isFound = true;
        }
    }

    return isFound;
}

/**
 * Member Function | ForwardChain | getMatchingVariableListEntry
 *
 * Summary: Takes a conclusion name that was popped off of the queue and tries to 
 *          locate it in the variable list. Note that the variable list will only
 *          contain unique values.
 *
 * @param  string entryName: The name of the variable list entry to match up.
 *
 * @return int matchingEntryIndex: The location of the matching entry. Returns
 *                  -1 if it is not found.
 *
 */
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
