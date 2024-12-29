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
        failas << string(30, '-') << endl;
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

string pasirinkimas_url(){
    string pasirinkimas;

    cout << "Pasirinkite kur norite matyti url rezultatus (Terminale - T, Faile - F): ";
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

void spausdinimas_url(std::ostream &out, vector<string> url_vektorius){
    out  << left << setw(15) << "Rasti url adresai: " << endl;

    for (const auto& url : url_vektorius) {
        out << url << endl;
    }

}

void url_paskirstymas(string pasirinkimas, vector<string> url_vektorius){
    if(pasirinkimas == "T"){
        spausdinimas_url(cout, url_vektorius);

    } else if(pasirinkimas == "F"){
        std::ofstream failas("url.txt");
        if(failas.is_open()){
           spausdinimas_url(failas, url_vektorius);
        }
        failas.close();
    }
}


void failo_tvarkymas(){
    string failo_pavadinimas;
    std::ifstream failas;
    map<string, int> zodziu_kiekis;
    map<string, pair<int, set<int>>> zodziu_eil;
    int eil_nr = 0;
    vector<string> url_vektorius;

    regex url(R"((https?:\/\/|www\.)?[a-zA-Z0-9-]+(\.[a-zA-Z]{2,})+(/[^\s]*)?)");

    cout << "Įveskite failo pavadinimą: ";
    
    while(true){
        try{
            std::getline(cin, failo_pavadinimas);
            failas.open(failo_pavadinimas);

            if(!failas.is_open()){
                throw std::runtime_error("Klaida, failas nerastas. Bandykite dar kartą! ");
            }
            cout << "Failas sėkmingai atidarytas!" << endl;
            string eil;
            while(std::getline(failas, eil)){
                std::stringstream strstream(eil);
                string zodis;
                eil_nr++;

                while(strstream >> zodis){
                    if (std::regex_match(zodis, url)){
                        url_vektorius.push_back(zodis);
                    }
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
    string pasirinkimas = pasirinkimas_url();
    url_paskirstymas(pasirinkimas, url_vektorius);
}

