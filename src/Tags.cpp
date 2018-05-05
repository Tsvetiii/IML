#include "Tags.h"
#include<string>
#include <set>


/////////////////MAP

std::list<double> mapINC(std::list<double>& lst, double n){
    for(std::list<double>::iterator it = lst.begin(); it != lst.end(); ++it)
        *it = *it + n;
    return lst;
}

std::list<double> mapMLT(std::list<double>& lst, double n){
    for(std::list<double>::iterator it = lst.begin(); it != lst.end(); ++it)
        *it = *it * n;
    return lst;
}


///////////////////AGG

double aggSUM(std::list<double>& lst){
    double sum = 0;
    for(std::list<double>::iterator it = lst.begin(); it != lst.end(); ++it)
        sum += *it;
    return sum;
}

double aggPRO(std::list<double>& lst){
    double sum = 1;
    for(std::list<double>::iterator it = lst.begin(); it != lst.end(); ++it)
        sum *= *it;
    return sum;
}

double aggAVG(std::list<double>& lst){
    double cnt = 0;
    for(std::list<double>::iterator it = lst.begin(); it != lst.end(); ++it)
        ++cnt;
    return aggSUM(lst)/cnt;
}

double aggFST(std::list<double>& lst){
    return lst.front();
}

double aggLST(std::list<double>& lst){
    return lst.back();
}


////////// SRT

std::list<double> srtREV(std::list<double>& lst){
    lst.reverse();
    return lst;
}

std::list<double> srtORD(std::list<double>& lst, std::string order){
    lst.sort();
    if(order == "DSC"){
        lst.reverse();
        return lst;
    }
    else return lst;
}

std::list<double> srtSLC(std::list<double>& lst, int index){
    std::list<double>::iterator it = lst.begin();
    while(index--)
        lst.pop_front();
    return lst;
}

std::list<double> srtDST(std::list<double>& lst){
    std::set<double> found;
    for (std::list<double>::iterator it = lst.begin(); it != lst.end();) {
        if (!found.insert(*it).second)
            it = lst.erase(it);
        else
            ++it;
    }
    return lst;
}




