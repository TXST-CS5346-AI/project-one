#ifndef STATEMENT_H
#define STATEMENT_H

#include <vector>

#include "ClauseItem.hpp"

/**
 * Represents a single line entry in the knowledge base file. 
 * 0 to n premises and 1 conclusion. A statement may be atomic (e.g., var = true). 
 * 
 */ 
class Statement
{
public:
    Statement();
    Statement(ClauseItem conclusionP, std::vector<ClauseItem>& premiseListP);
    ClauseItem conclusion;
    std::vector<ClauseItem> premiseList;
};

#endif // !STATEMENT_H

