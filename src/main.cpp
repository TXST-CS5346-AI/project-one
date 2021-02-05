//#include "include\mainwindow.h"

//#include <QApplication>

#include <iostream>
#include <cstring>

using namespace std;
/*
Enclosed a program, which comprises the inference engine based on backward chaining.  You need it for your
project #1.  The program contains some errors and it is not designed to be efficient.
Modify the program to make it better and efficient.  Explain in your report how you have modified the
program to make it better.



#include <iostream>
#include <cstring>

using namespace std;


******* backward chaining *******
Install your IF clauses in sequence in the first case
   statement of the main program
   example: if((a1==2) && (a2==6)) var_ess=1;
                      if(strcmp(var_jay,NO") != 0) var_ess=1;
   the then part of the above construction always
   contains var_ess=1;
   install your the clauses in sequence in the second
   case statement of the main program
   example strcpy(position,"YES");


/*  conclusion list */



class BackwardChaining
{
    private:
        char conclusion_list[10][3];
/*  variable list */
        char variable_list[10][3];
/*  clause variable list */
        char clause_variable_list[40][3];
        char response[3];
        char /* qualify */ qualify[4], /* degree*/ degree[4];
        char /* discovery */ discovery[4], /* position */ position[4];
        char buff[128];

/* instantiated list */
        int instantiated_list[11];
/* statement stack */
        int statement_list[11];
        int /* clause stack */
        clause_stack[11],
        sequence_number,
        var_eff,
        var_eye,
        var_jay,
        var_ess,
        var_kay,
/*stack pointer */
        stack_pointer;
        float /* grade */ gpa, /*experience */ experience;

       void calculateClause();

    public:
        BackwardChaining();
        void determine_member_concl_list(void);
        void chaining();
        void push_on_stack(void);
        void instantiate(void);

};

BackwardChaining::BackwardChaining()
{
    /***** initialization section ******/
    /* stack space is 10 we initially place stack space at 10+1 */
    stack_pointer=11;
    for (var_eye=1; var_eye < 11; var_eye++)
    {
        strcpy(conclusion_list[var_eye], "");
        strcpy(variable_list[var_eye], "");
        instantiated_list[var_eye]=0;
        statement_list[var_eye]=0;
        clause_stack[var_eye]=0;
    }
    for (var_eye=1; var_eye < 41; var_eye++)  strcpy(clause_variable_list[var_eye], "");
    /* enter conclusions which are the variables in the then part, 1 at
    a time.  enter the conclusions in exact order starting at the 1st
    if-then.  after last conclusion hit return key for rest of
    conclusions */

    /*** comment 305 *****/
    strcpy(conclusion_list[1], "PO");
    strcpy(conclusion_list[2], "QU");
    strcpy(conclusion_list[3], "PO");
    strcpy(conclusion_list[4], "PO");
    strcpy(conclusion_list[5], "PO");
    strcpy(conclusion_list[6], "PO");
    cout << "*** CONCLUSION LIST ***\n";
    for (var_eye=1; var_eye < 11; var_eye++)
        cout << "CONCLUSION " <<  var_eye << " " << conclusion_list[var_eye] << endl;

    cout << "HIT RETURN TO CONTINUE";
    cin.getline( buff,120 );
    /* enter variables which are in the if part, 1 at a time in the exact
    order that they occur, up to 3 variables per if statement.  do not
    duplicate any variable names.  any name is used only once.  if no
    more variables left just hit return key.
    */
    cout << "*** VARIABLE LIST *\n";
    /**** comment 367 *****/
    strcpy(variable_list[1], "DE");
    strcpy(variable_list[2], "DI");
    strcpy(variable_list[3], "EX");
    strcpy(variable_list[4], "GR");
    for(var_eye=1; var_eye < 11; var_eye++)
        cout << "VARIABLE " << var_eye << " " <<  variable_list[var_eye] << endl;
    cout << "HIT RETURN KEY TO CONTINUE";
    cin.getline( buff,120 );
    /* enter variables as they appear in the if clauses.  a maximum of 3
    variables per if statement.  if no more variables hit return key.
    */
    cout << "*** CLAUSE VARIABLE LIST ***\n";
    /***** comment 407 through 409 ***/
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
    for(var_eye=1; var_eye < 9; var_eye++)
    {
        cout << "** CLAUSE " << var_eye  << endl;
        for(var_jay=1; var_jay < 5; var_jay++)
        {
            var_kay = 4 * (var_eye - 1) + var_jay;
            cout << "VARIABLE  " << var_jay << " " << clause_variable_list[var_kay] << endl;
        }
        if (var_eye == 4)
        {
            cout << "HIT RETURN KEY TO CONTINUE";
            cin.getline( buff,120 );
        }
    }
}

void BackwardChaining::chaining()
{
    /****** inference section *****/
    cout << "** ENTER CONCLUSION ? ";
    cin.getline(response, 3); //gets(response);
    /* get conclusion statement number (sequence_number) from the conclusion list
       (conclt) */
    /* first statement starts search */
b520:
    var_eff=1;
    determine_member_concl_list();
    if (sequence_number != 0)
    {
        /* if sequence_number = 0 then no conclusion of that name */
        do
            /* push statement number (sequence_number) and clause number=1 on goal
               stack which is composed of the statement stack (statement_list)
               and clause stack (clause_stack) */
        {
            push_on_stack();

            do
            {
                /* calculate clause location in clause-variable list */

b545:           var_eye= (statement_list[stack_pointer] - 1) * 4 + clause_stack[stack_pointer];
                /* clause variable */
                strcpy(response, clause_variable_list[var_eye]);

                if(strcmp(response, "") != 0)
                {
                    /*is this clause variable a conclusion? */
                    var_eff = 1;
                    determine_member_concl_list();
                    if(sequence_number != 0)
                        /* it is a conclusion push it */
                        goto b520;
                    /* check instantiation of this clause */
                    instantiate();
                    clause_stack[stack_pointer] = clause_stack[stack_pointer] + 1;
                }

            } while(strcmp(response, "") != 0); /*do-while*/

            /*no more clauses check if part of statement */
            sequence_number = statement_list[stack_pointer];
            var_ess = 0;
            /**** if then statements ****/
            /* sample if parts of if then statements from
                the position knowledge base */
            switch (sequence_number) {
                /* if part of statement 1 */
                /****** comment 1500 ****/
                case 1: if(strcmp(degree, "NO") == 0) var_ess = 1;
                    break;
                    /* if part of statement 2 */
                    /***** comment 1510 ******/
                case 2: if(strcmp(degree, "YES") == 0) var_ess = 1;
                    break;
                    /* if part of statement 3 */
                case 3: if((strcmp(degree, "YES") == 0) &&
                           (strcmp(discovery, "YES") == 0)) var_ess =1;
                    break;
                    /* if part of statement 4 */
                    /******** comment 1560 ******/
                case 4: if((strcmp(qualify, "YES") == 0) &&
                           (gpa < 3.5) && (experience >= 2)) var_ess = 1;
                    break;
                    /******** comment 1570 ********/
                    /* if part of statement 5 */
                case 5: if((strcmp(qualify, "YES") == 0) &&
                           (gpa < 3.5) && (experience < 2)) var_ess = 1;
                    break;
                    /* if part of statement 6 */
                case 6: if((strcmp(qualify, "YES") == 0) &&
                           (gpa >= 3.5)) var_ess = 1;

                    break;
                    /********* comment 1680 ******/
            }
            /* see if the then part should be invoked */
            if(var_ess != 1) {
                /* failed..search rest of statements for
                    same conclusion */
                /* get conclusion */
                var_eye = statement_list[stack_pointer];
                strcpy(response, conclusion_list[var_eye]);
                /* search for conclusion starting at the
                    next statement number */
                var_eff = statement_list[stack_pointer] + 1;
                determine_member_concl_list();
                stack_pointer = stack_pointer + 1;
            }
            /* pop old conclusion and put on new one */
        } while((var_ess != 1) && (sequence_number != 0));  /* outer do-while loop */

        if(sequence_number != 0)
        {
            /* if part true invoke then part */
            /* then part of if-then statements from the
            position knowledge base */
            switch (sequence_number) {
                /* then part of statement 1 */
                /******* comment 1500 *******/
                case 1: strcpy(position, "NO");
                    cout << "PO=NO\n";
                    break;
                    /* then part of statement 2 */
                    /****** comment 1510 ******/
                case 2: strcpy(qualify, "YES");
                    cout << "QU=YES\n";
                    break;
                    /* then part of statement 3 */
                case 3: strcpy(position, "YES");
                    cout << "PO=RESEARCH\n";
                    break;
                    /* then part of statement 4 */
                    /******** comment 1560 ******/
                case 4: strcpy(position, "YES");
                    cout <<"PO=SERVICE ENGINEER\n";
                    break;
                    /* then part of statement 5 */
                    /****** comment 1570 *****/
                case 5: strcpy(position, "NO");
                    cout <<"PO=NO";
                    break;
                    /* then part of statement 6 */
                case 6: strcpy(position, "YES");
                    cout << "PO=PRODUCT ENGINEER\n";
                    break;
                    /****** comment 1680 ********/
            }
            /* pop the stack */
            stack_pointer= stack_pointer + 1;
            if(stack_pointer >= 11)
                /* finished */
                cout << "*** SUCCESS\n" << endl;
            else {
                /* stack is not empty */
                /* get next clause then continue */
                clause_stack[stack_pointer] = clause_stack[stack_pointer] + 1;
                goto b545;
            }
        }
    }

}

void BackwardChaining::determine_member_concl_list() {
/* routine to determine if a variable (response) is a member of the
   conclusion list (conclt).  if yes return sequence_number != 0.
   if not a member sequence_number=0;
*/
    /* initially set to not a member */
    sequence_number = 0;
    /* member of conclusion list to be searched is var_eff */
    var_eye = var_eff;
    while((strcmp(response, conclusion_list[var_eye]) != 0) && (var_eye < 8))
        /* test for membership */
        var_eye= var_eye + 1;
    if (strcmp(response, conclusion_list[var_eye]) == 0) sequence_number = var_eye;  /* a member */
}

void BackwardChaining::push_on_stack()
/* routine to push statement number (sequence_number) and a clause number of 1 onto the
conclusion stack which consists of the statement stack (statement_list) and the
clause stack (clause_stack)..to push decrement stack pointer (stack_pointer) */
{
    stack_pointer= stack_pointer - 1;
    statement_list[stack_pointer] = sequence_number;
    clause_stack[stack_pointer] = 1;
}

void BackwardChaining::instantiate()
/* routine to instantiate a variable (response) if it isn't already.  the
instantiate indication (instantiated_list) is a 0 if not, a 1 if it is.  the
variable list (varlt) contains the variable (response). */
{
    var_eye=1;
    /* find variable in the list */
    while((strcmp(response, variable_list[var_eye]) != 0) && (var_eye < 10)) var_eye= var_eye + 1;
    if((strcmp(response, variable_list[var_eye]) == 0) && (instantiated_list[var_eye] != 1))
        /*found variable and not already instantiated */
    {
        instantiated_list[var_eye]=1; /*mark instantiated */
        /* the designer of the
       knowledge base places the input statements to
       instantiate the variables below in the case statement */
        switch (var_eye)
        {
            /***** input statement *****/
            /* input statements for sample position knowledge
               base */
            /***** comment 1700 ******/
            case 1: cout << "INPUT YES OR NO FOR DEGREE-? ";
                cin.getline( degree,4 ); //gets(degree);
                break;
            case 2: cout << "INPUT YES OR NO FOR DISCOVERY-? ";
                cin.getline( discovery, 4 ); //gets(discovery);
                break;
            case 3: cout << "INPUT A REAL NUMBER FOR EXPERIENCE-? ";
                cin >> experience;
                break;
            case 4: cout << "INPUT A REAL NUMBER FOR GPA-? ";
                cin >> gpa;
                break;
                /***** comment 1715 ****/
        }
        /* end of inputs statements for sample position knowledge
           base */
    }
}

/*** FORWARD CHAINING ***/
/************************/
/* Install your IF clauses in squence in the middle of
the program within the first case statement.
EXAMPLE: IF ((A1==2) && (A2==6) || (A3 == 'YES')) S-1;
IF (J=='NO') S-1;

The THEN part of the above construction always contains
S-1. Install your THEN clauses in sequence in the middle
of the progrram within the second case statement. */

class ForwardChaining{
private:
    int flag;
    char conditional_variable[10][3];
    char variable_list[10][3], /* variable list*/ clause_variable_list[40][3]; /* clause var list */
    char cv_response[3],/* condition variable response */   temp_variable[3], buff[103]; /*variable */         //, vp[3],
    char federal_interest_rate[10], interest[10], stock[10], dollar[10], federal_monetary_policy[10];
    char position[10], /* position */  qualify[10]; /* qualify */
    int instantiated_list[10];         /* instantiated list*/
    int f, i, j, k, s, front_pointer   /* front pointer */;
    int  back_pointer  /* back pointer */,  grade /* grade */,  statement_number; /* statement number */
    int clause_number;  /* clause number */

public:
    ForwardChaining();
    void chaining();
    void search(void);
    void check_instantiation(void);
    void instantiate(void);


};

ForwardChaining::ForwardChaining()
{
    /******** INITIALIZATION SECTION ***********/
    front_pointer=1;
    back_pointer=1;

    for (i=1;i < 41; i++)
        strcpy(clause_variable_list[i], "");
/*
    for (i=1;i < 11; i++)
        strcpy(conditional_variable[i], "");
    for (i=1;i < 11; i++)
        instantiated_list[i] = 0;
    for (i=1;i < 11; i++)
        strcpy(variable_list[i], "");
*/
    for (i=1;i < 11; i++)
    {
        strcpy(conditional_variable[i], "");
        strcpy(variable_list[i], "");
        instantiated_list[i] = 0;
    }

    /* enter variables which are in the IF part, 1 at a time in
    the exact order that they occur. Up to 3 variables per
    IF statement. Do not duplicate any variable names. Any
    name is used only once. If no more variables left, just
    hit return key */
    /****** comment 367 *************/
    strcpy(variable_list[1], "DO");
    strcpy(variable_list[2], "FT");
    strcpy(variable_list[3], "FM");
    strcpy(variable_list[4], "IN");
    strcpy(variable_list[5], "ST");

    cout << "*** VARIABLE LIST ***\n";
    for (i=1;i < 11; i++)
        cout << "ENTER VARIABLE  " <<  i << "  " << variable_list[i] << endl;
    cout << "HIT RETURN TO CONTINUE";
    cin.getline( buff,130 );  //getchar();

    /* enter variables as they appear in the IF clauses, Up to 3
    variables per IF statement. If no more variables left, just
    hit return key */
    /****** comment 407, 408 *************/
    strcpy(clause_variable_list[1], "IN");
    strcpy(clause_variable_list[5], "IN");
    strcpy(clause_variable_list[9], "DO");
    strcpy(clause_variable_list[13], "DO");
    strcpy(clause_variable_list[17], "FT");
    strcpy(clause_variable_list[18], "FM");
    cout << "*** CLAUSE-VARIABLE LIST ***\n";
    for (i = 1; i < 9; i++)
    {
        cout << "** CLAUSE " << i << endl;
        for (j = 1; j < 5; j++)
        {
            k = 4 * (i - 1) + j;
            cout << "VARIABLE " <<  j << " " << clause_variable_list[k] << endl;
        }

        if (i==4)
        {
            cout << "HIT RETURN TO CONTINUE";
            cin.getline( buff,130 ); //getchar();
        }
    }

}

void ForwardChaining::chaining()
{
    /****** INFERENCE SECTION *****************/
    cout << "ENTER CONDITION VARIABLE? ";
    cin.getline( cv_response, 3 ); //gets(cv_response);
    /* place condition variable cv_response on condition var queue conditional_variable */
    strcpy(conditional_variable[back_pointer], cv_response);
    /* move backpointer (back_pointer) to back */
    back_pointer = back_pointer + 1;
    /* set the condition variable pointer consisting of the
    statement number (statement_number) and the clause number (clause_number) */
    statement_number = 1; clause_number = 1;
    /* find the next statement number containing the condition variable
    which is in front of the queue (conditional_variable), this statement number
    is located in the clause variable list (clause_variable_list) */
    /* start at the beginning */
    f=1;
b496:
    search();
    /* point to first clause in statement */
    clause_number=1;
    if (statement_number != 0)
        /* more statements */
    {
        /* locate the clause */
        i = 4 * (statement_number - 1) + clause_number;
        /* clause variable */
        strcpy(temp_variable, clause_variable_list[i]);
        /* are there any more clauses for this statement */
        while (strcmp(temp_variable, ""))
            /* more clauses */
        {
            /* check instantiation of this clause */
            check_instantiation();
            clause_number = clause_number + 1;
            /* check next clause */
            i = 4 * (statement_number - 1) + clause_number;
            strcpy(temp_variable, clause_variable_list[i]);
        }

        /* no more clauses - check IF part of statement */
        s = 0;
        /* sample IF-THEN statements from the position knowledge base */
        switch(statement_number)
        {
            /* statement 1 */
            /***** comment 1500 *****/
            case 1: if (strcmp(interest, "FALL") == 0) s=1;
                break;
                /* statement 2 */
                /***** comment 1510 *****/
            case 2: if (strcmp(interest, "RISE") == 0) s=1;
                break;
                /* statement 3 */
                /***** comment 1540 *****/
            case 3: if (strcmp(dollar, "FALL") == 0) s=1;
                break;
                /* statement 4 */
                /***** comment 1550 *****/
            case 4: if (strcmp(dollar, "RISE") == 0) s=1;
                break;
                /* statement 5 */
            case 5: if ((strcmp(federal_interest_rate, "FALL") == 0) &&
                        (strcmp(federal_monetary_policy, "ADD")) == 0) s=1;
                break;
                /* statement 6 */
            case 6: if ((strcmp(qualify, "YES") == 0) && (grade >= 3.5) == 0) s=1;
                break;
                /***** comment 1610 *****/
        }

        /* see if the THEN part should be inovked, i.e., s=1 */
        if (s != 1)
        {
            f = statement_number + 1;
            goto b496;
        }

        /* invoke THEN part */
        switch (statement_number)
        {
            /*********** comment 1500 ***********/
            /* put variable on the conclusion variable queue */
            case 1:
                strcpy(stock, "RISE");
                cout << "ST=RISE\n";
                strcpy(temp_variable, "ST");
                instantiate();
                break;
                /*********** comment 1510 ***********/
                /* put variable on the conclusion variable queue */
            case 2:
                strcpy(stock, "FALL");
                cout << "ST=FALL\n";
                strcpy(temp_variable, "ST");
                instantiate();
                break;
                /*********** comment 1540 ***********/
                /* put variable on the conclusion variable queue */
            case 3:
                strcpy(interest, "RISE");
                cout << "IN=RISE\n";
                strcpy(temp_variable, "IN");
                instantiate();
                break;
                /*********** comment 1550 ***********/
                /* put variable on the conclusion variable queue */
            case 4:
                strcpy(interest, "FALL");
                cout << "IN=FALL\n";
                strcpy(temp_variable, "IN");
                instantiate();
                break;
                /* put variable on the conclusion variable queue */
            case 5:
                strcpy(interest, "FALL");
                cout << "IN=FALL\n";
                strcpy(temp_variable, "IN");
                instantiate();
                break;
            case 6:
                strcpy(position, "YES");
                cout << "PO=YES\n";
                break;
                /*********** comment 1610 ***********/
        }

        f = statement_number + 1;
        goto b496;
    }

    /* no more clauses in the clause variable list (clause_variable_list)
    containing the variable in front of the queue (conditional_variable(front_pointer))
    then remove front variable (conditional_variable(front_pointer)) and replace it by
    the next variable (conditional_variable(front_pointer+1)). If no more variables are
    at the front of the queue, stop. */
    /* next queue variable */
    front_pointer= front_pointer + 1;
    if (front_pointer < back_pointer)
    {
        /* check out the condition variable */
        f = 1;
        goto b496;
    }
    /* no more conclusion variables on queue */

}

//==========================================================================
/* Routine to instantiate a variable (temp_variable) if it isn't already.
The instantiate indication (instantiated_list) is a 0 if not, a 1 if it is.
The vriable list (variable_list) contains the variable (temp_variable) */
void ForwardChaining::check_instantiation()
{
    i=1;

    /* find variable in the variable list */
    while ((strcmp(temp_variable, variable_list[i]) != 0) && (i <= 10)) i = i + 1;

    /* check if already instantiated */
    if (instantiated_list[i] != 1)
    {
        /* mark instantiated */
        instantiated_list[i] = 1;
        /* the designer of this knowledge base places the input
        statements to instantiate the variables in this case
        statement */

        switch (i)
        {
            /* input statements for sample position knowledge base */
            case 1:
                cout << "RISE OR FALL FOR DO? ";
                cin.getline( dollar, 10 ); // gets(dollar);
                break;
            case 2:
                cout << "RISE OR FALL FOR FT? ";
                cin.getline( federal_interest_rate, 10 );//gets(federal_interest_rate);
                break;
            case 3:
                cout << "ADD OR SUBTRACT FOR FM? ";
                cin.getline( federal_monetary_policy, 10 ); //gets(federal_monetary_policy);
                break;
            case 4:
                cout << "RISE OR FALL FOR IN? ";
                cin.getline( interest, 10 ); //gets(interest);
                break;
            case 5:
                cout << "RISE OR FALL FOR ST? ";
                cin.getline( stock, 10 );  //gets(stock);
                break;
        }
    }
    /* end of input statements for the position knowledge base */
}

//==========================================================================
/* Search clause variable list for a varialbe (clause_variable_list) equal to the
one in front of the conclusion queue (conditional_variable). Return the statement
number (statement_number). If there is no match, i.e., statement_number=0, the first statement
for the space is f. */
void ForwardChaining::search()
{
    flag = 0;
    statement_number = f;

    while ((flag == 0) && (statement_number <= 10))
    {
        clause_number=1;
        k = (statement_number - 1) * 4 + clause_number;
        while ((strcmp(clause_variable_list[k], conditional_variable[front_pointer]) != 0) && (clause_number < 4))
        {
            clause_number = clause_number + 1;
            k = (statement_number - 1) * 4 + clause_number;
        }

        if (strcmp(clause_variable_list[k], conditional_variable[front_pointer]) == 0) flag = 1;
        if (flag == 0) statement_number = statement_number + 1;
    }
    if (flag == 0) statement_number=0;
}

//==========================================================================
/* Routine to instantiate a varialbe (temp_variable) and then place it on the
back of the queu (conditional_variable[back_pointer]), if it is not already there. */
void ForwardChaining::instantiate()
{
    i=1;
    /* find varialbe in the varialbe list (variable_list) */
    while ((strcmp(temp_variable, variable_list[i]) != 0) && (i <= 10)) i= i + 1;

    /* instantiate it */
    instantiated_list[i] = 1;
    i = 1;

    /* determine if (temp_variable) is or already has been on the queue (conditional_variable) */
    while ((strcmp(temp_variable, conditional_variable[i]) != 0) && (i <= 10) ) i= i + 1;
    /* variable has not been on the queue. Store it in the back of the queue */
    if (strcmp(temp_variable, conditional_variable[i]) != 0)
    {
        strcpy(conditional_variable[back_pointer], temp_variable);
        back_pointer= back_pointer + 1;
    }
}




int main()
{

    BackwardChaining bNewChain;
    bNewChain.chaining();
    ForwardChaining fNewChain;
    fNewChain.chaining();
    return 0;
}









//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);
//    Mainwindow w;
//    w.show();
//    return a.exec();
//}
