#include "username.h"

Username::Username(string log, string pass) :  password(pass), login(log) {}

bool Username::checkPassword(string pass) const{
    return password==pass;
}

string Username::getPassword() const{
    return password;
}

void Username::setPassword(string p){
    password=p;
}
