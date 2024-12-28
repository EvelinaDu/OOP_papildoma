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
        for (const auto& i : zodziu_kiekis){
            if(i.second > 1){
                failas << i.first << ": " << i.second << endl;
            }
        }
        cout << "Rezultatai išsaugoti faile 'kiekis.txt' "<< endl;
        failas.close();
    } else{
        cout << "Nepavyko atidaryti failo!" << endl;
    }
}

void failo_tvarkymas(){
    string failo_pavadinimas;
    std::ifstream failas;
    std::map<string, int> zodziu_kiekis;

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

                while(strstream >> zodis){
                    string naujas_zodis = pakeistas_zodis(zodis);
                    zodziu_kiekis[naujas_zodis]++;
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
}

