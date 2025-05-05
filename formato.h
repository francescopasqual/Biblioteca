#ifndef FORMATO_H
#define FORMATO_H

#include <QObject>
#include <string>

class Formato : public QObject
{
    Q_OBJECT

public:

    Formato(QObject *parent = nullptr);
    virtual ~Formato() = default;
    virtual std::string descrizione() const = 0;

};

#endif // FORMATO_H
