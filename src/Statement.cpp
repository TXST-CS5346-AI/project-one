#include"Statement.h"

Statement::Statement()
{
    conclusion.name = "NULL";
    conclusion.value = "NULL";
    conclusion.type = STRING;
    premiseList.push_back(ClauseItem());
}
Statement::Statement(ClauseItem conclusionP, std::vector<ClauseItem>& premiseListP)
{
    conclusion = conclusionP;
    premiseList = premiseListP;
}