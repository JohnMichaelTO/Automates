#include "BallasMoraTo-ClassEtat.h"
#include "BallasMoraTo-ClassTransition.h"

ClassTransition::ClassTransition()
{
    ClassEtat origine, destination;
    _etiquette = '-';
    _origine = origine;
    _destination = destination;
}

void ClassTransition::Set(char etiquette, ClassEtat origine, ClassEtat destination)
{
    _etiquette = etiquette;
    _origine = origine;
    _destination = destination;
}

void ClassTransition::SetOrigine(ClassEtat origine)
{
    _origine = origine;
}

void ClassTransition::SetDestination(ClassEtat destination)
{
    _destination = destination;
}

char ClassTransition::GetEtiquette()
{
    return _etiquette;
}

ClassEtat ClassTransition::GetOrigine()
{
    return _origine;
}

ClassEtat ClassTransition::GetDestination()
{
    return _destination;
}

// Surcharge opérateur ==
bool ClassTransition::operator ==(const ClassTransition& a) const
{
    return (_origine == a._origine && _destination == a._destination && _etiquette == a._etiquette);
}
