#ifndef RETE_H
#define RETE_H

#include "utente.h"
#include "username.h"
#include <vector>
using std::vector;

class Rete{
private:
    vector<Utente*> friends;
public:
    Rete();
    //metodo che ritorna se un determinato utente si trova nella rete personale
    bool searchInPersonalNet(string) const; //forse meglio string con login perche non ho password
    void add(Utente*);
    void remove(string);
    //ancora da vedere
    vector<Utente*>& getRete();
    void saveRete(string);
    QString getAllContact(const vector<Utente*>&) const;
    vector<vector<Utente*>::iterator> search();
};

#endif // RETE_H

