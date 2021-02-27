#ifndef STATEMENT_H
#define STATEMENT_H

#include <vector>

#include "ClauseItem.hpp"

class Statement
{
public:
    Statement();
    Statement(ClauseItem conclusionP, std::vector<ClauseItem>& premiseListP);
    ClauseItem conclusion;
    std::vector<ClauseItem> premiseList;
};

#endif // !STATEMENT_H

