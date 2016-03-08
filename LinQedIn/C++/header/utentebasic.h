#ifndef UTENTEBASIC_H
#define UTENTEBASIC_H

#include "utente.h"

class UtenteBasic : public Utente{
public:
    //qui ci sarà l'overriding della funzione di ricerca
    UtenteBasic(Username, Info);
    virtual vector<string> userSearch(const DB&, string);
    virtual ~UtenteBasic();
};

#endif // UTENTEBASIC_H
