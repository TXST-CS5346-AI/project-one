#ifndef CLAUSE_ITEM_H
#define CLAUSE_ITEM_H

#include <string>

#define INT 1
#define STRING 2
#define FLOAT 3

class ClauseItem
{
public:
    std::string name;
    std::string value;
    int type;

    ClauseItem();
    ClauseItem(std::string nameP, std::string valueP, int typeP);
    void operator=(const ClauseItem& srcClause);

};

#endif // !CLAUSE_ITEM_H
