#include <vector>
#include <string>

#include "KnowledgeBase.hpp"
#include "VariableListItem.hpp"


/**
 * Constructor | VariableListItem | VariableListItem
 *
 * Summary: Instantiates a variable item with the specified values. Note that no
 *          values are passed in to the statement index. This is because
 *          this index is only used for forward chaining and is populated
 *          at that time.
 *
 * @param string nameP:   Name of the clause variable .
 * @param bool instantiatedP: If it has been given a value. Will start as false.
 * @param string valueP:  Initial value of the clause.
 * @param string descriptionP: A prompt to display when assigning a value.
 * @param int typeP:  The type of clause, usually set to STRING.
 *
 */
VariableListItem::VariableListItem(std::string nameP, bool instantiatedP, std::string valueP, std::string descriptionP, int typeP)
{
    name = nameP;
    instantiated = instantiatedP;
    value = valueP;
    description = descriptionP;
    type = typeP;
    statementIndex.push_back(-1); // To keep in line with the other indexes. But use -1 to note bad values
}


/**
 * CMember function | VariableListItem | populateAtatementIndex
 *
 * Summary: Creates an inverted index to allow for quicker searching when using
 *          forward chaining. Also helps prevent the need to double search or 
 *          process needless entries.
 *
 * @param const KnowledgeBase& knowledgeBase: Used to find entries that match
 *          the name for this variable list entry.
 */
void VariableListItem::populateStatementIndex(const KnowledgeBase& knowledgeBase)
{
    bool isFound = false;

    for (int statementIter = 1; statementIter < knowledgeBase.kBase.size(); statementIter++)
    {
        isFound = false;
        for (int premiseIter = 1; (!isFound && premiseIter < knowledgeBase.kBase.at(statementIter).premiseList.size()); premiseIter++)
        {
            if (name == knowledgeBase.kBase.at(statementIter).premiseList.at(premiseIter).name)
            {
                isFound = true;
                statementIndex.push_back(statementIter);
            }
        }
    }
}

