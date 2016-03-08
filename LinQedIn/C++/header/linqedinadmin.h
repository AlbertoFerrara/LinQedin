#ifndef LINQEDINADMIN_H
#define LINQEDINADMIN_H

#include "db.h"


class LinQedInAdmin{

private:
    DB* databaseAdmin;
public:
    LinQedInAdmin();
    void insert(Utente*);
    void remove(Utente*);
    void ChangeSubscriptionType();
    void save() const;
    void emptyDB();
    Utente* findByName(string, string) const;
    Utente* findByUsername(string) const;
    bool checkUsername(Username) const;
    vector<vector<Utente*>::iterator> search(string, string);
    ~LinQedInAdmin();
};

#endif // LINQEDINADMIN_H
