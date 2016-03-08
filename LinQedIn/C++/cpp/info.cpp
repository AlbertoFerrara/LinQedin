#include "info.h"

Info::Info(string n, string s, string a, string t, string e) : name(n), surname(s),
address(a), telephonNumber(t), email(e) {}

void Info::setName(string newName){
    name=newName;
}

void Info::setSurname(string newSurname){
    surname=newSurname;
}

void Info::setAddress(string newAddress){
    address=newAddress;
}

void Info::setTelNumber(string newTelNumber){
    telephonNumber=newTelNumber;
}

void Info::setEmail(string newEmail){
    email=newEmail;
}

string Info::getName() const{
    return name;
}

string Info::getSurname() const{
    return surname;
}

string Info::getAddress() const{
    return address;
}

string Info::getTelNumber() const{
    return telephonNumber;
}

string Info::getEmail() const{
    return email;
}

void Info::addPersExp(string s){
    personalExperience.push_back(s);
}

void Info::addWorkSkill(string s){
    workingSkills.push_back(s);
}

void Info::addKnownLang(string s){
    knownLanguages.push_back(s);
}

void Info::addQualif(string s){
    qualification.push_back(s);
}

string Info::getAllLanguages() const{
    string s="";
    for(list<string>::const_iterator it=knownLanguages.begin(); it!=knownLanguages.end(); ++it){
        s=s+*it+" ";
    }
    return s;
}

string Info::getAllPersonalExp() const{
    string s="";
    for(list<string>::const_iterator it=personalExperience.begin(); it!=personalExperience.end(); ++it){
        s=s+*it+" ";
    }
    return s;
}

string Info::getAllQualif() const{
    string s="";
    for(list<string>::const_iterator it=qualification.begin(); it!=qualification.end(); ++it){
        s=s+*it+" ";
    }
    return s;
}

string Info::getAllWorkExp() const{
    string s="";
    for(list<string>::const_iterator it=workingSkills.begin(); it!=workingSkills.end(); ++it){
        s=s+*it+" ";
    }
    return s;
}



