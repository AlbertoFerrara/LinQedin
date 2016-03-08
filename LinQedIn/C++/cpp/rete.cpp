#include <QFile>
#include <QDomDocument>
#include <QMessageBox>

#include "utentebasic.h"
#include "utentebusiness.h"
#include "utenteexecutive.h"
#include "rete.h"

Rete::Rete() {}

bool Rete::searchInPersonalNet(string l) const{
    for(vector<Utente*>::const_iterator it=friends.begin(); it!=friends.end(); ++it){
        if(l==(*it)->getLogin()){
            return true;
        }
    }
    return false;
}

void Rete::add(Utente* u){
    friends.push_back(u);
}

void Rete::remove(string u){
    bool removed=false;
    for(vector<Utente*>::iterator it=friends.begin(); it!=friends.end() && !removed; ++it){
        if((*it)->getLogin()==u){
            friends.erase(it);
            removed=true;
        }
    }
}

vector<vector<Utente*>::iterator> Rete::search(){
    vector<vector<Utente*>::iterator> vettIt;
    for(vector<Utente*>::iterator it=friends.begin(); it!=friends.end(); ++it){
        vettIt.push_back(it);
    }
    return vettIt;
}


vector<Utente*>& Rete::getRete(){
    return friends;
}

void Rete::saveRete(string s){
    QFile* file = new QFile("../../../rete.xml");
        // se file esiste lo provo ad aprire (sola scrittura e di tipo testuale (con "a capo" \n))
        if(!file->open(QIODevice::WriteOnly | QIODevice::Text)){
            QMessageBox err;
            err.setText("ERRORE APERTURA FILE");
            err.exec();
        }
        else{
            //creo un xmlStreamWrite (sistema di scrittura per file xml)
            QXmlStreamWriter* in = new QXmlStreamWriter;
            //abilito la formattazione automatica in modo da avere un xml indentato e spaziato da righe
            in->setAutoFormatting(true);
            //gli passo il file xml in cui scrivere
            in->setDevice(file);
                // scrivo l'intestazione del file xml
                in->writeStartDocument();
                // scrivo il tag radice
                in->writeStartElement("reti");
                //tag identificativo per ogni utente nella rete
                in->writeStartElement("rete");
                in->writeTextElement("user", QString::fromStdString(s));
                // scorro il database e salvo ogni user nel file
                for(vector<Utente*>::const_iterator it = friends.begin(); it != friends.end(); ++it){
                     in->writeTextElement("username", QString::fromStdString((*it)->getLogin()));}

                //tag di chiusura (</user> in questo caso)
                in->writeEndElement();


                 // Essendo qui, ho finito gli utenti del db e chiudo tag radice (</reti>)
                 in->writeEndElement();
                 // Chiudo il documento
                 in->writeEndDocument();
                 // Chiudo il file
                 file->close();}
}

//gli passo un vettore contenente il DB aggiornato in modo da salvare solo gli utenti
//ancora esistente, senno avrei un problema di dangling pointer
QString Rete::getAllContact(const vector<Utente*>& d) const{
    QString str="";
    for(vector<Utente*>::const_iterator it=friends.begin(); it!=friends.end(); ++it){
       for(vector<Utente*>::const_iterator it2=d.begin(); it2!=d.end(); ++it2){
        if(*it==*it2){
          if(str.size()!=0)
              str=str+","+QString::fromStdString((*it)->getLogin());
          else
              str=QString::fromStdString((*it)->getLogin());}}
    }
    return str;
}
