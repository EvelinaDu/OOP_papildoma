#include "../include/Mylib.h"

string pakeistas_zodis(const string& zodis) {
    string naujas_zodis;

    for (char ch : zodis) {
        ch = tolower(ch);
        if (!ispunct(ch) && !isdigit(ch)) {         // ispunct() Funkcija grąžina true, jei simbolis yra skyrybos ženklas, kitaip – false.
            naujas_zodis += ch;
        }
    }

    return naujas_zodis;
}

void spausdinimas_zodziu_kiekis(const map<string, int>& zodziu_kiekis){
    ofstream failas("kiekis.txt");

    if(failas.is_open()){
        failas << left << setw(20) << "Žodis" << setw(10) << "Kiekis" << endl;
        failas << string(27, '-') << endl;

        for (const auto& i : zodziu_kiekis){
            if(i.second > 1){
                failas << left << setw(20) << i.first << setw(10) << i.second << endl;
            }
        }

        cout << "Rezultatai išsaugoti faile 'kiekis.txt' "<< endl;
        failas.close();
    } else{
        cout << "Nepavyko atidaryti failo!" << endl;
    }
}

void spausdinimas_zodziu_eil(const map<string, pair<int, set<int>>>& zodziu_eil){
    ofstream failas("eil.txt");

    if(failas.is_open()){
        failas << left << setw(20) << "Žodis" << setw(1) << "Eilutės" << endl;
        failas << string(35, '-') << endl;

        for(const auto& i : zodziu_eil){

            if(i.second.first > 1){
                failas << left << setw(20) << i.first << setw(1) << "{";
                bool pirmas = true;

                for(auto it = i.second.second.begin(); it != i.second.second.end(); ++it){
                    if(!pirmas){
                        failas << ", ";
                    }
                    failas << *it;          // įrašomas reikšmė, į kurią rodo rodyklė
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

string pasirinkimas_url(){
    string pasirinkimas;

    cout << "Pasirinkite kur norite matyti URL rezultatus (Terminale - T, Faile - F): ";
    while(true){
        cin >> pasirinkimas;

        try{
            std::transform(pasirinkimas.begin(), pasirinkimas.end(), pasirinkimas.begin(), ::toupper);
            if(pasirinkimas != "T" && pasirinkimas != "F"){
                throw std::out_of_range("Netinkama įvestis, pasirinkite tarp: 'T', 'F'");
            }
            break;
        } catch(const std::out_of_range &e){
            cout << "Klaida: " << e.what() << "Bandykite dar kartą. ";
        }
    }

    return pasirinkimas;
}

void spausdinimas_url(std::ostream &out, const set<string> url_set){
    out  << left << setw(15) << "Rasti URL adresai: " << endl;

    for (const auto& url : url_set) {
        out << url << endl;
    }

}

void url_paskirstymas(string pasirinkimas, const set<string> url_set){
    if(pasirinkimas == "T"){
        spausdinimas_url(cout, url_set);

    } else if(pasirinkimas == "F"){
        ofstream failas("url_info.txt");
        if(failas.is_open()){
           spausdinimas_url(failas, url_set);
        }
        failas.close();
        cout << "Rezultatai išsaugoti faile 'url_info.txt'" << endl;
    }
}


void failo_tvarkymas(){
    string failo_pavadinimas;
    ifstream failas;
    map<string, int> zodziu_kiekis;                 // saugo žodį ir jo pasikartojimų kiekį
    map<string, pair<int, set<int>>> zodziu_eil;    // saugo žodį, jo pasikartojimų kiekį bei eilučių, kuriose buvo rastas, rinkynį
    int eil_nr = 0;
    set<string> url_set;

    regex url(R"(((https?://www\.)|(www\.))?[a-zA-Z0-9-]+\.[a-zA-Z]{2,}(/[^\s]*)?[.,;]?)");

    cout << "Įveskite failo pavadinimą: ";
    
    while(true){
        try{
            getline(cin, failo_pavadinimas);
            failas.open(failo_pavadinimas);

            if(!failas.is_open()){
                throw std::runtime_error("Klaida, failas nerastas. Bandykite dar kartą! ");
            }
            cout << "Failas sėkmingai atidarytas!" << endl;
            string eil;
            while(getline(failas, eil)){
                std::stringstream strstream(eil);
                string zodis;
                eil_nr++;

                while(strstream >> zodis){
                    if (std::regex_match(zodis, url)){
                        if(!zodis.empty() && (zodis.back() == '.' || zodis.back() == ',' || zodis.back() == ';')){
                            zodis.pop_back();
                        }
                        url_set.insert(zodis);
                    } else{
                        string naujas_zodis = pakeistas_zodis(zodis);

                        if(!naujas_zodis.empty()){
                            zodziu_kiekis[naujas_zodis]++;
                            zodziu_eil[naujas_zodis].first++;
                            zodziu_eil[naujas_zodis].second.insert(eil_nr);
                        }
                    }
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

    string pasirinkimas = pasirinkimas_url();

    if(!url_set.empty()){
        url_paskirstymas(pasirinkimas, url_set);
    } else{ 
        cout << "URL adresai nerasti." << endl;
    }
    
}

