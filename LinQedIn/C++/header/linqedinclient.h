//Manca funzione find

#ifndef LINQEDINCLIENT_H
#define LINQEDINCLIENT_H

#include "string"
#include "utente.h"
#include "db.h"

using std::string;

class LinQedInClient{
private:
    Utente* userClient; //puntatore polimorfo
    DB* database; //Caricato da file e solo in lettura
public:
    LinQedInClient(Username);
    void addInRete(Utente*);
    void removeFormRete(string);
    void loadDB() const;
    void saveDB() const;
    Utente* getUtente();
    string getLogin() const;
    vector<string> find(string) const;
    Utente* findByUsername(string) const;
    Utente* findByName(string, string) const;
    vector<vector<Utente*>::iterator> search(string, string);
    vector<vector<Utente*>::iterator> searchInNet();
    const Info* getInfo() const;
    bool checkUserClient() const;
    ~LinQedInClient();
};

#endif // LINQEDINCLIENT_H
