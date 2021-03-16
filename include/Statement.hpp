#ifndef STATEMENT_H
#define STATEMENT_H

#include <vector>

#include "ClauseItem.hpp"

/**
 * Represents a single line entry in the knowledge base file. 
 * 0 to n premises and 1 conclusion. A statement may be atomic (e.g., var = true). 
 * Here is an example of a statement (single line in KB file): 
 * {@code issue = Failure to Start ^ has_fuel = y ^ has_voltage = n : repair = Dead Battery, Change the battery.}
 * 
 * Here, we use intermediate variable issue (which may also be a conclusion). 
 * IF issue is equal to "Failure to Start AND (^ indicates logical AND) has_fuel is true AND 
 *    has_voltage is false THEN repair recommendation is "Dead Battery, Change the battery."
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

