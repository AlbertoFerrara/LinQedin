#include "utente.h"
#include "rete.h"
#include <QMessageBox>

Utente::Utente(Username u, Info i) : user(u), inf(i), rete(new Rete()){}

void Utente::addFriend(Utente* u){
        rete->add(u);
}

vector<Utente*>& Utente::getRete(){
    return rete->getRete();
}

void Utente::removeFriend(string u){
    if(rete->searchInPersonalNet(u)){
        rete->remove(u);
        QMessageBox msg;
        msg.setText("Utente rimosso correttamente");
        msg.exec();}
  else{
      QMessageBox err;
      err.setText("Utente non presente nella tua rete");
      err.exec();}
}

string Utente::getLogin() const{
    return user.login;
}

void Utente::addLanguages(string s){
    inf.addKnownLang(s);
}

void Utente::addPersExp(string s){
    inf.addPersExp(s);
}

void Utente::addQualif(string s){
    inf.addQualif(s);
}

void Utente::addWorkExp(string s){
    inf.addWorkSkill(s);
}

QString Utente::getReteContact(const vector<Utente*>& d) const{
    return rete->getAllContact(d);
}

Utente::~Utente(){
    delete rete;
}

string Utente::getPassword() const{
    return user.getPassword();
}

string Utente::getAddress() const{
    return inf.getAddress();
}

string Utente::getEmail() const{
    return inf.getEmail();
}

string Utente::getTelephone() const{
    return inf.getTelNumber();
}

string Utente::getName() const{
    return inf.getName();
}

string Utente::getSurname() const{
    return inf.getSurname();
}

const Info* Utente::getInfo() const{
    return &inf;
}

void Utente::setName(string n){
    inf.setName(n);
}

void Utente::setSurname(string s){
    inf.setSurname(s);
}

void Utente::setTelephone(string t){
    inf.setTelNumber(t);
}

void Utente::setAddress(string a){
    inf.setAddress(a);
}

void Utente::setEmail(string e){
    inf.setEmail(e);
}

void Utente::setPassword(string p){
    user.setPassword(p);
}

string Utente::getAllLanguages() const{
    return inf.getAllLanguages();
}

string Utente::getAllWorkExp() const{
    return inf.getAllWorkExp();
}

string Utente::getAllPersonalExp() const{
    return inf.getAllPersonalExp();
}

string Utente::getAllQualif() const{
    return inf.getAllQualif();
}

void Utente::saveRete(string s) const{
    rete->saveRete(s);
}

vector<vector<Utente*>::iterator> Utente::searchInNet(){
    return rete->search();
}

bool Utente::checkFriend(Utente* u) const{
    return rete->searchInPersonalNet(u->getLogin());
}


