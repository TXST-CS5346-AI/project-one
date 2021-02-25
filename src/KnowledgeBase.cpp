#include <iostream>
#include <fstream>

#include "Statement.h"
#include "KnowledgeBase.h"


KnowledgeBase::KnowledgeBase()
{

}

bool KnowledgeBase::populateKnowledgeBase(std::string fileName)
{
    int status;

    std::string inputBuffer;
    std::ifstream inputFile;
    inputFile.open(fileName);

    if (inputFile)
    {
        while (!inputFile.eof())
        {
            getline(inputFile, inputBuffer);
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
                        std::cout << "Conclusion and premise(s) are good => List has been Updated\n";
                        kBase.push_back(lList);
                    }
                    else
                        std::cout << "Premise List is formatted incorrectly.  List has not been updated\n";
                }
                else
                    std::cout << "Conclusion is formatted incorrectly.  List has not been updated\n";
            }
            std::cout << "Next item\n\n";
        }
    }
    else {
        std::cout << "Error reading file. " << std::endl;
    }

    return true;
}

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
    
    if (lList.conclusion.name.front() == ' ')
    {
        lList.conclusion.name = lList.conclusion.name.substr(1);
    }
    if (lList.conclusion.name.back() == ' ')
    {
        lList.conclusion.name = lList.conclusion.name.substr(0, lList.conclusion.name.size() - 1);
    }

    lList.conclusion.value = listConclusion.substr(indicatorLocation + 1, listConclusion.size());
    
    if (lList.conclusion.value.front() == ' ')
    {
        lList.conclusion.value = lList.conclusion.value.substr(1);
    }
    if (lList.conclusion.value.back() == ' ')
    {
        lList.conclusion.value = lList.conclusion.value.substr(0, lList.conclusion.value.size() - 1);
    }

    lList.conclusion.type = STRING;
    
    std::cout << "Conclusion is good\n";
    return true;
}

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
        nClause.name = listRight;
        if (nClause.name.front() == ' ')
        {
            nClause.name = nClause.name.substr(1);
        }
        if (nClause.name.back() == ' ')
        {
            nClause.name = nClause.name.substr(0, nClause.name.size() - 1);
        }
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
    std::cout << "Premise list is good!  " << lList.premiseList.size() - 1 << " premises has/have been loaded\n";
    return true;
}

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

std::string KnowledgeBase::getConclusion(unsigned int it)
{
    return kBase.at(it).conclusion.name;
}

std::string KnowledgeBase::getPremise(unsigned int it, unsigned int it1)
{
    return kBase.at(it).premiseList.at(it1).name;
}
