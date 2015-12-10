#ifndef CLASSAUTOMATE_H
#define CLASSAUTOMATE_H

#include <vector>
#include "BallasMoraTo-ClassEtat.h"
#include "BallasMoraTo-ClassTransition.h"

class ClassAutomate
{
    private:
        std::vector<ClassEtat> _etats;
        std::vector<ClassTransition> _transitions;
        std::vector<char> _etiquettes;
        int _nbEtiquettes;

    public:
        // Constructeur
        ClassAutomate();
        // Chargement d'un fichier
        bool LireFichier(std::string url);
        // Retourne le type d'un état à partir d'une chaîne
        t_type RetournerType(std::string type);
        std::vector<ClassEtat> GetEtats();
        std::vector<ClassTransition> GetTransitions();
        std::vector<char> GetEtiquettes();

        void SetEtats(std::vector<ClassEtat> etats);
        void SetTransitions(std::vector<ClassTransition> transitions);
        void SetEtiquettes(std::vector<char> etiquettes);
        /*
        int GetNbEtiquettes();
        void SetNbEtiquettes(int nb);
        */
        // Affichage de la table d'un automate
        void Afficher(std::string nom);
        // Affiche les partitions de l'automate (minimal)
        void AfficherPartitions(int n);
        // Lecture de Mot
        bool LectureMot(std::string mot);
        // Vérifie si un état est un état poubelle
        bool VerifEtatPoubelle(ClassEtat EtatP);
};

#endif // CLASSAUTOMATE_H
