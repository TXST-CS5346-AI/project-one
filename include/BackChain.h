#ifndef BACK_CHAIN_H
#define BACK_CHAIN_H

#include <string>
#include <vector>

#include "Statement.h"
#include "VariableListItem.h"
#include "ClauseItem.h"
#include"KnowledgeBase.h"

class BackChain
{
public:
    void populateLists();
    void runBackwardChaining();
    int findValidConclusionInStatements(std::string conclusionName, int startingIndex, std::string stringToMatch);
    bool instantiatePremiseClause(const ClauseItem& clause);
    bool processPremiseList(const Statement& statement, std::string stringToMatch);
    void populateVariableList(std::string);

    KnowledgeBase ruleSystem;
    std::vector<VariableListItem> variableList;
};

#endif // !BACK_CHAIN_H
