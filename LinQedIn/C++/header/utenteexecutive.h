#ifndef UTENTEEXECUTIVE_H
#define UTENTEEXECUTIVE_H

#include "utente.h"

class UtenteExecutive : public Utente{
public:
    //qui ci sarà l'overriding della funzione di ricerca
    UtenteExecutive(Username, Info);
    virtual vector<string> userSearch(const DB&, string);
};

#endif // UTENTEEXECUTIVE_H
