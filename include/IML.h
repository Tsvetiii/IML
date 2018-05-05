#ifndef IML_H
#define IML_H

#include<iostream>

#include<stack>
#include<list>
#include<cstring>

#include"Tags.h"

struct Operation{
    std::string tag;
    std::list<double> arguments;
    Operation(std::string _tag = "",std::list<double> _arg = std::list<double>()): tag(_tag), arguments(_arg){}
};

void printList(std::ofstream& os, std::list<double> lst);
void applyTag(std::list<double>& lst, Operation op);
void parser(std::string& rfilename, std::string& wfilename);
void cleanStack(std::stack<Operation>& operations);

#endif // IML_H
