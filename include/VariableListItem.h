#ifndef VARIABLE_LIST_ITEM_H
#define VARIABLE_LIST_ITEM_H

#include <string>

class VariableListItem
{
public:
    VariableListItem(std::string nameP, bool instantiatedP, std::string valueP, std::string descriptionP, int typeP);
    std::string name;
    bool instantiated;
    std::string value;
    std::string description;
    int type;
};

#endif // !VARIABLE_LIST_ITEM_H
