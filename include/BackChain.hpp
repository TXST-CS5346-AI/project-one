#ifndef BACK_CHAIN_H
#define BACK_CHAIN_H

#include <string>
#include <vector>

#include "Statement.hpp"
#include "VariableListItem.hpp"
#include "ClauseItem.hpp"
#include"KnowledgeBase.hpp"

class BackChain
{
public:
    void populateLists();
    void runBackwardChaining();
    void populateVariableList(std::string);

    KnowledgeBase ruleSystem;
    std::vector<VariableListItem> variableList;

    // Due to the design of the system (use the info from the backward
    // chain to populate the forward chain), this list is needed
    // to keep track of the conclusions that were set.
    std::vector<VariableListItem> intermediateConclusionList;

private:
    int findValidConclusionInStatements(std::string conclusionName, int startingIndex, std::string stringToMatch);
    bool instantiatePremiseClause(const ClauseItem& clause);
    bool processPremiseList(const Statement& statement);
    void addToIntermediateConclusionList(const ClauseItem& intermediateConclusion);

};

#endif // !BACK_CHAIN_H

