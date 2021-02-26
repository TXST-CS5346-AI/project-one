#ifndef KNOWLEDGE_BASE_H
#define KNOWLEDGE_BASE_H

#include <vector>
#include <string>
#include <stdexcept>

#include "ClauseItem.hpp"
#include "Statement.hpp"


class KnowledgeBase 
{
public:
    KnowledgeBase();  // Constructor
    void displayBase();  // Display Entire KnowledgeBase
    void populateKnowledgeBase(std::string fileName);
    std::string getConclusion(unsigned int);  //  get a conclusion from index provided
    std::string getPremise(unsigned int, unsigned int);  // first UI is kBase index, second is premise index  
    std::vector<Statement> kBase;

private:
    bool isConclusionGood(Statement&, std::string, std::string&);
    bool arePremisesGood(Statement&, std::string);
};


#endif //KNOWLEDGE_BASE_H

