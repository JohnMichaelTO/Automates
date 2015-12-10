#ifndef CLASSETAT_H
#define CLASSETAT_H

#include <string>
#include "BallasMoraTo-structures.h"

class ClassEtat
{
    private:
        std::string _ref; // Numéro/nom de l'état
        t_type _type; // Type (I/IT/R)
        char _partition; // Ne sert qu'à minimisation de l'automate

    public:
        ClassEtat();
        void Set(t_type type, std::string ref);
        void SetPartition(char partition);
        void SetType(t_type type);
        t_type GetType();
        std::string GetRef();
        char GetPartition();
        // Surcharge opérateur ==
        bool operator ==(const ClassEtat& a) const;
        // Surcharge opérateur !=
        bool operator !=(const ClassEtat& a) const;
};

#endif // CLASSETAT_H
