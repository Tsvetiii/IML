#ifndef TAGS_H
#define TAGS_H

#include<list>
#include<string>

std::list<double> mapINC(std::list<double>& lst, double n);
std::list<double> mapMLT(std::list<double>& lst, double n);

double aggSUM(std::list<double>& lst);
double aggPRO(std::list<double>& lst);
double aggAVG(std::list<double>& lst);
double aggFST(std::list<double>& lst);
double aggLST(std::list<double>& lst);

std::list<double> srtREV(std::list<double>& lst);
std::list<double> srtORD(std::list<double>& lst, std::string order);
std::list<double> srtSLC(std::list<double>& lst, int index);
std::list<double> srtDST(std::list<double>& lst);

#endif // TAGS_H
