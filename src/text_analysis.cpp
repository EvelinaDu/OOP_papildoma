#include "../include/Mylib.h"

string pakeistas_zodis(const string& zodis) {
    string naujas_zodis;
    for (char ch : zodis) {
        ch = tolower(ch);
        if (!ispunct(ch)) {
            naujas_zodis += ch;
        }
    }
    return naujas_zodis;
}

void spausdinimas_zodziu_kiekis(const std::map<string, int>& zodziu_kiekis){
    std::ofstream failas("kiekis.txt");
    if(failas.is_open()){
        failas << left << setw(15) << "Žodis" << setw(10) << "Kiekis" << endl;
        failas << string(21, '-') << endl;
        for (const auto& i : zodziu_kiekis){
            if(i.second > 1){
                failas << left << setw(15) << i.first << setw(10) << i.second << endl;
            }
        }
        cout << "Rezultatai išsaugoti faile 'kiekis.txt' "<< endl;
        failas.close();
    } else{
        cout << "Nepavyko atidaryti failo!" << endl;
    }
}

void spausdinimas_zodziu_eil(const map<string, pair<int, set<int>>>& zodziu_eil){
    std::ofstream failas("eil.txt");
    if(failas.is_open()){
        failas << left << setw(15) << "Žodis" << setw(1) << "Eilutės" << endl;
        failas << string(22, '-') << endl;
        for(const auto& i : zodziu_eil){
            if(i.second.first > 1){
                failas << left << setw(15) << i.first << setw(1) << "{";
                bool pirmas = true;
                for(auto it = i.second.second.begin(); it != i.second.second.end(); ++it){
                    if(!pirmas){
                        failas << ", ";
                    }
                    failas << *it;
                    pirmas = false;
                }
                failas << "}" << endl;
            }
            
        }

        cout << "Rezultatai išsaugoti faile 'eil.txt' "<< endl;
        failas.close();
    } else{
        cout << "Nepavyko atidaryti failo!" << endl;
    }
}

void failo_tvarkymas(){
    string failo_pavadinimas;
    std::ifstream failas;
    map<string, int> zodziu_kiekis;
    map<string, pair<int, set<int>>> zodziu_eil;
    int eil_nr = 0;

    cout << "Įveskite failo pavadinimą: ";
    
    while(true){
        try{
            std::getline(cin, failo_pavadinimas);
            failas.open(failo_pavadinimas);

            if (!failas.is_open()){
                throw std::runtime_error("Klaida, failas nerastas. Bandykite dar kartą! ");
            }
            cout << "Failas sėkmingai atidarytas!" << endl;
            string eil;
            while(std::getline(failas, eil)){
                std::stringstream strstream(eil);
                string zodis;
                eil_nr++;

                while(strstream >> zodis){
                    string naujas_zodis = pakeistas_zodis(zodis);
                    zodziu_kiekis[naujas_zodis]++;
                    zodziu_eil[naujas_zodis].first++;
                    zodziu_eil[naujas_zodis].second.insert(eil_nr);
                }
            }
            cout << "Failas sėkmingai perskaitytas!" << endl;
            failas.close();
            break;
        } catch (const std::runtime_error &e){
            cout << e.what();
        }
    }

    spausdinimas_zodziu_kiekis(zodziu_kiekis);
    spausdinimas_zodziu_eil(zodziu_eil);
}

