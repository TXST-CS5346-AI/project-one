#ifndef KNOWLEDGE_BASE_H
#define KNOWLEDGE_BASE_H

#include <vector>
#include <string>
#include <set>

#include "ClauseItem.hpp"
#include "Statement.hpp"

/**
* KnowledgeBase - parses a text file of statements and acts as a database; it contains a vector of statement.
* This class allows us to more clearly separate the knowledge base from the inference enginge. 
*/
class KnowledgeBase 
{
public:
    KnowledgeBase();  // Constructor
    void displayBase();  // Display Entire KnowledgeBase
    void populateKnowledgeBase(std::string fileName);
    std::string getConclusion(unsigned int);  //  get a conclusion from index provided
    std::string getPremise(unsigned int, unsigned int);  // first UI is kBase index, second is premise index  
    std::vector<Statement> kBase;
    std::set<std::string> conclusionSet;
private:
    bool isConclusionGood(Statement&, std::string, std::string&);
    bool arePremisesGood(Statement&, std::string);
};


#endif //KNOWLEDGE_BASE_H

