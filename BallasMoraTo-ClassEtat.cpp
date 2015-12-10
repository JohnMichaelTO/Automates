#include "BallasMoraTo-ClassEtat.h"

ClassEtat::ClassEtat()
{
    _type = V;
    _ref = "-1";
}

void ClassEtat::Set(t_type type, std::string ref)
{
    _type = type;
    _ref = ref;
}

void ClassEtat::SetPartition(char partition)
{
    _partition = partition;
}

t_type ClassEtat::GetType()
{
    return _type;
}

std::string ClassEtat::GetRef()
{
    return _ref;
}

char ClassEtat::GetPartition()
{
    return _partition;
}

void ClassEtat::SetType(t_type type)
{
    _type = type;
}

// Surcharge opérateur ==
bool ClassEtat::operator ==(const ClassEtat& a) const
{
    return (_ref == a._ref && _type == a._type);
}

// Surcharge opérateur !=
bool ClassEtat::operator !=(const ClassEtat& a) const
{
    return (_ref != a._ref || _type != a._type);
}
