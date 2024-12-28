#include "../include/Mylib.h"

void failo_tvarkymas(){
    string failo_pavadinimas;
    std::ifstream failas;
    // string eil;

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
            // tolimesnis kodas
            while(std::getline(failas, eil)){
                std::stringstream strstream(eil);
                string zodis;

                while(strstream >> zodis){
                    string naujas_zodis;
                    for (char ch : zodis) {
                        if(isalnum(ch)){
                            naujas_zodis += ch;
                        }
                    }
                    cout << naujas_zodis << endl;
                }

            }
            
            failas.close();
            break;
        } catch (const std::runtime_error &e){
            cout << e.what();
        }

    }
}