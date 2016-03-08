#include <QFile>
#include <QDomDocument>
#include <QMessageBox>


#include "utentebasic.h"
#include "utentebusiness.h"
#include "utenteexecutive.h"
#include <info.h>
#include "db.h"

DB::DB() {}

DB::~DB(){    
    for(vector<Utente*>::iterator it=database.begin(); it!=database.end(); ++it){
        delete *it;
    }
}

const vector<Utente*>* DB::getDB() const{
    return &database;
}

void DB::loadDB(){
    QFile* file = new QFile("../../../../LinQedIn/database.xml");
        if(file->exists()){
            // se file esiste lo provo ad aprire (sola lettura e di tipo testuale con "a capo" \n)
            if(!file->open(QIODevice::ReadOnly | QIODevice::Text)){
                QMessageBox err;
                err.setText("ERRORE APERTURA FILE");
                err.exec();
            }
            else{ 
                //creo il file xml
                QDomDocument doc;
                //provo a fare il parser del file caricato, se non va allora ritorno
                if(!doc.setContent(file)){            
                    return;
                }
                //salvo la radice del documento
                QDomElement docElem = doc.documentElement();
                // creo una lista dei nodi utenti identificati dal tag "user"
                QDomNodeList nodes = docElem.elementsByTagName("user");
                // scorro la lista nodo per nodo
                for(int i=0; i<nodes.count(); ++i){
                    //salvo l'elemento contenuto nel nodo, in posizione i, in un oggetto xml
                    QDomElement el = nodes.at(i).toElement();
                    // mi sposto sul primo figlio
                    QDomNode nodo = el.firstChild();
                    // creo le variabili per l'oggetto user
                    QString n, s, u, p, in, t, e, esl, esp, l, esd, tu, co;
                    // scorro tutti i tag del nodo e li salvo nelle rispettive variabili
                    while (!nodo.isNull()) {
                        QDomElement elemento = nodo.toElement();
                        QString tagName = elemento.tagName();

                        if(tagName=="name"){
                            n=elemento.text();
                        }
                        if(tagName=="surname"){
                            s=elemento.text();
                        }
                        if(tagName=="username"){
                            u=elemento.text();
                        }
                        if(tagName=="password"){
                            p=elemento.text();
                        }
                        if(tagName=="indirizzo"){
                            in=elemento.text();
                        }
                        if(tagName=="telefono"){
                            t=elemento.text();
                        }
                        if(tagName=="email"){
                            e=elemento.text();
                        }                      
                        if(tagName=="tipoutente"){
                            tu=elemento.text();
                        }
                        if(tagName=="esperienzelavorative"){
                            esl=elemento.text();
                        }
                        if(tagName=="esperienzepersonali"){
                            esp=elemento.text();
                        }
                        if(tagName=="lingue"){
                            l=elemento.text();
                        }
                        if(tagName=="esperienzedidattiche"){
                            esd=elemento.text();
                        }                       

                         //mi sposto sul tag successivo
                        nodo=nodo.nextSibling();
                    }
                    // creo l'oggetto user in base al tipoutente
                    Utente* ut = 0; // puntatore polimorfo

                    if(tu == "1"){
                        Info inf(n.toStdString(), s.toStdString(), in.toStdString(), t.toStdString(), e.toStdString());
                        Username us(u.toStdString(), p.toStdString());
                        ut=new UtenteBasic(us, inf);                                                
                    }
                    if( tu == "2"){
                        Info inf(n.toStdString(), s.toStdString(), in.toStdString(), t.toStdString(), e.toStdString());
                        Username us(u.toStdString(), p.toStdString());
                        ut=new UtenteBusiness(us, inf);
                    }
                    if( tu == "3"){
                        Info inf(n.toStdString(), s.toStdString(), in.toStdString(), t.toStdString(), e.toStdString());
                        Username us(u.toStdString(), p.toStdString());
                        ut=new UtenteExecutive(us, inf);
                    }


                    //carico varie esperienze
                    if(esl.size()!=0)
                       ut->addWorkExp(esl.toStdString());
                    if(esp.size()!=0)
                       ut->addPersExp(esp.toStdString());
                    if(esd.size()!=0)
                       ut->addQualif(esd.toStdString());
                    if(l.size()!=0)
                       ut->addLanguages(l.toStdString());



                    // creo lo Utente* che punta all'utente creato e lo inserisco nel db
                    database.push_back(ut);
                }
                // chiudo il file database.xml
                file->close();
            }
        }

  }

  void DB::saveDB() const{
      QFile* file = new QFile("../../../../LinQedIn/database.xml");
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
              in->writeStartElement("users");

              // scorro il database e salvo ogni user nel file
              for(vector<Utente*>::const_iterator it = database.begin(); it != database.end(); ++it){
                      //tag identificativo per ogni utente
                   UtenteBasic* uba=dynamic_cast< UtenteBasic*>(*it);
                  if(uba){
                      QString str=uba->getReteContact(database);
                      in->writeStartElement("user");
                      in->writeTextElement("name", QString::fromStdString((*it)->getName()));
                      in->writeTextElement("surname", QString::fromStdString((*it)->getSurname()));
                      in->writeTextElement("username", QString::fromStdString((*it)->getLogin()));
                      in->writeTextElement("password", QString::fromStdString((*it)->getPassword()));
                      in->writeTextElement("indirizzo", QString::fromStdString((*it)->getAddress()));
                      in->writeTextElement("telefono", QString::fromStdString((*it)->getTelephone()));
                      in->writeTextElement("email", QString::fromStdString((*it)->getEmail()));
                      in->writeTextElement("contatti", str);
                      in->writeTextElement("tipoutente", QString::number(1));
                      in->writeTextElement("esperienzelavorative", QString::fromStdString((*it)->getAllWorkExp()));
                      in->writeTextElement("esperienzepersonali", QString::fromStdString((*it)->getAllPersonalExp()));
                      in->writeTextElement("lingue", QString::fromStdString((*it)->getAllLanguages()));
                      in->writeTextElement("esperienzedidattiche", QString::fromStdString((*it)->getAllQualif()));
                      //tag di chiusura (</user> in questo caso)
                      in->writeEndElement();}
                  else{
                      const UtenteBusiness* ubu=dynamic_cast<const UtenteBusiness*>(*it);
                      if(ubu){
                          QString str=ubu->getReteContact(database);
                          in->writeStartElement("user");
                          in->writeTextElement("name", QString::fromStdString((*it)->getName()));
                          in->writeTextElement("surname", QString::fromStdString((*it)->getSurname()));
                          in->writeTextElement("username", QString::fromStdString((*it)->getLogin()));
                          in->writeTextElement("password", QString::fromStdString((*it)->getPassword()));
                          in->writeTextElement("indirizzo", QString::fromStdString((*it)->getAddress()));
                          in->writeTextElement("telefono", QString::fromStdString((*it)->getTelephone()));
                          in->writeTextElement("email", QString::fromStdString((*it)->getEmail()));
                          in->writeTextElement("contatti", str);
                          in->writeTextElement("tipoutente", QString::number(2));
                          in->writeTextElement("esperienzelavorative", QString::fromStdString((*it)->getAllWorkExp()));
                          in->writeTextElement("esperienzepersonali", QString::fromStdString((*it)->getAllPersonalExp()));
                          in->writeTextElement("lingue", QString::fromStdString((*it)->getAllLanguages()));
                          in->writeTextElement("esperienzedidattiche", QString::fromStdString((*it)->getAllQualif()));
                          //tag di chiusura (</user> in questo caso)
                          in->writeEndElement();
                      }
                      else{
                          const UtenteExecutive* uex=dynamic_cast<const UtenteExecutive*>(*it);
                          if(uex){
                              QString str=uex->getReteContact(database);
                              in->writeStartElement("user");
                              in->writeTextElement("name", QString::fromStdString((*it)->getName()));
                              in->writeTextElement("surname", QString::fromStdString((*it)->getSurname()));
                              in->writeTextElement("username", QString::fromStdString((*it)->getLogin()));
                              in->writeTextElement("password", QString::fromStdString((*it)->getPassword()));
                              in->writeTextElement("indirizzo", QString::fromStdString((*it)->getAddress()));
                              in->writeTextElement("telefono", QString::fromStdString((*it)->getTelephone()));
                              in->writeTextElement("email", QString::fromStdString((*it)->getEmail()));
                              in->writeTextElement("contatti", str);
                              in->writeTextElement("tipoutente", QString::number(3));
                              in->writeTextElement("esperienzelavorative", QString::fromStdString((*it)->getAllWorkExp()));
                              in->writeTextElement("esperienzepersonali", QString::fromStdString((*it)->getAllPersonalExp()));
                              in->writeTextElement("lingue", QString::fromStdString((*it)->getAllLanguages()));
                              in->writeTextElement("esperienzedidattiche", QString::fromStdString((*it)->getAllQualif()));
                              //tag di chiusura (</user> in questo caso)
                              in->writeEndElement();}}
                  }


              }

              // Essendo qui, ho finito gli utenti del db e chiudo tag radice (</users>)
              in->writeEndElement();
              // Chiudo il documento
              in->writeEndDocument();
              // Chiudo il file
              file->close();

              // messaggio di avvenuto salvataggio
              QMessageBox* mess = new QMessageBox;
              mess->setText("Salvataggio avvenuto con successo!");
              mess->exec();
          }
}

void DB::loadRete(Utente* ut){
    QFile* file = new QFile("../../../../LinQedIn/database.xml");
        if(file->exists()){
            // se file esiste lo provo ad aprire (sola lettura e di tipo testuale con "a capo" \n)
            if(!file->open(QIODevice::ReadOnly | QIODevice::Text)){
                QMessageBox err;
                err.setText("ERRORE APERTURA FILE");
                err.exec();
            }
            else{
                //creo il file xml
                QDomDocument doc;
                //provo a fare il parser del file caricato, se non va allora ritorno
                if(!doc.setContent(file)){
                    return;
                }
                //salvo la radice del documento
                QDomElement docElem = doc.documentElement();
                // creo una lista dei nodi utenti identificati dal tag "user"
                QDomNodeList nodes = docElem.elementsByTagName("user");
                // scorro la lista nodo per nodo
                for(int i=0; i<nodes.count(); ++i){

                    //salvo l'elemento contenuto nel nodo, in posizione i, in un oggetto xml
                    QDomElement el = nodes.at(i).toElement();
                    // mi sposto sul primo figlio
                    QDomNode nodo = el.firstChild();
                    // creo le variabili per l'oggetto user
                    QString co, su;
                    //Espressione regolare per il parsing della QString
                    QRegExp re("[,]");
                    // scorro tutti i tag del nodo e li salvo nelle rispettive variabili



                    while (!nodo.isNull()) {
                        QDomElement elemento = nodo.toElement();
                        QString tagName = elemento.tagName();
                        if(tagName=="contatti"){
                            co=elemento.text();
                        }
                        if(tagName=="username"){
                            su=elemento.text();
                        }
                         //mi sposto sul tag successivo
                        nodo=nodo.nextSibling();

                    }


                    //carico lista contatti
                    if(su.toStdString()==ut->getLogin()){
                       QStringList list=co.split(re, QString::SkipEmptyParts);
                       QList <string> contacts;
                       for(int i=0; i<list.size(); ++i){
                           contacts.append(list.at(i).toStdString());}
                       Utente* toAdd;
                       for(int i=0; i<contacts.size(); ++i){
                           toAdd=findUsername(contacts.at(i));
                           if(ut)
                               ut->addFriend(toAdd);
                       }
                   }
                }
        }
                file->close();
        }
}

Utente* DB::find(Username u) const{
    bool found=false;
    for(vector<Utente*>::const_iterator it=database.begin(); it!=database.end() &&!found; ++it){
        if(u.login==(*it)->getLogin() && u.checkPassword((*it)->getPassword())){
            return (*it);
            found=true;}
    }
    return 0;
}

void DB::insert(Utente* su){
    database.push_back(su);
}


void DB::remove(Utente* su){
    bool removed=false;
    for(vector<Utente*>::iterator it=database.begin(); it!=database.end() &&!removed; ++it){
        if(su->getLogin()==(*it)->getLogin()){
            //elimino oggetto puntato per evitare garbage
            delete *it;
            database.erase(it);
            removed=true;}
    }
}

void DB::empty_db(){
    //elimino tutti gli oggetti puntati per evitare garbage
    for(vector<Utente*>::iterator it=database.begin(); it!=database.end(); ++it){
        delete *it;
    }
    database.erase(database.begin(), database.end());
    QMessageBox msg;
    msg.setText("Database svuotato!");
    msg.exec();
}

Utente* DB::findUsername(string u) const{
    for(vector<Utente*>::const_iterator it=database.begin(); it!=database.end(); ++it){
        if(u==(*it)->getLogin())
            return *it;
    }
    return 0;
}

Utente* DB::findName(string n, string s) const{
    for(vector<Utente*>::const_iterator it=database.begin(); it!=database.end(); ++it){
        if(n==(*it)->getName() && s==(*it)->getSurname())
            return *it;
    }
    return 0;
}


bool DB::checkUsername(Username u) const{
    bool found=false;
    for(vector<Utente*>::const_iterator it=database.begin(); it!=database.end() &&!found; ++it){
        if((*it)->getLogin()==u.login)
            return false;
    }
    return true;
}

vector<vector<Utente*>::iterator> DB::search(string n, string s){
    vector<vector<Utente*>::iterator> vettIt;
    for(vector<Utente*>::iterator it=database.begin(); it!=database.end(); ++it){
        if((((*it)->getName()==n) && (*it)->getSurname()==s) || ((n=="all") && (s=="all"))){
            vettIt.push_back(it);
        }
    }
    return vettIt;
}

