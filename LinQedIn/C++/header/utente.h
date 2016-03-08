#ifndef UTENTE_H
#define UTENTE_H

#include "info.h"
#include "username.h"
#include "db.h"
#include <string>
#include <vector>

using std::vector;
using std::string;

class Rete;
class DB;

//classe base polimorfa astratta
class Utente{
private:
    Username user;
    Info inf;
    Rete* rete;
public:
    Utente(Username, Info);
    void addFriend(Utente*);
    void removeFriend(string);
    void addLanguages(string);
    void addWorkExp(string);
    void addQualif(string);
    void addPersExp(string);
    string getName() const;
    string getSurname() const;
    string getLogin() const;
    string getTelephone() const;
    string getAddress() const;
    string getPassword() const;
    string getEmail() const;
    void setName(string);
    void setSurname(string);
    void setTelephone(string);
    void setAddress(string);
    void setEmail(string);
    void setPassword(string);
    string getAllLanguages() const;
    string getAllPersonalExp() const;
    string getAllQualif() const;
    string getAllWorkExp() const;
    void saveRete(string) const;
    const Info* getInfo() const;
    bool checkFriend(Utente*) const;
    QString getReteContact(const vector<Utente*>&) const;
    vector<Utente*>& getRete();
    vector<vector<Utente*>::iterator> searchInNet();
  //funzione virtuale di ricerca PURA, ricerca a seconda del tipo dell'utente
    virtual vector<string> userSearch(const DB&, string) =0;
    //ridefinizione del distruttore virtuale
    virtual ~Utente();
protected:
    //classe funtore che definisce le diverse possibilità di ricerca a seconda del tipo dell'utente
    class SearchFunctor{
    public:
        int searchType; //intero che indica semplicemente il tipo di ricerca (1-2-3)
        SearchFunctor(int t=0) : searchType(t) {}
        //overloading operatore () che così "trasformerà" la classe in un funtore
        void operator() (Utente* su,  vector<string>& v) const{
            switch(searchType){
            case 1:
            {
                v.push_back("Basic");
                v.push_back(su->getName());
                v.push_back(su->getSurname());
            }
            case 2:
            {
                v.push_back("Business");
                v.push_back(su->getName());
                v.push_back(su->getSurname());
                v.push_back(su->getEmail());
                v.push_back(su->getAddress());
                v.push_back(su->getTelephone());
            }
            case 3:
            {
                v.push_back("Executive");
                v.push_back(su->getName());
                v.push_back(su->getSurname());
                v.push_back(su->getEmail());
                v.push_back(su->getAddress());
                v.push_back(su->getTelephone());
                v.push_back(su->getAllLanguages());
                v.push_back(su->getAllWorkExp());
                v.push_back(su->getAllQualif());
                v.push_back(su->getAllPersonalExp());
            }
            default:
            {
                v.push_back("Basic");
                v.push_back(su->getName());
                v.push_back(su->getSurname());
            }

            }
        }

    };
};

#endif // UTENTE_H
