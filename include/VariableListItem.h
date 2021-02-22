#ifndef VARIABLE_LIST_ITEM_H
#define VARIABLE_LIST_ITEM_H

#include <string>
#include <vector>

#include "KnowledgeBase.h"

class VariableListItem
{
public:
    VariableListItem(std::string nameP, bool instantiatedP, std::string valueP, std::string descriptionP, int typeP);
    void populateStatementIndex(const KnowledgeBase& knowledgeBase);
    std::string name;
    bool instantiated;
    std::string value;
    std::string description;
    int type;
    std::vector<int>statementIndex;
};

#endif // !VARIABLE_LIST_ITEM_H
