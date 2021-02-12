#include <string>

#include "VariableListItem.h"


VariableListItem::VariableListItem(std::string nameP, bool instantiatedP, std::string valueP, std::string descriptionP, int typeP)
{
    name = nameP;
    instantiated = instantiatedP;
    value = valueP;
    description = descriptionP;
    type = typeP;
}
