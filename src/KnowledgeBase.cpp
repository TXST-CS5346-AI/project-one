#include <iostream>
#include <fstream>
#include <stdexcept>

#include "KnowledgeBase.hpp"


KnowledgeBase::KnowledgeBase()
{
    std::cout << "\nCreating knowledge base instance..." << std::endl;
}

/**
 * populateKnowledgeBase - reads in a data file and creates the knowledge base (KB) 
 * accordingly, provided the right format is used. 
 * File format example
 * issue = Failure to Start ^ has_fuel = n : repair = Insufficient Fuel, Add more fuel.
 *
 * = is used to separate variable and value
 * ^ is logical AND
 * : separates clause and conclusion
 *
 * The above example should be read as follows. If issue is equal to failure to start, and has fuel is false
 * then repair conclusion equals "Insufficient Fuel, Add more fuel." 
 *
 * @param string fileName - the name of the file containing the knowledge base. knowledgeBase.txt
 *
 * @return none
 *
 */
void KnowledgeBase::populateKnowledgeBase(std::string fileName)
{
    int total_good = 0, total_bad = 0;

    std::string inputBuffer;
    std::ifstream inputFile;
    inputFile.open(fileName);

    if (inputFile)
    {
        while (getline(inputFile, inputBuffer))  // while read was successfull
        {
            std::cout << "Processing:  " << inputBuffer << std::endl;
            if (inputBuffer.size() > 0)
            {
                Statement lList;
                std::string listPremise;

                int indicatorLocation;
                if (isConclusionGood(lList, inputBuffer, listPremise))
                {
                    if (arePremisesGood(lList, listPremise))
                    {
                        std::cout << "Conclusion and premise(s) are good => List Updated\n";
                        kBase.push_back(lList);
                        ++total_good;
                    }
                    else
                    {
                        std::cout << "Premise List is formatted incorrectly.  List NOT updated\n";
                        ++total_bad;
                    }
                }
                else
                {
                    std::cout << "Conclusion is formatted incorrectly.  List NOT updated\n";
                    ++total_bad;
                }
            }
            std::cout << std::endl; 
        }
    }
    else {
        throw std::runtime_error("Error reading Knowledge Base (KB) file. Please validate it uses the correct format. Invoke application with -h or -help for details.");
    }
    std::cout << "\nKnowledge Base finished Loading.\n" << total_good << " items were loaded into the KnowledgeBase\n";
    if ( total_bad > 0 )
        std::cerr << "\nWARNING! " << total_bad << " malfromed item(s) were not loaded into the Knowledge Base. " << 
        "\nPlease check output above for items not loaded and inspect data file.\n";
    std::cout << "<CR/Enter> to continue  ";
    std::cin.ignore();
}

/**
 * isConclusionGood - helper function to check if the conclusion in the premise is valid and trim any white spaces
 * 
 * @param Statement& lList - a statement containing the premise list and the conclusion it leads to
 * @param std::string iBuffer - the entire statement (premise and conclusions)
 * @param std::string& listPremise - a list of the premises (left side of expression) 
 * 
 * @return bool - if the conclusion is valid, true. Otherwise false. 
 */
bool KnowledgeBase::isConclusionGood(Statement& lList, std::string iBuffer, std::string& listPremise)
{
    ClauseItem nClause;
    std::string listConclusion;
    int indicatorLocation = iBuffer.find(':', 0);  // THEN symbol

    if (indicatorLocation == -1)
        return false;

    listPremise = iBuffer.substr(0, indicatorLocation);
    listConclusion = iBuffer.substr(indicatorLocation + 1, iBuffer.size());
    indicatorLocation = listConclusion.find('=', 0);  // Assignment Symbol
    
    if (indicatorLocation == -1)
        return false;
    
    lList.conclusion.name = listConclusion.substr(0, indicatorLocation);
    
    // trim white spaces in conclusion name, first front, then back
    if (lList.conclusion.name.front() == ' ')
    {
        lList.conclusion.name = lList.conclusion.name.substr(1);
    }
    if (lList.conclusion.name.back() == ' ')
    {
        lList.conclusion.name = lList.conclusion.name.substr(0, lList.conclusion.name.size() - 1);
    }

    lList.conclusion.value = listConclusion.substr(indicatorLocation + 1, listConclusion.size());
    // trim white spaces in conclusion value, first front, then back
    if (lList.conclusion.value.front() == ' ')
    {
        lList.conclusion.value = lList.conclusion.value.substr(1);
    }
    if (lList.conclusion.value.back() == ' ')
    {
        lList.conclusion.value = lList.conclusion.value.substr(0, lList.conclusion.value.size() - 1);
    }

    lList.conclusion.type = STRING;
    conclusionSet.insert(lList.conclusion.name); // add conclusion to set, maintaining unique list of conclusions

    std::cout << "Conclusion is good; ";
    return true;
}

/**
 * isConclusionGood - helper function to check if the conclusion in the premise is valid and trim any white spaces
 * 
 * @param Statement& lList - a statement containing the premise list and the conclusion it leads to
 * @param std::string& listPremise - a list of the premises (left side of expression) 
 * 
 * @return bool - if the premise is valid, true. Otherwise false. 
 */
bool KnowledgeBase::arePremisesGood(Statement& lList, std::string listPremise)
{
    ClauseItem nClause;
    std::string listRight,
        listLeft,
        tmpList;
    do
    {
        int andLocation = listPremise.find('^', 0),
            equalsLocation;

        if (andLocation == -1 && listPremise.size() == 0) // no premise
            return false;

        if (andLocation == -1)
            andLocation = listPremise.size();

        tmpList = listPremise.substr(0, andLocation);
        listPremise.erase(0, andLocation + 1);
        equalsLocation = tmpList.find('=', 0);  // assignment Symbol

        if (equalsLocation == -1)
            return false;

        listRight = tmpList.substr(0, equalsLocation);
        listLeft = tmpList.substr(equalsLocation + 1, tmpList.size());

        if (listLeft.size() == 0 || listRight.size() == 0)  // missing something
            return false;

        // trim white space from clause name, first front then back
        nClause.name = listRight;
        if (nClause.name.front() == ' ')
        {
            nClause.name = nClause.name.substr(1);
        }
        if (nClause.name.back() == ' ')
        {
            nClause.name = nClause.name.substr(0, nClause.name.size() - 1);
        }

        // trim white space from clause value, first front then back
        nClause.value = listLeft;
        if (nClause.value.front() == ' ')
        {
            nClause.value = nClause.value.substr(1);
        }
        if (nClause.value.back() == ' ')
        {
            nClause.value = nClause.value.substr(0, nClause.value.size() - 1);
        }

        nClause.type = STRING;
        lList.premiseList.push_back(nClause);
    } while (listPremise.size() != 0);

    std::cout << "Premise list is good!  " << lList.premiseList.size() - 1 << " premise(s) loaded\n";
    return true;
}

/**
 * displayBase - prints out the imported knowledge base to the screen 
 * We iterate over the knowledge base vector and print the premise list 
 * and the conclusion they lead to in a human readable format. 
 */
void KnowledgeBase::displayBase()
{
    Statement n;
    unsigned int pntr = 1;
    while (pntr < kBase.size())
    {
        unsigned int pPntr = 1,
            lastPntr = kBase.at(pntr).premiseList.size();
        std::cout << pntr << ". IF ";
        while (pPntr < kBase.at(pntr).premiseList.size())
        {
            std::cout << kBase.at(pntr).premiseList.at(pPntr).name;
            pPntr++;
            if (pPntr < lastPntr)
                std::cout << " AND ";

        }
        std::cout << " THEN " << kBase.at(pntr).conclusion.name << std::endl;
        pntr++;
    }
}

/**
 * getConclusion - helper function, which allows to get a conclusion of a specific index in the KB
 * 
 * @param unsigned int index - position of the statement in the knowledge base vector, whose conclusion we want
 * 
 * @return std::string the string representation of the conclusion
 */ 
std::string KnowledgeBase::getConclusion(unsigned int index)
{
    return kBase.at(index).conclusion.name;
}

/**
 * getConclusion - helper function, which allows to get a conclusion of a specific index in the KB
 * 
 * @param unsigned int index - position of the statement in the knowledge base vector, whose conclusion we want
 * @param unsigned int index_1 - once we know which statement, we need to know which premise
 *                               as a statement may contain one or more premises. 
 * 
 * @return std::string the string representation of the premise
 */ 
std::string KnowledgeBase::getPremise(unsigned int index, unsigned int index_1)
{
    return kBase.at(index).premiseList.at(index_1).name;
}

