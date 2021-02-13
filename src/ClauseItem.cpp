#include <string>

#include "ClauseItem.h"

#define INT 1
#define STRING 2
#define FLOAT 3

ClauseItem::ClauseItem()
{
    name = "NULL";
    value = "NULL";
    type = STRING;
}

ClauseItem::ClauseItem(std::string nameP, std::string valueP, int typeP)
{
    name = nameP;
    value = valueP;
    type = typeP;
}

void ClauseItem::operator=(const ClauseItem& srcClause)
{
    name = srcClause.name;
    value = srcClause.value;
    type = srcClause.type;
}