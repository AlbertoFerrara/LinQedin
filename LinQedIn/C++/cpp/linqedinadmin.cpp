#include "linqedinadmin.h"

LinQedInAdmin::LinQedInAdmin(){
    databaseAdmin=new DB();
    databaseAdmin->loadDB();
    for(vector<Utente*>::const_iterator it=databaseAdmin->getDB()->begin(); it!=databaseAdmin->getDB()->end(); ++it){
        databaseAdmin->loadRete(*it);
    }
}

LinQedInAdmin::~LinQedInAdmin(){
    delete databaseAdmin;
}

void LinQedInAdmin::insert(Utente* su){
    databaseAdmin->insert(su);
}

void LinQedInAdmin::remove(Utente* u){
    databaseAdmin->remove(u);
}

void LinQedInAdmin::ChangeSubscriptionType(){

}

void LinQedInAdmin::save() const{
    databaseAdmin->saveDB();
}

Utente* LinQedInAdmin::findByName(string n, string s) const{
    return databaseAdmin->findName(n, s);
}

Utente* LinQedInAdmin::findByUsername(string u) const{
    return databaseAdmin->findUsername(u);
}

bool LinQedInAdmin::checkUsername(Username u) const{
    return databaseAdmin->checkUsername(u);
}

void LinQedInAdmin::emptyDB(){
    databaseAdmin->empty_db();
}

vector<vector<Utente*>::iterator> LinQedInAdmin::search(string n, string s){
    return databaseAdmin->search(n,s);
}
