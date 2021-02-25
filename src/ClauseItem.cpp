#include <string>

#include "ClauseItem.h"

// These defines are used throughout the program to specify what type of clause
// is being processed. The current implementation is all strings. As such, they
// are retained only for future development.
#define INT 1
#define STRING 2
#define FLOAT 3


/**
 * Constructor | ClauseItem | ClauseItem
 *
 * Summary: Instantiates a default clause with NULL values. Note that if the 
 *          knowledge base contains the value of NULL, some care must be taken.
 *          However, a guard is in place as each index begins at element 1.
 *
 */
ClauseItem::ClauseItem()
{
    name = "NULL";
    value = "NULL";
    type = STRING;
}


/**
 * Constructor | ClauseItem | ClauseItem
 *
 * Summary: Instantiates a clause item with the specified values. Clauses follow
 *          the pattern of Name = Value. The type parameter is for future use.
 *          All types are currently set to type string.
 *
 * Inputs:  string nameP:   The name portion of the clause.
 *          string valueP:  The value portion of the clause.
 *          int typeP:      The type of clause that it is.
 *
 */
ClauseItem::ClauseItem(std::string nameP, std::string valueP, int typeP)
{
    name = nameP;
    value = valueP;
    type = typeP;
}


/**
 * Operator overload | ClauseItem | operator=
 *
 * Summary: Overloaded equals operator to copy over one clause to another.
 *
 * Inputs:  const ClauseItem& srcClause:    The clause that holds the name,
 *                                          value and type to be copied into the
 *                                          new clause.
 *
 */
void ClauseItem::operator=(const ClauseItem& srcClause)
{
    name = srcClause.name;
    value = srcClause.value;
    type = srcClause.type;
}
