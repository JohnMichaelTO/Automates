#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "BallasMoraTo-ClassEtat.h"
#include "BallasMoraTo-ClassTransition.h"
#include "BallasMoraTo-ClassAutomate.h"
#include "BallasMoraTo-Fonctions.h"

using namespace std;

// Retourne l'indice correspondant à une transition parmi une liste
int RechercheCptTrans(vector<t_cptTrans> liste, t_cptTrans e)
{
    for(unsigned int i = 0; i < liste.size(); i++)
    {
        if(liste[i].etiquette == e.etiquette && liste[i].etat == e.etat) return i;
    }
    return -1;
}

// Formate une chaîne pour avoir la référence des états dans l'ordre et supprime les doublons
std::string FormaterString(std::string input, std::string delimiteur)
{
    std::string output("");
    vector<std::string> AOrdonner = cut(input, delimiteur), Nouveau;
    vector<int> ordonner(StringToInt(AOrdonner)), NouveauTab;
    ordonner = TrierInt(ordonner);
    int j(0);

    NouveauTab.push_back(ordonner[0]);

    for(unsigned int i = 1; i < ordonner.size(); i++)
    {
        if(NouveauTab[j] != ordonner[i])
        {
            NouveauTab.push_back(ordonner[i]);
            j++;
        }
    }

    Nouveau = IntToString(NouveauTab);

    for(unsigned int i = 0; i < Nouveau.size(); i++)
    {
        if(i != 0) output += delimiteur;
        output += Nouveau[i];
    }
    return output;
}

// Conversion d'un tableau de string en tableau de int
std::vector<int> StringToInt(std::vector<std::string> input)
{
    std::vector<int> output;
    for(unsigned int i = 0; i < input.size(); i++)
    {
        if(input[i] == "I") output.push_back(-1);       // Exception pour le I dans la standardisation
        else if(input[i] == "P") output.push_back(-2);  // Exception pour le P (état poubelle)
        else
        {
            std::istringstream temp(input[i]);
            int nb;
            temp >> nb;
            output.push_back(nb);
        }
    }
    return output;
}

// Conversion d'un tableau de int en tableau de string
std::vector<std::string> IntToString(std::vector<int> input)
{
    std::vector<std::string> output;
    std::string out;
    for(unsigned int i = 0; i < input.size(); i++)
    {
        if(input[i] == -1) output.push_back("I");       // Exception pour le I dans la standardisation
        else if(input[i] == -2) output.push_back("P");  // Exception pour le P (état poubelle)
        else
        {
            std::ostringstream temp;
            temp << input[i];
            std::string out = temp.str();
            output.push_back(out);
        }
    }
    return output;
}

// Tri un tableau de int dans l'ordre
std::vector<int> TrierInt(std::vector<int> t)
{
    bool desordre = true;
    for (unsigned int i = 0; i < t.size() && desordre; i++)
    {
        desordre = false;
        for (unsigned int j = 1; j < t.size() - i; j++)
        {
            if (t[j-1] > t[j])
            {
                swap(t[j], t[j-1]);
                desordre = true;
            }
        }
    }
    return t;
}

// Fonction swap
void swap(int &x, int &y)
{
    int temp;
    temp = x;
    x = y;
    y = temp;
}

// Retourne le nouveau type lors du regroupement de plusieurs états
t_type ChercherNouveauType(std::vector<ClassEtat> Etats, std::string e)
{
    std::vector<string> decomp = cut(e, ",");

    for(unsigned int i = 0; i < decomp.size(); i++)
    {
        for(unsigned int j = 0; j < Etats.size(); j++)
        {
            if(decomp[i] == Etats[j].GetRef())
            {
                if(Etats[j].GetType() == T || Etats[j].GetType() == IT) return T;
            }
        }
    }
    return R;
}

// Recherche d'un état à partir d'une liste de plusieurs états avec un booléen en résultat
bool RechercherEtat(std::vector<ClassEtat> liste, ClassEtat e, bool verifType)
{
    unsigned int i;

    for(i = 0; i < liste.size(); i++)
    {
        if(verifType && e == liste[i]) return true;
        else if(e.GetRef() == liste[i].GetRef()) return true;
    }
    return false;
}

// Recherche d'une partition d'un état à partir d'une liste de plusieurs états avec un booléen en résultat
bool RechercherEtatParPartition(std::vector<ClassEtat> liste, char e)
{
    unsigned int i;

    for(i = 0; i < liste.size(); i++)
    {
        if(e == liste[i].GetPartition()) return true;
    }
    return false;
}

// Recherche d'un état à partir d'une liste de plusieurs états avec un état en résultat
ClassEtat RetournerEtat(std::vector<ClassEtat> liste, std::string e)
{
    unsigned int i;
    ClassEtat a;

    for(i = 0; i < liste.size(); i++)
    {
        if(e == liste[i].GetRef()) return liste[i];
    }
    return a;
}

// Recherche d'une partition d'un état à partir d'une liste de plusieurs états avec un état en résultat
ClassEtat RetournerEtatParPartition(std::vector<ClassEtat> liste, char e)
{
    unsigned int i;
    ClassEtat a;

    for(i = 0; i < liste.size(); i++)
    {
        if(e == liste[i].GetPartition()) return liste[i];
    }
    return a;
}

// Recherche d'une transition à partir d'une liste de transitions avec un booléen en résultat
bool RechercherTransition(std::vector<ClassTransition> liste, ClassTransition e)
{
    unsigned int i;

    for(i = 0; i < liste.size(); i++)
    {
        if(e == liste[i]) return true;
    }
    return false;
}

// Recherche d'une transition à partir d'une liste de transitions avec une transition en résultat
ClassTransition RetournerTransition(std::vector<ClassTransition> liste, ClassTransition e)
{
    unsigned int i;
    ClassTransition a;

    for(i = 0; i < liste.size(); i++)
    {
        if(e == liste[i]) return liste[i];
    }
    return a;
}

// Retourne si un automate est standard ou non
bool isStandard(ClassAutomate Automate)
{
    int cpt(0);

    for(unsigned int i = 0; i < Automate.GetTransitions().size(); i++)
    {
        if(Automate.GetTransitions()[i].GetDestination().GetType() == I) return false;
    }

    for(unsigned int i = 0; i < Automate.GetEtats().size(); i++)
    {
        if(Automate.GetEtats()[i].GetType() == IT) cpt++;
        if(Automate.GetEtats()[i].GetType() == I) cpt++;

        if(cpt > 1) return false;
    }
    return true;
}

// Standardise un automate
ClassAutomate Standardiser(ClassAutomate Automate)
{
    if(!isStandard(Automate))
    {
        ClassAutomate AutomateStandard;
        ClassEtat Etat0, Etat;
        ClassTransition Transition0, Transition;
        vector<ClassEtat> EtatsNouveau;
        vector<ClassTransition> TransitionsNouveau;

        AutomateStandard.SetEtiquettes(Automate.GetEtiquettes());

        // Ajout de l'état I
        Etat0.Set(I, "I");
        EtatsNouveau.push_back(Etat0);

        // Retire le type terminal de chaque état
        for(unsigned int i = 0; i < Automate.GetEtats().size(); i++)
        {
            if(Automate.GetEtats()[i].GetType() == I)
            {
                Etat.Set(R, Automate.GetEtats()[i].GetRef());
            }
            else if(Automate.GetEtats()[i].GetType() == IT)
            {
                Etat.Set(T, Automate.GetEtats()[i].GetRef());
            }
            else
            {
                Etat = Automate.GetEtats()[i];
            }

            if(!RechercherEtat(EtatsNouveau, Etat, true)) EtatsNouveau.push_back(Etat);
        }

        // Procédure de standardisation avec les transitions
        for(unsigned int i = 0; i < Automate.GetTransitions().size(); i++)
        {
            // Mettre les transitions de destination des états initiaux à l'état I & Retirer tous les types I sauf à l'état I et mettre un R à la place
            if(Automate.GetTransitions()[i].GetOrigine().GetType() == I || Automate.GetTransitions()[i].GetOrigine().GetType() == IT)
            {
                // Mettre les transitions de destination des états initiaux à l'état I
                Transition0.Set(Automate.GetTransitions()[i].GetEtiquette(), Etat0, Automate.GetTransitions()[i].GetDestination());
                if(!RechercherTransition(TransitionsNouveau, Transition0)) TransitionsNouveau.push_back(Transition0);

                // Retirer tous les types I sauf à l'état I et mettre un R à la place
                if(Automate.GetTransitions()[i].GetOrigine().GetType() == I)
                {
                    Etat.Set(R, Automate.GetTransitions()[i].GetOrigine().GetRef());
                }
                else
                {
                    Etat.Set(T, Automate.GetTransitions()[i].GetOrigine().GetRef());
                }

                Transition.Set(Automate.GetTransitions()[i].GetEtiquette(), Etat, Automate.GetTransitions()[i].GetDestination());
                if(!RechercherTransition(TransitionsNouveau, Transition)) TransitionsNouveau.push_back(Transition);
            }
            else
            {
                Transition.Set(Automate.GetTransitions()[i].GetEtiquette(), Automate.GetTransitions()[i].GetOrigine(), Automate.GetTransitions()[i].GetDestination());
                if(!RechercherTransition(TransitionsNouveau, Transition)) TransitionsNouveau.push_back(Transition);
            }
        }

        AutomateStandard.SetEtats(EtatsNouveau);
        AutomateStandard.SetTransitions(TransitionsNouveau);

        return AutomateStandard;
    }
    else
    {
        return Automate;
    }
}

// Retourne si un automate est déterministe ou non
bool isDeterministe(ClassAutomate Automate)
{
    int cpt(0), j;
    vector<t_cptTrans> cptTransitions;
    t_cptTrans temp;

    // Vérifier qu'il n'y a qu'un seul état initial
    for(unsigned int i = 0; i < Automate.GetEtats().size(); i++)
    {
        if(Automate.GetEtats()[i].GetType() == I || Automate.GetEtats()[i].GetType() == IT) cpt++;

        if(cpt > 1) return false;
    }

    // Vérifier qu'il n'y a pas 2 transitions portant la même étiquette partant d'un même état
    for(unsigned int i = 0; i < Automate.GetTransitions().size(); i++)
    {
        temp.etat = Automate.GetTransitions()[i].GetOrigine();
        temp.etiquette = Automate.GetTransitions()[i].GetEtiquette();
        temp.cpt = 1;

        if(cptTransitions.size() > 0 && (j = RechercheCptTrans(cptTransitions, temp)) != -1)
        {
            cptTransitions[j].cpt = cptTransitions[j].cpt + 1;
            if(cptTransitions[j].cpt >= 2) return false;
        }
        else
        {
            cptTransitions.push_back(temp);
        }
    }
    return true;
}

// Déterminise un automate
ClassAutomate Determiniser(ClassAutomate Automate)
{
    if(!isDeterministe(Automate))
    {
        // Regrouper les états initiaux
        // Mettre les transitions correspondantes à chaque état initial provenant de la table de transition normale, ce qui forme des groupes
        // Prendre ces groupes comme nouveaux états puis faire de même, ainsi de suite.
        // Pour chaque état contenant un état terminal, mettre l'état terminal dans chacun des groupes contenant ce même état.
        ClassAutomate AutomateDeterministe;
        ClassEtat Etat;
        ClassTransition Transition;
        vector<ClassEtat> EtatsNouveau;
        vector<ClassTransition> TransitionsNouveau;
        vector<string> EtatTemp;
        string temp("");
        int cpt(0);
        unsigned int l(0);
        t_type Type(I);

        AutomateDeterministe.SetEtiquettes(Automate.GetEtiquettes());

        // Regrouper les états initiaux
        for(unsigned int i = 0; i < Automate.GetEtats().size(); i++)
        {
            if(Automate.GetEtats()[i].GetType() == I || Automate.GetEtats()[i].GetType() == IT)
            {
                if(Automate.GetEtats()[i].GetType() == IT) Type = IT;

                if(cpt != 0) temp += ",";
                temp += Automate.GetEtats()[i].GetRef();
                cpt++;
            }
        }

        temp = FormaterString(temp, ",");
        Etat.Set(Type, temp);
        if(!RechercherEtat(EtatsNouveau, Etat, true)) EtatsNouveau.push_back(Etat);

        while(l < EtatsNouveau.size())
        {
            EtatTemp = cut(EtatsNouveau[l].GetRef(), ",");

            for(unsigned int k = 0; k < AutomateDeterministe.GetEtiquettes().size(); k++)
            {
                cpt = 0;
                temp = "";
                for(unsigned int i = 0; i < EtatTemp.size(); i++)
                {
                    for(unsigned int j = 0; j < Automate.GetTransitions().size(); j++)
                    {
                        if(EtatTemp[i] == Automate.GetTransitions()[j].GetOrigine().GetRef() && AutomateDeterministe.GetEtiquettes()[k] == Automate.GetTransitions()[j].GetEtiquette())
                        {
                            if(cpt != 0) temp += ",";
                            temp += Automate.GetTransitions()[j].GetDestination().GetRef();
                            cpt++;
                        }
                    }
                }
                if(cpt != 0)
                {
                    temp = FormaterString(temp, ",");
                    Etat.Set(ChercherNouveauType(Automate.GetEtats(), temp), temp);
                    if(!RechercherEtat(EtatsNouveau, Etat, false)) EtatsNouveau.push_back(Etat);

                    Transition.Set(AutomateDeterministe.GetEtiquettes()[k], EtatsNouveau[l], Etat);
                    if(!RechercherTransition(TransitionsNouveau, Transition)) TransitionsNouveau.push_back(Transition);

                    // cout << AutomateDeterministe.GetEtiquettes()[k] << " : " << EtatsNouveau[l].GetRef() << "->" << Etat.GetRef() << endl;
                }
            }
            l++;
        }

        /**************************************************************/
        /*
        if(EtatsNouveau[0].GetType() == IT)
        {
            for(int i = 0; i < EtatsNouveau.size(); i++)
            {
                for(int j = 0; j < Automate.GetEtats().size(); j++)
                {
                    if(EtatsNouveau[i].GetRef() == Automate.GetEtats()[j].GetRef() && Automate.GetEtats()[j].GetType() == IT)
                    {
                        EtatsNouveau[0].Set(I, EtatsNouveau[0].GetRef());

                        for(int k = 0; k < TransitionsNouveau.size(); k++)
                        {
                            if(TransitionsNouveau[k].GetOrigine().GetRef() == EtatsNouveau[0].GetRef())
                            {
                                TransitionsNouveau[k].Set(TransitionsNouveau[k].GetEtiquette(), EtatsNouveau[0], TransitionsNouveau[k].GetDestination());
                            }
                        }
                    }
                }
            }
        }
        */
        /**************************************************************/

        AutomateDeterministe.SetEtats(EtatsNouveau);
        AutomateDeterministe.SetTransitions(TransitionsNouveau);

        return AutomateDeterministe;
    }
    else
    {
        return Automate;
    }
}

// Retourne si un automate est complet ou non
bool isComplet(ClassAutomate Automate)
{
    int cpt;

    for(unsigned int i = 0; i < Automate.GetEtats().size(); i++)
    {
        for(unsigned int j = 0; j < Automate.GetEtiquettes().size(); j++)
        {
            cpt = 0;
            for(unsigned int k = 0; k < Automate.GetTransitions().size(); k++)
            {
                if(Automate.GetEtats()[i] == Automate.GetTransitions()[k].GetOrigine() && Automate.GetEtiquettes()[j] == Automate.GetTransitions()[k].GetEtiquette())
                {
                    cpt++;
                }
            }

            if(cpt == 0) return false;
        }
    }
    return true;
}

// Complète un automate
ClassAutomate Completer(ClassAutomate Automate)
{
    ClassTransition Transition;
    ClassAutomate AutomateComplet;
    vector<ClassEtat> EtatsNouveau;
    vector<ClassTransition> TransitionsNouveau;
    ClassEtat P;
    int cpt;
    bool PoubelleExiste(false);

    P.Set(R, "P"); // Etat poubelle

    AutomateComplet.SetEtiquettes(Automate.GetEtiquettes());
    EtatsNouveau = Automate.GetEtats();
    TransitionsNouveau = Automate.GetTransitions();

    for(unsigned int i = 0; i < EtatsNouveau.size(); i++)
    {
        for(unsigned int j = 0; j < AutomateComplet.GetEtiquettes().size(); j++)
        {
            cpt = 0;
            for(unsigned int k = 0; k < TransitionsNouveau.size(); k++)
            {
                if(EtatsNouveau[i] == TransitionsNouveau[k].GetOrigine() && AutomateComplet.GetEtiquettes()[j] == TransitionsNouveau[k].GetEtiquette())
                {
                    cpt++;
                }
            }

            if(cpt == 0)
            {
                Transition.Set(AutomateComplet.GetEtiquettes()[j], EtatsNouveau[i], P);
                if(!RechercherTransition(TransitionsNouveau, Transition)) TransitionsNouveau.push_back(Transition);
                PoubelleExiste = true;
            }
        }
    }

    if(PoubelleExiste)
    {
        for(unsigned int i = 0; i < AutomateComplet.GetEtiquettes().size(); i++)
        {
            Transition.Set(AutomateComplet.GetEtiquettes()[i], P, P);
            if(!RechercherTransition(TransitionsNouveau, Transition)) TransitionsNouveau.push_back(Transition);
        }
        EtatsNouveau.push_back(P);
    }

    AutomateComplet.SetEtats(EtatsNouveau);
    AutomateComplet.SetTransitions(TransitionsNouveau);

    return AutomateComplet;
}

// Minimise un automate
ClassAutomate Minimiser(ClassAutomate Automate)
{
    int n(0);
    ClassAutomate AutomatePrec, AutomateMinimal;

    AutomatePrec = CompleterPartition0(Automate);
    AutomatePrec.AfficherPartitions(n);
    n++;
    AutomateMinimal = CompleterPartition(AutomatePrec);
    AutomateMinimal.AfficherPartitions(n);

    while(!ComparerAutomateMinimal(AutomatePrec, AutomateMinimal))
    {
        n++;
        AutomatePrec = AutomateMinimal;
        AutomateMinimal = CompleterPartition(AutomateMinimal);
        AutomateMinimal.AfficherPartitions(n);
    }

    AutomateMinimal = SupprimerEtatsIdentiques(AutomateMinimal);

    return AutomateMinimal;
}

// Création de la partition 0 d'un automate
ClassAutomate CompleterPartition0(ClassAutomate Automate)
{
    ClassAutomate AutomatePartition0;
    vector<ClassEtat> EtatsNouveau;
    vector<ClassTransition> TransitionsNouveau;

    AutomatePartition0.SetEtiquettes(Automate.GetEtiquettes());
    EtatsNouveau = Automate.GetEtats();
    TransitionsNouveau = Automate.GetTransitions();

    for(unsigned int i = 0; i < EtatsNouveau.size(); i++)
    {
        if(EtatsNouveau[i].GetType() == IT || EtatsNouveau[i].GetType() == T)
        {
            EtatsNouveau[i].SetPartition('B'); // On définit B pour les états terminaux
        }
        else
        {
            EtatsNouveau[i].SetPartition('A'); // On définit A pour les états non-terminaux
        }
    }

    MAJTransitions(TransitionsNouveau, EtatsNouveau);

    AutomatePartition0.SetEtats(EtatsNouveau);
    AutomatePartition0.SetTransitions(TransitionsNouveau);

    return AutomatePartition0;
}

// Création d'une partition successive
ClassAutomate CompleterPartition(ClassAutomate Automate)
{
    ClassAutomate AutomatePartition;
    vector<ClassEtat> EtatsNouveau;
    vector<ClassTransition> TransitionsNouveau, TransitionsCompare;

    unsigned int cpt;
    char partition('A');

    AutomatePartition.SetEtiquettes(Automate.GetEtiquettes());
    EtatsNouveau = Automate.GetEtats();
    TransitionsNouveau = Automate.GetTransitions();

    // Retire toutes les partitions
    for(unsigned int i = 0; i < EtatsNouveau.size(); i++)
    {
        EtatsNouveau[i].SetPartition('0');
    }

    for(unsigned int i = 0; i < Automate.GetEtats().size(); i++)
    {
        /*******************************************************************************************************/
        /************** Comparer les Etats/Transitions pour faire une nouvelle partition ***********************/
        /*******************************************************************************************************/
        /****************************************************************************************************************************/

        // Pour tout état qui n'a pas sa partition actualisée
        if(EtatsNouveau[i].GetPartition() == '0')
        {
            EtatsNouveau[i].SetPartition(partition); // On lui attribue une partition

            // Récupère dans un tableau toutes les transitions de l'état actif
            for(unsigned int j = 0; j < Automate.GetTransitions().size(); j++)
            {
                if(Automate.GetEtats()[i] == Automate.GetTransitions()[j].GetOrigine())
                {
                    TransitionsCompare.push_back(Automate.GetTransitions()[j]);
                }
            }

            // Comparaison aux autres états
            for(unsigned int j = 0; j < Automate.GetEtats().size(); j++)
            {
                if(i != j)
                {
                    cpt = 0;
                    for(unsigned int k = 0; k < Automate.GetTransitions().size(); k++)
                    {
                        if(Automate.GetEtats()[j] == Automate.GetTransitions()[k].GetOrigine())
                        {
                            for(unsigned int l = 0; l < TransitionsCompare.size(); l++)
                            {
                                // if(Automate.GetTransitions()[k] == TransitionsCompare[l]) cpt++;
                                if(Automate.GetTransitions()[k].GetOrigine().GetPartition() == TransitionsCompare[l].GetOrigine().GetPartition())
                                {
                                    if(Automate.GetTransitions()[k].GetDestination().GetPartition() == TransitionsCompare[l].GetDestination().GetPartition())
                                    {
                                        if(Automate.GetTransitions()[k].GetEtiquette() == TransitionsCompare[l].GetEtiquette()) cpt++;
                                    }
                                }
                            }
                        }
                    }

                    if(cpt >= Automate.GetEtiquettes().size())
                    {
                        EtatsNouveau[j].SetPartition(partition);
                    }
                }
            }
            TransitionsCompare.clear();
            partition++;
        }

        /*
        if(!RechercherEtat(EtatsCompare, Automate.GetEtats()[i], true))
        {
            // Récupère dans un tableau toutes les transitions de l'état actif
            for(unsigned int j = 0; j < Automate.GetTransitions().size(); j++)
            {
                if(Automate.GetEtats()[i] == Automate.GetTransitions()[j].GetOrigine())
                {
                    TransitionsCompare.push_back(Automate.GetTransitions()[j]);
                }
            }

            for(unsigned int j = 0; j < Automate.GetEtats().size(); j++)
            {
                if(i != j)
                {
                    cpt = 0;
                    for(unsigned int k = 0; k < Automate.GetTransitions().size(); k++)
                    {
                        if(Automate.GetEtats()[j] == Automate.GetTransitions()[k].GetOrigine())
                        {
                            for(unsigned int l = 0; l < TransitionsCompare.size(); l++)
                            {
                                if(Automate.GetTransitions()[k].GetEtiquette() == TransitionsCompare[l].GetEtiquette())
                                {
                                    if(Automate.GetTransitions()[k].GetDestination().GetPartition() == TransitionsCompare[l].GetDestination().GetPartition()) cpt++;
                                }
                            }
                        }
                    }

                    if(cpt >= Automate.GetEtiquettes().size())
                    {
                        EtatsNouveau[j].SetPartition(partition);
                        EtatsCompare.push_back(EtatsNouveau[j]);
                    }
                }
            }
            TransitionsCompare.clear();
            EtatsNouveau[i].SetPartition(partition);
            EtatsCompare.push_back(EtatsNouveau[i]);
            partition++;

        }*/
        /****************************************************************************************************************************/

    }

    MAJTransitions(TransitionsNouveau, EtatsNouveau);

    AutomatePartition.SetEtats(EtatsNouveau);
    AutomatePartition.SetTransitions(TransitionsNouveau);

    return AutomatePartition;
}

// Met à jour les transitions d'un automate en fonction des états
void MAJTransitions(std::vector<ClassTransition> &Transitions, std::vector<ClassEtat> Etats)
{
    for(unsigned int i = 0; i < Transitions.size(); i++)
    {
        Transitions[i].SetOrigine(RetournerEtat(Etats, Transitions[i].GetOrigine().GetRef()));
        Transitions[i].SetDestination(RetournerEtat(Etats, Transitions[i].GetDestination().GetRef()));
    }
}

// Met à jour les transitions d'un automate en fonction des partitions des états
void MAJTransitionsPartitions(std::vector<ClassTransition> &Transitions, std::vector<ClassEtat> Etats)
{
    for(unsigned int i = 0; i < Transitions.size(); i++)
    {
        Transitions[i].SetOrigine(RetournerEtatParPartition(Etats, Transitions[i].GetOrigine().GetPartition()));
        Transitions[i].SetDestination(RetournerEtatParPartition(Etats, Transitions[i].GetDestination().GetPartition()));
    }
}

// Compare les partitions de deux automates
bool ComparerAutomateMinimal(ClassAutomate Automate1, ClassAutomate Automate2)
{
    if(Automate1.GetEtats().size() != Automate2.GetEtats().size()) return false;
    if(Automate1.GetEtats().size() < 1) return false;
    if(Automate2.GetEtats().size() < 1) return false;

    for(unsigned i = 0; i < Automate1.GetEtats().size(); i++)
    {
        if(Automate1.GetEtats()[i].GetPartition() != Automate2.GetEtats()[i].GetPartition()) return false;
    }

    return true;
}

// Simplifie un automate minimal en regroupant les partitions identiques
ClassAutomate SupprimerEtatsIdentiques(ClassAutomate Automate)
{
    std::string ref;
    bool entree, sortie;
    t_type type;
    ClassAutomate AutomateClean;
    ClassEtat Etat;
    vector<ClassEtat> EtatsNouveau, EtatsCompare;
    vector<ClassTransition> TransitionsNouveau, Transitions;
    AutomateClean.SetEtiquettes(Automate.GetEtiquettes());
    Transitions = Automate.GetTransitions();

    for(unsigned int i = 0; i < Automate.GetEtats().size(); i++)
    {
        if(!RechercherEtat(EtatsCompare, Automate.GetEtats()[i], true))
        {
            EtatsCompare.push_back(Automate.GetEtats()[i]);
            ref = Automate.GetEtats()[i].GetRef();
            entree = false;
            sortie = false;

            for(unsigned int j = 0; j < Automate.GetEtats().size(); j++)
            {
                if(i != j && Automate.GetEtats()[i].GetPartition() == Automate.GetEtats()[j].GetPartition())
                {
                    if(Automate.GetEtats()[i].GetType() == I && Automate.GetEtats()[j].GetType() == T) { entree = true; sortie = true; }
                    else if(Automate.GetEtats()[i].GetType() == T && Automate.GetEtats()[j].GetType() == I) { entree = true; sortie = true; }
                    else if(Automate.GetEtats()[i].GetType() == IT || Automate.GetEtats()[j].GetType() == IT) { entree = true; sortie = true; }
                    else if(Automate.GetEtats()[i].GetType() == I || Automate.GetEtats()[j].GetType() == I) entree = true;
                    else if(Automate.GetEtats()[i].GetType() == T || Automate.GetEtats()[j].GetType() == T) sortie = true;

                    EtatsCompare.push_back(Automate.GetEtats()[j]);
                    ref += "," + Automate.GetEtats()[j].GetRef();
                }
            }

            if(entree && sortie) type = IT;
            else if(entree) type = I;
            else if(sortie) type = T;
            else type = Automate.GetEtats()[i].GetType();

            Etat.Set(type, FormaterString(ref, ","));
            Etat.SetPartition(Automate.GetEtats()[i].GetPartition());
            EtatsNouveau.push_back(Etat);
        }
    }

    MAJTransitionsPartitions(Transitions, EtatsNouveau);

    for(unsigned int i = 0; i < Transitions.size(); i++)
    {
        if(!RechercherTransition(TransitionsNouveau, Transitions[i]))
        {
            TransitionsNouveau.push_back(Transitions[i]);
        }
    }

    AutomateClean.SetEtats(EtatsNouveau);
    AutomateClean.SetTransitions(TransitionsNouveau);

    return AutomateClean;
}

/*************************************************************************************/
// Renverse un automate
ClassAutomate Renverser(ClassAutomate Automate)
{
    ClassTransition Transition;
    ClassAutomate AutomateRenverse;
    vector<ClassEtat> EtatsNouveau;
    vector<ClassTransition> TransitionsNouveau;

    AutomateRenverse.SetEtiquettes(Automate.GetEtiquettes());
    EtatsNouveau = Automate.GetEtats();

    for(unsigned int i = 0; i < Automate.GetTransitions().size(); i++)
    {
        Transition.Set(Automate.GetTransitions()[i].GetEtiquette(), Automate.GetTransitions()[i].GetDestination(), Automate.GetTransitions()[i].GetOrigine());
        if(!RechercherTransition(TransitionsNouveau, Transition)) TransitionsNouveau.push_back(Transition);
    }

    AutomateRenverse.SetEtats(EtatsNouveau);
    AutomateRenverse.SetTransitions(TransitionsNouveau);

    return AutomateRenverse;
}
