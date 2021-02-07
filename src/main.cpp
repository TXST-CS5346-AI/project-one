#pragma warning(disable : 4996)

#include <iostream>
#include <stack>
#include <queue>
#include <cstring>
#include <string>
#include <fstream>

#define INT 1
#define STRING 2
#define FLOAT 3

using namespace std;

class ConclusionStackItem
{
public:
    ConclusionStackItem(int ruleNum, int clauseNum);
    int ruleNumber;
    int clauseNumber;
};
ConclusionStackItem::ConclusionStackItem(int ruleNum, int clauseNum)
{
    ruleNumber = ruleNum;
    clauseNumber = clauseNum;
}

class VariableListItem
{
public:
    VariableListItem(string nameP, bool instantiatedP, string valueP, string descriptionP, int typeP);
    string name;
    bool instantiated;
    string value;
    string description;
    int type;
};
VariableListItem::VariableListItem(string nameP, bool instantiatedP, string valueP, string descriptionP, int typeP)
{
    name = nameP;
    instantiated = instantiatedP;
    value = valueP;
    description = descriptionP;
    type = typeP;
}


class BackwardChaining
{
private:
    //  string conclusionList[10];
    char conclusion_list[10][3];
    char variable_list[10][3];
    char clause_variable_list[40][3];
    string clauseVariableListS[40];

    bool solutionFound;
    bool validExpression;
    string results;
    char response[3];
    string responseS;
    char qualify[4], degree[4];
    char discovery[4], position[4];
    char buff[128];

    int ruleNumber;
    int instantiated_list[11];
    int rule_stack[11];
    int clause_stack[11];
    int clauseVariableListIter;

    float gpa;
    float experience;

    stack<ConclusionStackItem> conclusionStack;
    vector<VariableListItem> variableList;
    vector<string> conclusionList;

public:
    BackwardChaining();
    int findValInConclusionList(char conclusionToFind[], int startIndex);
    void chaining(int);
    void runChaining();
    void pushOnConclusionStack(int ruleNumber, int clauseNumber);
    void instantiate(void);
    void parseKnowledgeBase();
    void presentSolution();
    int getClauseVarListItem(int ruleNumber, int clauseNumber);
    bool validateStatement(int ruleNumber);
};

int BackwardChaining::getClauseVarListItem(int ruleNumber, int clauseNumber)
{
    return ((ruleNumber - 1) * 4 + clauseNumber);
}

void BackwardChaining::parseKnowledgeBase()
{
    string inputBuffer;
    char parsedToken;
    ifstream inputFile;
    inputFile.open("knowledgeBase.txt");
    if (inputFile)
    {
        while (!inputFile.eof())
        {
            getline(inputFile, inputBuffer);
            inputFile >> parsedToken;
            cout << inputBuffer << endl;
        }
    }
    else
    {
        cout << "Error reading file. " << endl;
    }



}

BackwardChaining::BackwardChaining()
{
    /***** initialization section ******/
    int curIter = 0;

    solutionFound = false;
    results = "Inconclusive";
    validExpression = false;
    //parseKnowledgeBase();

    for (curIter = 1; curIter < 11; curIter++)
    {
        strcpy(conclusion_list[curIter], "");
        strcpy(variable_list[curIter], "");
        instantiated_list[curIter] = 0;
        rule_stack[curIter] = 0;
        clause_stack[curIter] = 0;
    }

    clauseVariableListS[0] = "";
    for (curIter = 1; curIter < 40; curIter++)
    {
        strcpy(clause_variable_list[curIter], "");
        clauseVariableListS[curIter] = "";
    }
    conclusionList.push_back("PO");
    conclusionList.push_back("QU");
    conclusionList.push_back("PO");
    conclusionList.push_back("PO");
    conclusionList.push_back("PO");
    conclusionList.push_back("PO");

    strcpy(conclusion_list[1], "PO");
    strcpy(conclusion_list[2], "QU");
    strcpy(conclusion_list[3], "PO");
    strcpy(conclusion_list[4], "PO");
    strcpy(conclusion_list[5], "PO");
    strcpy(conclusion_list[6], "PO");

    variableList.push_back(VariableListItem("DE", false, "", "INPUT YES OR NO FOR DEGREE: ", STRING));
    variableList.push_back(VariableListItem("DI", false, "", "INPUT YES OR NO FOR DISCOVERY: ", STRING));
    variableList.push_back(VariableListItem("EX", false, "", "INPUT A REAL NUMBER FOR EXPERIENCE: ", FLOAT));
    variableList.push_back(VariableListItem("GR", false, "", "INPUT A REAL NUMBER FOR GPA: ", FLOAT));

    strcpy(variable_list[1], "DE");
    strcpy(variable_list[2], "DI");
    strcpy(variable_list[3], "EX");
    strcpy(variable_list[4], "GR");

    strcpy(clause_variable_list[1], "DE");
    strcpy(clause_variable_list[5], "DE");
    strcpy(clause_variable_list[9], "DE");
    strcpy(clause_variable_list[10], "DI");
    strcpy(clause_variable_list[13], "QU");
    strcpy(clause_variable_list[14], "GR");
    strcpy(clause_variable_list[15], "EX");
    strcpy(clause_variable_list[17], "QU");
    strcpy(clause_variable_list[18], "GR");
    strcpy(clause_variable_list[19], "EX");
    strcpy(clause_variable_list[21], "QU");
    strcpy(clause_variable_list[22], "GR");
}

void BackwardChaining::runChaining()
{
    char response[3];
    int ruleNumber = 0;

    cout << "** ENTER CONCLUSION ? ";
    // cin >> responseS;
    //string response;

    cin.getline(response, 3);

    ruleNumber = findValInConclusionList(response, 1);
    if (ruleNumber != 0)
    {
        chaining(ruleNumber);
    }

}


void BackwardChaining::chaining(int ruleNumberP)
{
    ruleNumber = ruleNumberP;
    do
    {
        pushOnConclusionStack(ruleNumber, 1); //ruleNumber will not be 0 here no matter what.

        do // Resolve clauses as either instantiated or on conclusion list
        {
        b545:
            clauseVariableListIter = getClauseVarListItem(conclusionStack.top().ruleNumber, conclusionStack.top().clauseNumber);
            responseS = clause_variable_list[clauseVariableListIter];
            strcpy(response, clause_variable_list[clauseVariableListIter]);

            if (responseS != "")
            {

                ruleNumber = findValInConclusionList(response, 1);
                if (ruleNumber != 0)
                {
                    chaining(ruleNumber);
                }

                instantiate();

                if (!conclusionStack.empty())
                {
                    conclusionStack.top().clauseNumber = conclusionStack.top().clauseNumber + 1;
                }
            }

        } while (strcmp(response, "") != 0); //Resolve clauses

        /*no more clauses check if part of statement */
        if (!conclusionStack.empty())
        {
            ruleNumber = conclusionStack.top().ruleNumber;
        }
        validExpression = false;
        /**** if then statements ****/
        /* sample if parts of if then statements from
            the position knowledge base */
        switch (ruleNumber)
        {
        case 1: if (strcmp(degree, "NO") == 0) validExpression = true;
            break;
        case 2: if (strcmp(degree, "YES") == 0) validExpression = true;
            break;
        case 3: if ((strcmp(degree, "YES") == 0) &&
            (strcmp(discovery, "YES") == 0)) validExpression = true;
            break;
        case 4: if ((strcmp(qualify, "YES") == 0) &&
            (gpa < 3.5) && (experience >= 2)) validExpression = true;
            break;
        case 5: if ((strcmp(qualify, "YES") == 0) &&
            (gpa < 3.5) && (experience < 2)) validExpression = true;
            break;
        case 6: if ((strcmp(qualify, "YES") == 0) &&
            (gpa >= 3.5)) validExpression = true;
            break;
        }
        /* see if the then part should be invoked */
        if (validExpression == false)
        {
            /* failed..search rest of statements for
                same conclusion */
                /* get conclusion */
            strcpy(response, conclusion_list[conclusionStack.top().ruleNumber]);
            /* search for conclusion starting at the
                next statement number */
            ruleNumber = findValInConclusionList(response, conclusionStack.top().ruleNumber + 1);
            if (!conclusionStack.empty())
            {
                conclusionStack.pop();
            }
        }
        /* pop old conclusion and put on new one */
    } while ((validExpression == false) && (ruleNumber != 0));  /* outer do-while loop */

    if (ruleNumber != 0)
    {
        /* if part true invoke then part */
        /* then part of if-then statements from the
        position knowledge base */
        switch (ruleNumber) {
        case 1:
            strcpy(position, "NO");
            //cout << "PO=NO\n";
            results = "No position offered.";
            break;
        case 2:
            strcpy(qualify, "YES");
            //cout << "QU=YES\n";
            results = "Candidate qualifies for a position.";
            break;
        case 3:
            strcpy(position, "YES");
            //cout << "PO=RESEARCH\n";
            results = "Offer a position in research.";
            break;
        case 4:
            strcpy(position, "YES");
            //cout << "PO=SERVICE ENGINEER\n";
            results = "Offer a service engineer position.";
            break;
        case 5:
            strcpy(position, "NO");
            //cout << "PO=NO";
            results = "No position offered.";
            break;
        case 6:
            strcpy(position, "YES");
            //cout << "PO=PRODUCT ENGINEER\n";
            results = "Offer a product engineer position.";
            break;
        }
        if (!conclusionStack.empty())
        {
            conclusionStack.pop();
        }
        if (conclusionStack.empty())
        {
            solutionFound = true;
            //cout << "*** SUCCESS\n" << endl;
        }
        else
        {
            conclusionStack.top().clauseNumber = conclusionStack.top().clauseNumber + 1;
            goto b545;
        }
    }

}

bool BackwardChaining::validateStatement(int ruleNumber)
{
    bool validExpression = false;
    /**** if then statements ****/
    /* sample if parts of if then statements from
        the position knowledge base */
    switch (ruleNumber)
    {
    case 1: if (strcmp(degree, "NO") == 0) validExpression = true;
        break;
    case 2: if (strcmp(degree, "YES") == 0) validExpression = true;
        break;
    case 3: if ((strcmp(degree, "YES") == 0) &&
        (strcmp(discovery, "YES") == 0)) validExpression = true;
        break;
    case 4: if ((strcmp(qualify, "YES") == 0) &&
        (gpa < 3.5) && (experience >= 2)) validExpression = true;
        break;
    case 5: if ((strcmp(qualify, "YES") == 0) &&
        (gpa < 3.5) && (experience < 2)) validExpression = true;
        break;
    case 6: if ((strcmp(qualify, "YES") == 0) &&
        (gpa >= 3.5)) validExpression = true;
        break;
    }
    /* see if the then part should be invoked */
    if (validExpression == false)
    {
        /* failed..search rest of statements for
            same conclusion */
            /* get conclusion */
        strcpy(response, conclusion_list[conclusionStack.top().ruleNumber]);
        /* search for conclusion starting at the
            next statement number */
        ruleNumber = findValInConclusionList(response, conclusionStack.top().ruleNumber + 1);
        if (!conclusionStack.empty())
        {
            conclusionStack.pop();
        }
    }
    /* pop old conclusion and put on new one */
}

void BackwardChaining::pushOnConclusionStack(int ruleNumberP, int clauseNumberP)
{
    conclusionStack.push(ConclusionStackItem(ruleNumberP, clauseNumberP));
}


int BackwardChaining::findValInConclusionList(char conlusionToFind[], int startIndex)
{

    startIndex--;
    int indexLocation = 0; // Not found = 0
    bool found = false;

    for (int curIndex = startIndex; curIndex < conclusionList.size() && (!found); curIndex++)
    {
        if (conclusionList.at(curIndex) == conlusionToFind)
        {
            indexLocation = curIndex;
            found = true;
        }

    }

    if (!found)
    {
        return 0;
    }
    return indexLocation + 1;
}

void BackwardChaining::instantiate()
/* routine to instantiate a variable (response) if it isn't already.  the
instantiate indication (instantiated_list) is a 0 if not, a 1 if it is.  the
variable list (varlt) contains the variable (response). */
{
    int curIter = 1;
    /* find variable in the list */
    while ((strcmp(response, variable_list[curIter]) != 0) && (curIter < 10)) curIter = curIter + 1;
    if ((strcmp(response, variable_list[curIter]) == 0) && (instantiated_list[curIter] != 1))
        /*found variable and not already instantiated */
    {
        instantiated_list[curIter] = 1; /*mark instantiated */
        /* the designer of the
       knowledge base places the input statements to
       instantiate the variables below in the case statement */
        switch (curIter)
        {
        case 1: cout << "INPUT YES OR NO FOR DEGREE-? ";
            cin.getline(degree, 4);
            break;
        case 2: cout << "INPUT YES OR NO FOR DISCOVERY-? ";
            cin.getline(discovery, 4);
            break;
        case 3: cout << "INPUT A REAL NUMBER FOR EXPERIENCE-? ";
            cin >> experience;
            break;
        case 4: cout << "INPUT A REAL NUMBER FOR GPA-? ";
            cin >> gpa;
            break;
        }
    }
}

void BackwardChaining::presentSolution()
{
    if (solutionFound)
    {
        cout << "\nA solution was found.\n";
        cout << results << endl;
    }
    else
    {
        cout << "\nUnable to determine a solution.\n";
    }
}

int main()
{
    BackwardChaining bNewChain;

    bNewChain.runChaining();
    bNewChain.presentSolution();
    return 0;
}