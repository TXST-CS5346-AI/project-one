#ifndef FORWARD_CHAIN_H
#define FORWARD_CHAIN_H

#include <string>
#include <vector>
#include <queue>

#include "Statement.h"
#include "VariableListItem.h"
#include "ClauseItem.h"
#include"KnowledgeBase.h"

class ForwardChain
{
public:
    void runForwardChaining();
    bool instantiatePremiseClause(ClauseItem& clause);
    bool processPremiseList(std::vector<ClauseItem>& premiseList);
    void copyVariableList(const std::vector<VariableListItem>& srcVariableList);
    void copyKnowledgeBase(const KnowledgeBase& srcKnowledgeBase);
    int getMatchingVariableListEntry(std::string entryName);

    std::queue<ClauseItem> conclusionVariableQueue;

    KnowledgeBase ruleSystem;
    std::vector<VariableListItem> variableList;
};

#endif // !FORWARD_CHAIN_H