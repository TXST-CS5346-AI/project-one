#include"Statement.h"


//================================================================================
// Constructor | Statement | Statement
//
// Summary: Instantiates a default statement with NULL values. Note that if the 
//          knowledge base contains the value of NULL, some care must be taken.
//          However, a guard is in place as each index begins at element 1.
//
//================================================================================
Statement::Statement()
{
    conclusion.name = "NULL";
    conclusion.value = "NULL";
    conclusion.type = STRING;
    premiseList.push_back(ClauseItem());
}


//================================================================================
// Constructor | ClauseItem | ClauseItem
//
// Summary: Instantiates a statement item with the specified values. Statements
//          follow the pattern of premiseList then conclusion.
//          All types are currently set to type string.
//
// Inputs:  ClauseItem conclusionP: The conclusion portion of the statement
//          std::vector<ClauseItem>& premiseListP> :    A vector of premise 
//                                  clauses to be used in the statement.
//
//================================================================================
Statement::Statement(ClauseItem conclusionP, std::vector<ClauseItem>& premiseListP)
{
    conclusion = conclusionP;
    premiseList = premiseListP;
}