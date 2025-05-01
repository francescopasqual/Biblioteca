#ifndef AUTHENTICATOR_H
#define AUTHENTICATOR_H

#include <QObject>
#include <QString>
#include <QHash>
#include <QDebug>

class Authenticator : public QObject
{
    Q_OBJECT

private:

    //mappa username e password
    QHash <QString, QString> credenzialiValide;

public:
    Authenticator(QObject *parent = nullptr);

    //metodo di verifica
    bool verificaCredenziali(const QString& username, const QString& password);

signals:
};

#endif // AUTHENTICATOR_H
