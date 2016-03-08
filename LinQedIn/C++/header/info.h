//Manca da inserire, volendo, la modifica delle liste e dei suoi nodi

#ifndef INFO_H
#define INFO_H

#include <iostream>
#include <list>
#include "string"
using std::list;
using std::string;

class Info{
private:
    string name;
    string surname;
    string address;
    string telephonNumber;
    string email;
    list<string> personalExperience;
    list<string> workingSkills;
    list<string> knownLanguages;
    list<string> qualification;

public:
    //Costruttore dell'oggetto Info
    Info(string, string, string, string, string);
    //Info(const Info&);
    //Modifica del nome
    void setName(string);
    //Modifica del cognome
    void setSurname(string);
    //Settaggio o modifica dell'indirizzo
    void setAddress(string);
    //Settaggio o modifica del numero di telefono
    void setTelNumber(string);
    //Settaggio o modifica dell'indirizzo
    void setEmail(string);
    //Ritorno del nome
    string getName() const;
    //Ritorno del cognome
    string getSurname() const;
    //Ritorno dell'indirizzo
    string getAddress() const;
    //Ritorno del numero di telefono
    string getTelNumber() const;
    //Ritorno dell'indirizzo
    string getEmail() const;
    //Inserimento in coda di personalExperience
    void addPersExp(string);
    //Inserimento in coda di workingSkills
    void addWorkSkill(string);
    //Inserimento in coda di knownLanguages
    void addKnownLang(string);
    //Inserimento in coda di qualifications
    void addQualif(string);
    //Ritorno dei dati delle knownLanguages
    string getAllLanguages() const;
    string getAllPersonalExp() const;
    string getAllQualif() const;
    string getAllWorkExp() const;
};

#endif // INFO_H

/*
 Per i campi dati personalExperience, workingSkills, knownLanguages
 e qualifications ho scelto di utilizzare una lista (list) perchè
 l'inserimento dei vari dati andrà fatto sempre ed esclusivamente
 in coda, e questa operazione nelle liste è molto piu efficente perche
 nel vector al momento della sua saturazione avviene l'operazione di
 raddoppio della size con corrispondente copia di tutti i dati. Inoltre
 in questo caso non è necessaria la funzionalità di accesso casuale ai
 dati che è il motivo per cui si potrebbe scegliere un vector.
*/
