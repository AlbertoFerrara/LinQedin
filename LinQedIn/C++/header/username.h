#ifndef USERNAME_H
#define USERNAME_H

#include <string>
using std::string;

class Username{
private:
    string password;
public:
    string login;
    Username(string, string);
    //metodo costante che controlla se la password inserita è uguale da quella memorizzata
    bool checkPassword(string) const;
    string getPassword() const;
    void setPassword(string);
};

#endif // USERNAME_H
