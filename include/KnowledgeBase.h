#ifndef KNOWLEDGE_BASE_H
#define KNOWLEDGE_BASE_H

#include <vector>
#include <string>

#include "ClauseItem.h"
#include "Statement.h"

/*struct StatementItem {
    ClauseItem conclusionItem;
    std::vector<ClauseItem> premiseItem;
};*/

class KnowledgeBase {
private:
    //std::vector<StatementItem> kBase;

    //bool isConclusionGood(StatementItem&, std::string, std::string&);
    //bool arePremisesGood(StatementItem&, std::string);

    //std::vector<Statement> kBase;

    bool isConclusionGood(Statement&, std::string, std::string&);
    bool arePremisesGood(Statement&, std::string);

public:
    KnowledgeBase();  // Constructor
    void displayBase();  // Display Entire KnowledgeBase
    std::string getConclusion(unsigned int);  //  get a conclusion from index provided
    std::string getPremise(unsigned int, unsigned int);  // first UI is kBase index, second is premise index
    std::vector<Statement> kBase;
};


#endif //KNOWLEDGE_BASE_H