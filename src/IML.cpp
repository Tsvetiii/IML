#include "IML.h"
#include<fstream>
#include<sstream>

void append(std::list<double>& l1, std::list<double> l2){
    for(std::list<double>::iterator it = l2.begin(); it != l2.end(); ++it){
        l1.push_back(*it);
    }
}

double toDigit(char c){
    return c - '0';
}

void printList(std::ofstream& os, std::list<double> lst){
    for(std::list<double>::iterator it = lst.begin(); it != lst.end(); ++it){
        os<<*it<<' ';
    }
}

void cleanStack(std::stack<Operation>& operations){
    while(!operations.empty()){
        operations.pop();
    }
}

void applyTag(std::list<double>& lst, Operation op, std::ofstream& os){
    std::istringstream tagName(op.tag);
    char c;
    std::string opTag = "";
    while(tagName.get(c) && c != '-'){
        opTag += c;
    }
    if(opTag == "MAP"){
        std::string opTagSpec = "";
        for(int i = 0; i < 3; ++i){
            tagName.get(c);
            opTagSpec += c;
        }
        tagName.get(c);
        tagName.get(c);
        tagName.get(c);
        std::string numStr;
        while(c != '"'){
            numStr += c;
            tagName.get(c);
        }
        double number = 0;
        std::stringstream(numStr) >> number;
        if(opTagSpec == "INC")
            append(lst, mapINC(op.arguments, number));
        else if(opTagSpec == "MLT")
            append(lst, mapMLT(op.arguments, number));
    }
    else if(opTag == "AGG"){
        std::string opTagSpec = "";
        while(tagName.get(c))
            opTagSpec += c;
        if(opTagSpec == "SUM")
            lst.push_back(aggSUM(op.arguments));
        else if(opTagSpec == "PRO")
            lst.push_back(aggPRO(op.arguments));
        else if(opTagSpec == "AVG")
            lst.push_back(aggAVG(op.arguments));
        else if(opTagSpec == "FST")
            lst.push_back(aggFST(op.arguments));
        else if(opTagSpec == "LST")
            lst.push_back(aggLST(op.arguments));
        else {
            os<<"Error. Invalid tag.";
            return;
            }
    }
    else if(opTag == "SRT"){
        std::string opTagSpec = "";
        for(int i = 0; i < 3; ++i){
            tagName.get(c);
            opTagSpec += c;
        }
        if(opTagSpec == "REV"){
            append(lst, srtREV(op.arguments));
        }
        else if(opTagSpec == "DST"){
            append(lst, srtDST(op.arguments));
        }
        else if(opTagSpec == "ORD"){
            std::string order = "";
            tagName.get(c);
            tagName.get(c);
            for(int i = 0; i < 3; ++i){
                tagName.get(c);
                order += c;
            }
            append(lst, srtORD(op.arguments, order));
        }
        else if(opTagSpec == "SLC"){
            tagName.get(c);
            tagName.get(c);
            tagName.get(c);
            std::string indexStr = "";
            double index = 0;
            while(c != '"'){
                indexStr += c;
                tagName.get(c);
            }
            std::stringstream(indexStr) >> index;
            append(lst, srtSLC(op.arguments, index));
        }

    } else {
        os<<"Error. Invalid tag.";
        return;
    }
}

bool isRightClosingTag(std::string openingTag, std::string closingTag){
    std::string::iterator open = openingTag.begin();
    for(std::string::iterator close = closingTag.begin(); close != closingTag.end(); ++close, ++open)
        if(*close != *open) return false;
    return true;
}

void parser(std::string& readFilename, std::string& writeFilename){
    std::ifstream rfile(readFilename);
    std::ofstream wfile(writeFilename);
    std::string str;
    std::getline(rfile, str);
    std::istringstream strs(str);

    std::stack<Operation> operations;

    char c;

    while(strs.peek()){
        std::string currTag = "";
        std::list<double> currTagArg;
        if(strs.peek() == '<'){
            strs.get(c);
            if(strs.peek() != '/' && !std::isdigit(strs.peek())){
                while(strs.peek() != '>' && strs.get(c)){
                    currTag += c;
                }
                strs.get(c);
            }
            else if(strs.peek() == '/'){
                strs.get(c);
                std::string currClosingTag = "";
                while(strs.peek() != '>' && strs.get(c))
                    currClosingTag += c;
                strs.get(c);
                Operation lastTag = operations.top();
                operations.pop();
                if(isRightClosingTag(lastTag.tag, currClosingTag)){
                    if(operations.empty()){
                        if(strs.gcount() > 1){
                            wfile<<"Error. Invalid tag.";
                            return;
                        }

                        std::list<double> lst;
                        applyTag(lst, lastTag, wfile);
                        printList(wfile, lst);
                        return;
                    }
                    else applyTag(operations.top().arguments, lastTag, wfile);
                }
                else{
                    wfile<<"Error. Invalid tag.";
                    return;
                }
            }
            else {
                wfile<<"Error. Invalid tag.";
                return;
            }
        }
        if(std::isdigit(strs.peek())){
            while(strs.peek() != '<'){
                double arg = 0;
                while(strs.peek() != '<' && strs.get(c) && std::isdigit(c)){
                    arg = arg*10 + toDigit(c);
                }
            currTagArg.push_back(arg);
            }
            if(currTag.empty()){
                append(operations.top().arguments, currTagArg);
            }
            else{
            Operation newTag(currTag, currTagArg);
            operations.push(newTag);
            }
        }
    }

    cleanStack(operations);
}
