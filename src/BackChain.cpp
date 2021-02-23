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

//================================================================================
// Member Function | BackChain | populateLists
//
// Summary: Populates the knowledge base and variable lists for the back
//          chaining portion of the program. Typically read from a csv or text
//          file. Takes the outside representation of the knowledge base and
//          allows the inference engine to act on it.
//
//================================================================================
void BackChain::populateLists()
{
    // To offest the vectors by 1, populate index 0 with NULL or Empty elements.
    ruleSystem.kBase.push_back(Statement());
    variableList.push_back(VariableListItem("Empty", false, "", "This is an error string", STRING));
    intermediateConclusionList.push_back(VariableListItem("Empty", false, "", "This is an error string", STRING));

    // Populate the knowledge base and variable list. 
    ruleSystem.populateKnowledgeBase("carKnowledgeBase.txt");
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
 
    if (variableListFile)
    {
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
    else
    {
        cout << "Could not fine the file" << endl;
    }


}

//================================================================================
// Member Function | BackChain | processPremiseList
//
// Summary: Processed the premise list of a given statement. This statement
//          can lead to a recursive call if the statement contains a conclusion
//          in its premise list.
//
// Preconditions:   The statement parameter was found to have a valid conclusion.
//
// Inputs:  Statement&  statement   :   An individual statement taken from the
//                                      knowledge base. It typically includes 
//                                      premise clauses that will be processed
//                                      in order to see if they are conclusions,
//                                      premise clauses, or just invalid.
//
//================================================================================
bool BackChain::processPremiseList(const Statement& statement)
{
    int solution = 0;
    bool isValid = true;
    int location = 0;
    int conclusionLocation = 0;
    string valueToMatch = "";


    // Process the premise list for a conclusion that was found to be valid.
    for (int premiseIter = 1; (isValid && premiseIter < statement.premiseList.size()); premiseIter++)
    {

        // Go through and if it is a conclusion on the premise side, 
        // back chain with it. 
        // This will cause another recursive call by adding a conclusion 
        // to the stack. It is this step that allows the removal of the actual
        // stack in back chaining.
        conclusionLocation = findValidConclusionInStatements(statement.premiseList.at(premiseIter).name, 1,
            statement.premiseList.at(premiseIter).value);

        // It is a conclusion but not valid
        if (conclusionLocation == -1)
        {
            isValid = false;
        }

        // It is a conclusion and valid
        if (conclusionLocation > 0)
        {
            isValid = true;

            // This step is not needed for the backward chaining portion. It is used
            // when farward chaining is to immediately follow backward chaining and
            // use values that have already been instantiated.
            addToIntermediateConclusionList(statement.premiseList.at(premiseIter));
        }

        // It was not a conclusion. Go to the clause variable list and 
        // check if it is instantiated as well as what the value was.
        if (conclusionLocation == 0)
        {
            isValid = instantiatePremiseClause(statement.premiseList.at(premiseIter));
        }
    }

    return isValid;
}

//================================================================================
// Member Function | BackChain | instantiatePremiseClause
//
// Summary: Checks to see if the single premise clause passed in has a matching
//          value to what exists in the clause variable list. If not, ask for
//          a value and then check.
//
// Postcondition:   The clause variable list, if it matches, will have the
//                  matching entry instantiated.
//
// Inputs:  const ClauseItem& clause:   An individual premise clause. Contains
//                                      a name and potentially a value.
//
// Outputs: bool isValid:   Returns if the individual premise clause was found
//                          to be valid by matching the name and value of the
//                          premise clause in the knowledge base to what is
//                          in the clause variable list.
//
//================================================================================
bool BackChain::instantiatePremiseClause(const ClauseItem& clause)
{
    bool isValid = false;
    bool isFound = false;

    // Go through the entire clause variable list and look for the matching
    // Entry. It has to find a match. If not, it could be the case that
    // The two are out of sync with eachother (the knowledge base and clause
    // variable list).
    for (int premiseClauseIter = 1; (!isFound && premiseClauseIter < variableList.size()); premiseClauseIter++)
    {
        // If the premise clause we are looking to resolve matches, check
        // its status.
        if (clause.name == variableList.at(premiseClauseIter).name)
        {
            isFound = true;

            // This means that it is the first time we encountered this
            // premise. We need more info and will get it in this step.
            if (!variableList.at(premiseClauseIter).instantiated)
            {
                std::cout << variableList.at(premiseClauseIter).description;
                std::cin >> variableList.at(premiseClauseIter).value;
                variableList.at(premiseClauseIter).instantiated = true;
            }

            // Clause variable list is guaranteed to be updated here.
            // It can now be safely compared to the incoming premise clause
            // value.
            if (variableList.at(premiseClauseIter).value == clause.value)
            {
                isValid = true;
            }
        }
    }
    
    // The premise clause we just looked at will either be good or bad.
    // One thing to note is that this is for an individual premise.
    return isValid;
}

//================================================================================
// Member Function | BackChain | findValidConclusionInStatements
//
// Summary: Takes a conclusion name and value and tries to find a statement
//          that matches up to both. If it finds one and the recursive stack
//          is done, that will be the solution. If the stack is not empty,
//          that means that we just completed an intermediate step in the process.
//
// Inputs:  string  conclusionName: The name of a conclusion to match up to. Used
//                                  As the first part in checking if a statement
//                                  is valid or not.
//          int     starting index: The first index location to begin searching
//                                  from. Typically a 1, but can be adjusted.
//          string  stringToMatch:  The value portion to be matched when searching
//                                  for a valid conclusion. It will take on
//                                  a value when this function is called
//                                  recursively.
//
// Outputs: int location:   Specifies the location of a conclusion.
//
//================================================================================
int BackChain::findValidConclusionInStatements(string conclusionName, int startingIndex, string stringToMatch)
{
    int location = 0;
    bool isConclusion = false;
    bool isValid = false;

    // This loop will go through the knowledge base and look for a matching 
    // conclusion in all of the statements. It initially is not trying to 
    // find a match to the conclusion value, as the first inquiry will be 
    // the open ended question that the user wants the system to solve.
    // It also begins at index 1 for the first run.
    for (int conclusionIter = startingIndex; (conclusionIter < ruleSystem.kBase.size() && !isValid); conclusionIter++)
    {
        // Check that the conclusion name matches what the user entered or
        // if the back chain is recursing, see if it matches the conclusion
        // Next in the list.
        if (conclusionName == ruleSystem.kBase.at(conclusionIter).conclusion.name)
        {
            // It matched the conclusion name, just that at this point.
            isConclusion = true;

            // Note the DONTCARE here. This allows the initial inquiry to go through
            // Since it is open ended. However, if not DONTCARE, the stringToMatch
            // Parameter that was passed in must match. This is due to the multi
            // purposing of this function. 
            if (stringToMatch == ruleSystem.kBase.at(conclusionIter).conclusion.value || stringToMatch == "DONTCARE")
            {
                // It matched the conclusion name (above) and now it also matched the 
                // value in the knowledge base. This needs to be fully processed.
                // Process premiseList will do just that for this statement.
                // If everything lines up, we are good.
                isValid = processPremiseList(ruleSystem.kBase.at(conclusionIter));

                if (isValid)
                {
                    // Everything matched up, conclusion name, conclusion value
                    // and the premises all were good.
                    location = conclusionIter;
                }
            }
        }
    }

    // There are actually three options here. -1 means that the conclusion name
    // was found, but it was not valid. This could happen if there is a bad
    // knowledge base or perhaps the user entered in a bad value, such as an x
    // instead of a y or n.
    //
    // The second option is 0, which means there was no match, no nothing.
    // This can happen if the user enters in a bad inquiry to start.
    //
    // The third option is the actual index of where a valid conclusion was found.
    if (isConclusion && !isValid)
    {
        location = -1;
    }

    // See comment right above this one for info on this return value.
    return location;
}

//================================================================================
// Member Function | BackChain | runBackwardChaining
//
// Summary: The entry point for starting the backward chain process. Asks
//          the user to enter the conclusion to solve and then runs.
//
//================================================================================
void BackChain::runBackwardChaining()
{

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

//================================================================================
// Member Function | BackChain | addToIntermediateConclusionList
//
// Summary: This function allows for intermediate conclusion clauses to be added
//          to the forward chaining variable list. This is needed in order to
//          run the forward chaining portion immediately after the backward
//          chaining portion. It allows for all entries including the resolved
//          intermediate conclusion clauses to be preserved. Note that the 
//          description field is not specific. This is entered in here only to
//          keep in line with the other entries. It will not actually be seen.
//
//================================================================================
void BackChain::addToIntermediateConclusionList(const ClauseItem& intermediateConclusion)
{
    intermediateConclusionList.push_back(
        VariableListItem(intermediateConclusion.name,
            true,
            intermediateConclusion.value,
            (intermediateConclusion.name + "(y/n)"),
            intermediateConclusion.type));
}