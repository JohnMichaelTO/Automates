#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "BallasMoraTo-ClassEtat.h"
#include "BallasMoraTo-ClassTransition.h"
#include "BallasMoraTo-ClassAutomate.h"
#include "BallasMoraTo-Fonctions.h"

using namespace std;

// Constructeur
ClassAutomate::ClassAutomate()
{
}

// Chargement d'un fichier
bool ClassAutomate::LireFichier(string url)
{
    string ligne, memoire("");
    int nbEtats(-1);
    signed int i;

    // Chargement du fichier
    ifstream fichier(url.c_str(), ios::in);

    if(fichier)
    {
        while(getline(fichier, ligne))
        {
            if(ligne != "" && ligne != "\n")
            {
                nbEtats++;
                memoire += ligne + '\n';
            }
        }
        fichier.close();
    }
    else
    {
        cout << "ERREUR : Fichier " << url << " inexistant" << endl;
        fichier.clear();
        return false;
    }

    vector<string> TabTemp = cut(memoire, "\n");
    vector< vector<string> > tableau;
    tableau.resize(nbEtats + 1);

    for(i = 0; i < nbEtats + 1; i++)
    {
        tableau[i] = cut(TabTemp[i], "\t");
    }

    _nbEtiquettes = tableau[0].size() - 2;

    ClassEtat EtatActu;
    ClassTransition newTransition;
    bool entree(false), sortie(false);

    for(i = 1; i < nbEtats + 1; i++) // nbEtats + 1 = nb de lignes du tableau
    {
        EtatActu.Set(RetournerType(tableau[i][0]), tableau[i][1]);

        if(EtatActu.GetType() == I || EtatActu.GetType() == IT) entree = true;
        if(EtatActu.GetType() == T || EtatActu.GetType() == IT) sortie = true;

        _etats.push_back(EtatActu);
    }

    if(!entree || !sortie)
    {
        cout << "ERREUR : Il n'y a pas d'entree ou de sortie dans l'automate" << endl;
        return false;
    }
    /*
    if(_nbEtiquettes == 0)
    {
        cout << "ERREUR : Pas d'etiquette" << endl;
        return false;
    }
    */

    for(i = 1; i < nbEtats + 1; i++) // nbEtats + 1 = nb de lignes du tableau
    {
        for(int j = 2; j < (_nbEtiquettes + 2); j++) // nbEtiquettes + 2 = nb de colonnes du tableau
        {
            if(i == 1) _etiquettes.push_back(tableau[0][j][0]); // Tableau listant les étiquettes

            if(tableau[i][j] != "-")
            {
                vector<string> TabDestination = cut(tableau[i][j], ";");
                for(unsigned int k = 0; k < TabDestination.size(); k++)
                {
                    newTransition.Set(tableau[0][j][0], _etats[i - 1], RetournerEtat(_etats, TabDestination[k]));
                    _transitions.push_back(newTransition);
                }
            }
        }
    }

    for(unsigned int i = 0; i < _etats.size(); i++)
    {
        if(_etats[i].GetRef() == "-1")
        {
            cout << "ERREUR : Il y a un etat inexistant" << endl;
            return false;
        }
    }

    for(unsigned int i = 0; i < _transitions.size(); i++)
    {
        if(_transitions[i].GetOrigine().GetRef() == "-1" || _transitions[i].GetDestination().GetRef() == "-1")
        {
            cout << "ERREUR : Il y a un etat inexistant" << endl;
            return false;
        }
    }

    return true;
}

// Retourne le type d'un état à partir d'une chaîne
t_type ClassAutomate::RetournerType(std::string type)
{
    if(type == "R") return R;
    if(type == "I") return I;
    if(type == "IT") return IT;
    if(type == "T") return T;
    return V;
}

std::vector<ClassEtat> ClassAutomate::GetEtats()
{
    return _etats;
}

std::vector<ClassTransition> ClassAutomate::GetTransitions()
{
    return _transitions;
}

std::vector<char> ClassAutomate::GetEtiquettes()
{
    return _etiquettes;
}

void ClassAutomate::SetEtats(std::vector<ClassEtat> etats)
{
    _etats = etats;
}

void ClassAutomate::SetTransitions(std::vector<ClassTransition> transitions)
{
    _transitions = transitions;
}

void ClassAutomate::SetEtiquettes(std::vector<char> etiquettes)
{
    _etiquettes = etiquettes;
}

/*
int ClassAutomate::GetNbEtiquettes()
{
    return _nbEtiquettes;
}

void ClassAutomate::SetNbEtiquettes(int nb)
{
    _nbEtiquettes = nb;
}
*/

// Affichage de la table d'un automate
void ClassAutomate::Afficher(std::string nom)
{
    int cpt;

    // Première ligne du tableau
    cout << nom << "\tEtat";
    for(unsigned int i = 0; i < _etiquettes.size(); i++)
    {
        cout << "\t" << _etiquettes[i];
    }
    cout << "\n";

    for(unsigned int i = 0; i < _etats.size(); i++)
    {
        switch(_etats[i].GetType())
        {
            case 0: cout << " "; break;
            case 1: cout << "I"; break;
            case 2: cout << "IT"; break;
            case 3: cout << "T"; break;
            case 4: cout << "V"; break;
        }

        cout << "\t" << _etats[i].GetRef() << "\t";

        for(unsigned int j = 0; j < _etiquettes.size(); j++)
        {
            cpt = 0;
            for(unsigned int k = 0; k < _transitions.size(); k++)
            {
                if(_etats[i] == _transitions[k].GetOrigine() && _etiquettes[j] == _transitions[k].GetEtiquette())
                {
                    if(cpt != 0) cout << ";";
                    cout << _transitions[k].GetDestination().GetRef();

                    cpt++;
                }
            }

            if(cpt == 0) cout << "-";
            cout << "\t";
        }
        cout << "\n";
    }
}

// Affiche les partitions de l'automate (minimal)
void ClassAutomate::AfficherPartitions(int n)
{
    int cpt;

    // Première ligne du tableau
    cout << "\tP" << n;
    for(unsigned int i = 0; i < _etiquettes.size(); i++)
    {
        cout << "\t" << _etiquettes[i];
    }
    cout << "\n";

    for(unsigned int i = 0; i < _etats.size(); i++)
    {
        switch(_etats[i].GetType())
        {
            case 0: cout << " "; break;
            case 1: cout << "I"; break;
            case 2: cout << "IT"; break;
            case 3: cout << "T"; break;
            case 4: cout << "V"; break;
        }

        cout << "\t" << _etats[i].GetPartition() << "\t";

        for(unsigned int j = 0; j < _etiquettes.size(); j++)
        {
            cpt = 0;
            for(unsigned int k = 0; k < _transitions.size(); k++)
            {
                if(_etats[i] == _transitions[k].GetOrigine() && _etiquettes[j] == _transitions[k].GetEtiquette())
                {
                    if(cpt != 0) cout << ";";
                    cout << _transitions[k].GetDestination().GetPartition();

                    cpt++;
                }
            }

            if(cpt == 0) cout << "-";
            cout << "\t";
        }
        cout << "\n";
    }
    cout << "\n";
}

// Lecture d'un mot
bool ClassAutomate::LectureMot(std::string mot)
{
    // mot trop court (fin d’analyse sur un état non terminal)
    // symbole non attendu (transition vers l’état poubelle de l’AFDC, ou absence de transition dans un AFD non complet).

    // Recherche de l'état initial
    // Suivre les transitions à partir de l'état initial
    // si le mot fini sur un état non terminal -> non ok
    // si un caractère du mot finit dans l'état poubelle ou pas de transition pour un état -> non ok
    // sinon ok

    ClassEtat EtatInitial, EtatEnCours;
    unsigned int cpt(0);
    bool transition;

    // Recherche de l'état initial
    for(unsigned int i = 0; i < _etats.size(); i++)
    {
        if(_etats[i].GetType() == I || _etats[i].GetType() == IT)
        {
            EtatInitial = _etats[i];
            EtatEnCours = _etats[i];
        }
    }

    // Reconnaissance du mot vide
    if(mot == "." && (EtatEnCours.GetType() == T || EtatEnCours.GetType() == IT)) return true;

    cpt = 0; // Début du mot
    do
    {
        transition = false;
        // Suivre les transitions à partir de l'état courant (ou initial)
        for(unsigned int i = 0; i < _transitions.size(); i++)
        {
            // Action seulement si l'état en cours correspond à l'état d'origine d'une transition
            if(EtatEnCours == _transitions[i].GetOrigine())
            {
                // Si un caractère peut être lu => L'état destination de la transition devient l'état courant
                if(mot[cpt] == _transitions[i].GetEtiquette())
                {
                    EtatEnCours = _transitions[i].GetDestination();
                    cpt++;
                    transition = true;
                }
            }
        }

        // Si le mot finit sur un état non terminal
        if(cpt >= mot.size() - 1 && (EtatEnCours.GetType() != T && EtatEnCours.GetType() != IT)) return false;
        // Si le mot finit dans l'état poubelle ou dans un état où il n'y a plus de transition
        if((!transition) || (VerifEtatPoubelle(EtatEnCours) && EtatEnCours.GetType() != T && EtatEnCours.GetType() != IT)) return false;
    } while(cpt < (mot.size() - 1));
    return true;
}

// Vérifie si un état est un état poubelle
bool ClassAutomate::VerifEtatPoubelle(ClassEtat EtatP)
{
    unsigned int cpt(0);
    for(unsigned int i = 0; i < _transitions.size(); i++)
    {
        if(EtatP == _transitions[i].GetOrigine())
        {
            if(_transitions[i].GetOrigine() == _transitions[i].GetDestination())
            {
                cpt++;
            }
        }
    }

    if(cpt >= _etiquettes.size() - 1) return true;

    return false;
}
