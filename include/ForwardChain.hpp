#ifndef FORWARD_CHAIN_H
#define FORWARD_CHAIN_H

#include <string>
#include <vector>
#include <queue>

#include "Statement.hpp"
#include "VariableListItem.hpp"
#include "ClauseItem.hpp"
#include"KnowledgeBase.hpp"

class ForwardChain
{
public:
    void runForwardChaining();
    void copyVariableList(const std::vector<VariableListItem>& srcVariableList);
    void copyKnowledgeBase(const KnowledgeBase& srcKnowledgeBase);
    int getMatchingVariableListEntry(std::string entryName);
    void addIntermediateConclusions(const std::vector<VariableListItem>& srcConclusionVariableList);
    
    std::queue<ClauseItem> conclusionVariableQueue;

    KnowledgeBase ruleSystem;
    std::vector<VariableListItem> variableList;

private:
    void processStatementIndex(int variableListEntry);
    bool instantiatePremiseClause(const ClauseItem& clause);
    bool processPremiseList(std::vector<ClauseItem>& premiseList);


};

#endif // !FORWARD_CHAIN_H

