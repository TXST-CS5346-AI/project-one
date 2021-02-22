#include <vector>
#include <string>

#include "KnowledgeBase.h"
#include "VariableListItem.h"


VariableListItem::
VariableListItem(std::string nameP, bool instantiatedP, std::string valueP, std::string descriptionP, int typeP)
{
    name = nameP;
    instantiated = instantiatedP;
    value = valueP;
    description = descriptionP;
    type = typeP;
    statementIndex.push_back(-1); // To keep in line with the other indexes. But use -1 to note bad values
}

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
