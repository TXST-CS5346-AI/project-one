#ifndef VARIABLE_LIST_ITEM_H
#define VARIABLE_LIST_ITEM_H

#include <string>
#include <vector>

#include "KnowledgeBase.hpp"

/**
* A list of variables and their associated values that must accompany the knowledgeBase.txt file
* The variablesList.csv file contains a comma delimited list of variables and their contents to display. 
* For example: 
* {@code is_distributor_cap_damaged,Is the distributor cap cracked or broken? (y/n),STRING} 
* 
* first value is the variable name, next is the description that will be displayed to the user if we need to obtain their
* input about this variable, and last is the type. Currently all variables are of string type, as we read them in via text file. 
*/
class VariableListItem
{
public:
    VariableListItem(std::string nameP, bool instantiatedP, std::string valueP, std::string descriptionP, int typeP);
    void populateStatementIndex(const KnowledgeBase& knowledgeBase);
    
    std::string name;
    bool instantiated;
    std::string value;
    std::string description;
    int type;
    std::vector<int>statementIndex;
};

#endif // !VARIABLE_LIST_ITEM_H

