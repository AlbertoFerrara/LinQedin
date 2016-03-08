#ifndef DB_H
#define DB_H

#include <QXmlStreamReader>
#include <QList>
#include <vector>
#include "utente.h"
using std::vector;

class Utente;
class DB{
private:
    vector<Utente*> database;
public:
    DB();
    ~DB();
    void loadDB();
    void saveDB() const;
    void loadRete(Utente*);
    void insert(Utente*);
    void remove(Utente*);
    void empty_db();
    const vector<Utente*>* getDB() const;
    Utente* findName(string, string) const;
    Utente* findUsername(string) const;
    Utente* find(Username) const;
    //metodo che ritorna un vettore di iteratori a utente con nome-cognome passato
    vector<vector<Utente*>::iterator> search(string, string);
    bool checkUsername(Username) const;
};

#endif // DB_H




