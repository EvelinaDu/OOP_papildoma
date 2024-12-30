#ifndef TEXT_ANALYSIS_H_INCLUDED
#define TEXT_ANALYSIS_H_INCLUDED

#include "Mylib.h"

// Funkcija pašalina skyrybos ženklus, paveržia visas raides į mažasias.
string pakeistas_zodis(const string& zodis);

// Funkcija atspausdina skirtingus zodzius ir jų pasikartojimų kiekį, rezultatas pateiktas tik tų žodžių, kurie pasikartojo daugiau negu vieną kartą.
void spausdinimas_zodziu_kiekis(const map<string, int>& zodziu_kiekis);

// Funkcija atspausdina skirtingus zodzius ir jų eilučių numerius, kuriuose pasikartoja žodis. Rezultatas pateiktas tik tų žodžių, kurie pasikartojo daugiau negu vieną kartą.
void spausdinimas_zodziu_eil(const map<string, pair<int, set<int>>>& zodziu_eil);

// Funcija grąžina string reikšmę, kurioje įrašomas vartotojo pasirinkimas dėl URL rezultatų spausdinimo (T - terminalas, F - failas).
string pasirinkimas_url();

// Funkcija, kuri atspausdina visus rastus URL adresus
void spausdinimas_url(std::ostream &out, set<string> url_set);

// Funkcija, kuri paskirsto kur atspausdinamas/įrašomas URL rezultatas.
void url_paskirstymas(string pasirinkimas, set<string> url_set);

// Pagrindinė funkcija, kurioje vyksta nuskaitymas bei duomenų skaičiavimas, joje taip pat kviečiamos atspausdinimo funkcijos.
void failo_tvarkymas();


#endif