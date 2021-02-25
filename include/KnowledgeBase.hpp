#ifndef KNOWLEDGE_BASE_H
#define KNOWLEDGE_BASE_H

#include <vector>
#include <string>

#include "ClauseItem.h"
#include "Statement.h"


class KnowledgeBase {

private:
    bool isConclusionGood(Statement&, std::string, std::string&);
    bool arePremisesGood(Statement&, std::string);

public:
    KnowledgeBase();  // Constructor
    void displayBase();  // Display Entire KnowledgeBase
    bool populateKnowledgeBase(std::string fileName);
    std::string getConclusion(unsigned int);  //  get a conclusion from index provided
    std::string getPremise(unsigned int, unsigned int);  // first UI is kBase index, second is premise index
  
    std::vector<Statement> kBase;
};


#endif //KNOWLEDGE_BASE_H

