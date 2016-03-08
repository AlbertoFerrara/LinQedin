#ifndef UTENTEBUSINESS_H
#define UTENTEBUSINESS_H

#include "utente.h"

class UtenteBusiness : public Utente{
public:
    //qui ci sarà l'overriding della funzione di ricerca
    UtenteBusiness(Username, Info);
    virtual vector<string> userSearch(const DB&, string);
};

#endif // UTENTEBUSINESS_H
