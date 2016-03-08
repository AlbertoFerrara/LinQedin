#include "utentebasic.h"


UtenteBasic::UtenteBasic(Username u, Info i) : Utente(u, i) {}

vector<string> UtenteBasic::userSearch(const DB& d, string u){
    SearchFunctor sf(1);
    bool found=false;
    vector<string> vett;
    for(vector<Utente*>::const_iterator it=d.getDB()->begin(); it!=d.getDB()->end() && !found; ++it){
        if((*it)->getLogin()==u){
             sf((*it), vett);}
    }
    return vett;

}

UtenteBasic::~UtenteBasic(){
}

