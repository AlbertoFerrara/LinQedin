#include "linqedinclient.h"
#include <QMessageBox>

LinQedInClient::LinQedInClient(Username u) {
    database=new DB();
    database->loadDB();
    userClient=database->find(u);
    if(userClient){
        string s=userClient->getLogin();
        //carico anche le reti di tutti gli utenti per poter salvarle nel DB al momento della saveDB()
        for(vector<Utente*>::const_iterator it=database->getDB()->begin(); it!=database->getDB()->end(); ++it){
            database->loadRete(*it);}
    }
}

void LinQedInClient::addInRete(Utente* u){
    if(u->getLogin()!=userClient->getLogin()){
       if(!userClient->checkFriend(u)){
          userClient->addFriend(u);
          QMessageBox msg;
          msg.setText("Inserimento avvenuto con successo");
          msg.exec();}
       else{
           QMessageBox err;
           err.setText("Utente già presente nella tua rete");
           err.exec();}
       }
    else{
        QMessageBox err;
        err.setText("Non puoi aggiungere te stesso");
        err.exec();
    }
}

void LinQedInClient::removeFormRete(string u){
    userClient->removeFriend(u);
}

vector<string> LinQedInClient::find(string s) const{
    return userClient->userSearch(*database, s); //chiamata polimorfa
}

Utente* LinQedInClient::findByName(string n, string s) const{
    return database->findName(n, s);
}

Utente* LinQedInClient::findByUsername(string u) const{
    return database->findUsername(u);
}

Utente* LinQedInClient::getUtente(){
    return userClient;
}

string LinQedInClient::getLogin() const{
    return userClient->getLogin();
}

void LinQedInClient::loadDB() const{
    database->loadDB();
}

void LinQedInClient::saveDB() const{
    database->saveDB();
}

bool LinQedInClient::checkUserClient() const{
    if(userClient!=0)
        return true;
    return false;
}

const Info* LinQedInClient::getInfo() const{
    return userClient->getInfo();
}

LinQedInClient::~LinQedInClient(){
    delete database;
}

vector<vector<Utente*>::iterator> LinQedInClient::search(string n, string s){
    return database->search(n,s);
}

vector<vector<Utente*>::iterator> LinQedInClient::searchInNet(){
    return userClient->searchInNet();
}
