#pragma warning(disable : 4996)

#include <iostream>
#include <stack>
#include <queue>
#include <cstring>
#include <string>
#include <fstream>

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
    VariableListItem(string nameP, bool instantiatedP, string valueP, string descriptionP);
    string name;
    bool instantiated;
    string value;
    string description;
};
VariableListItem::VariableListItem(string nameP, bool instantiatedP, string valueP, string descriptionP)
{
    name = nameP;
    instantiated = instantiatedP;
    value = valueP;
    description = descriptionP;
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
    string results;
    char response[3];
    string responseS;
    char qualify[4], degree[4];
    char discovery[4], position[4];
    char buff[128];

    int instantiated_list[11];
    int rule_stack[11];
    int clause_stack[11];
    int clauseVariableListIter;
    int ruleNumber;
    int var_ess;
    float gpa;
    float experience;

    stack<ConclusionStackItem> conclusionStack;
    vector<VariableListItem> variableList;
    vector<string> conclusionList;

public:
    BackwardChaining();
    int findValInConclusionList(char conclusionToFind[], int startIndex);
    void chaining(char[]);
    void pushOnConclusionStack(int ruleNumber, int clauseNumber);
    void instantiate(void);
    void parseKnowledgeBase();
    void presentSolution();
};

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
    /* enter conclusions which are the variables in the then part, 1 at
    a time.  enter the conclusions in exact order starting at the 1st
    if-then.  after last conclusion hit return key for rest of
    conclusions */
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

    /* enter variables which are in the if part, 1 at a time in the exact
    order that they occur, up to 3 variables per if statement.  do not
    duplicate any variable names.  any name is used only once.  if no
    more variables left just hit return key.
    */
    variableList.push_back(VariableListItem("DE", false, "", "INPUT YES OR NO FOR DEGREE-?"));
    variableList.push_back(VariableListItem("DI", false, "", "INPUT YES OR NO FOR DISCOVERY-?"));
    variableList.push_back(VariableListItem("EX", false, "", "INPUT A REAL NUMBER FOR EXPERIENCE-?"));
    variableList.push_back(VariableListItem("GR", false, "", "INPUT A REAL NUMBER FOR GPA-?"));

    strcpy(variable_list[1], "DE");
    strcpy(variable_list[2], "DI");
    strcpy(variable_list[3], "EX");
    strcpy(variable_list[4], "GR");

    /* enter variables as they appear in the if clauses.  a maximum of 3
    variables per if statement.  if no more variables hit return key.
    */
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

void BackwardChaining::chaining(char responseP[])
{
    strcpy(response, responseP);
    ruleNumber = findValInConclusionList(response, 1);
    if (ruleNumber != 0)
    {
        do
        {
            pushOnConclusionStack(ruleNumber, 1);
            do
            {
            b545:
                clauseVariableListIter = (conclusionStack.top().ruleNumber - 1) * 4 + conclusionStack.top().clauseNumber;
                responseS = clause_variable_list[clauseVariableListIter];
                strcpy(response, clause_variable_list[clauseVariableListIter]);

                if (responseS != "")
                {
                    /*is this clause variable a conclusion? */
                    ruleNumber = findValInConclusionList(response, 1);
                    if (ruleNumber != 0)
                        /* it is a conclusion push it */
                        chaining(response);
                    /* check instantiation of this clause */
                    instantiate();
                    if (!conclusionStack.empty())
                    {
                        conclusionStack.top().clauseNumber = conclusionStack.top().clauseNumber + 1;
                    }
                }

            } while (strcmp(response, "") != 0); /*do-while*/

            /*no more clauses check if part of statement */
            if (!conclusionStack.empty())
            {
                ruleNumber = conclusionStack.top().ruleNumber;
            }
            var_ess = 0;
            /**** if then statements ****/
            /* sample if parts of if then statements from
                the position knowledge base */
            switch (ruleNumber)
            {
            case 1: if (strcmp(degree, "NO") == 0) var_ess = 1;
                break;
            case 2: if (strcmp(degree, "YES") == 0) var_ess = 1;
                break;
            case 3: if ((strcmp(degree, "YES") == 0) &&
                (strcmp(discovery, "YES") == 0)) var_ess = 1;
                break;
            case 4: if ((strcmp(qualify, "YES") == 0) &&
                (gpa < 3.5) && (experience >= 2)) var_ess = 1;
                break;
            case 5: if ((strcmp(qualify, "YES") == 0) &&
                (gpa < 3.5) && (experience < 2)) var_ess = 1;
                break;
            case 6: if ((strcmp(qualify, "YES") == 0) &&
                (gpa >= 3.5)) var_ess = 1;
                break;
            }
            /* see if the then part should be invoked */
            if (var_ess != 1)
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
        } while ((var_ess != 1) && (ruleNumber != 0));  /* outer do-while loop */

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

}


void BackwardChaining::pushOnConclusionStack(int ruleNumberP, int clauseNumberP)
/* routine to push statement number (ruleNumber) and a clause number of 1 onto the
conclusion stack which consists of the statement stack (statement_list) and the
clause stack (clause_stack)..*/
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
    /****** inference section *****/
    cout << "** ENTER CONCLUSION ? ";
    // cin >> responseS;
    char response[3];
    //string response;

    cin.getline(response, 3);
    bNewChain.chaining(response);
    bNewChain.presentSolution();
    return 0;
}
