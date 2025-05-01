#include "mp4.h"

Mp4::Mp4(int s, QObject *parent) : Digitale(s,parent) {}

std::string Mp4::descrizione() const
{
    return "Formato Mp4";
}
