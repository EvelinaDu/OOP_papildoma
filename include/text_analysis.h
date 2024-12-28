#ifndef TEXT_ANALYSIS_H_INCLUDED
#define TEXT_ANALYSIS_H_INCLUDED

#include "Mylib.h"

string pakeistas_zodis(const string& zodis);

void failo_tvarkymas();

void spausdinimas_zodziu_kiekis(const map<string, int>& zodziu_kiekis);

void spausdinimas_zodziu_eil(const map<string, pair<int, set<int>>>& zodziu_eil);


#endif