#include "authenticator.h"

Authenticator::Authenticator(QObject *parent)
    : QObject{parent}
{
    //Definisco le credenziali valide
    credenzialiValide["admin"] = "password123";
    credenzialiValide["bibliotecario"] = "sicura456";

}

bool Authenticator::verificaCredenziali(const QString &username, const QString &password)
{
    //logica di autenticazione

    //se trovo lo username tra quelli validi di default
    if(credenzialiValide.contains(username)){

        //se la password immessa corrisponde a quella definita valida di default
        if(credenzialiValide.value(username)==password){
            qDebug() << "Authenticator: Credenziali valide.";
            return true; // Username e password corrispondono

        }else{
            qDebug() << "Authenticator: Password non corretta.";
            return false;
        }

    }else{
        qDebug() << "Authenticator: Utente non trovato:" << username;
        return false; // Username non trovato
    }
}
