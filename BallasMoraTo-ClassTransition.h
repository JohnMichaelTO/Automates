#ifndef CLASSTRANSITION_H
#define CLASSTRANSITION_H

#include <string>
#include "BallasMoraTo-ClassEtat.h"

class ClassTransition
{
    private:
        char _etiquette; // Etiquette de la transition
        ClassEtat _origine; // Etat d'origine
        ClassEtat _destination; // Etat de destination

    public:
        ClassTransition();
        void Set(char etiquette, ClassEtat origine, ClassEtat destination);
        void SetOrigine(ClassEtat origine);
        void SetDestination(ClassEtat destination);
        char GetEtiquette();
        ClassEtat GetOrigine();
        ClassEtat GetDestination();
        // Surcharge opérateur ==
        bool operator ==(const ClassTransition& a) const;
};

#endif // CLASSTRANSITION_H
