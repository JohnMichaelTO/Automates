#ifndef CLASSFONCTION_H
#define CLASSFONCTION_H

#include <vector>
#include "BallasMoraTo-ClassEtat.h"
#include "BallasMoraTo-ClassTransition.h"

typedef struct s_cptTrans
{
    char etiquette;
    ClassEtat etat;
    int cpt;
} t_cptTrans;

// Retourne l'indice correspondant à une transition parmi une liste
int RechercheCptTrans(std::vector<t_cptTrans> liste, t_cptTrans e);
// Formate une chaîne pour avoir la référence des états dans l'ordre et supprime les doublons
std::string FormaterString(std::string input, std::string delimiteur);
// Conversion d'un tableau de string en tableau de int
std::vector<int> StringToInt(std::vector<std::string> input);
// Conversion d'un tableau de int en tableau de string
std::vector<std::string> IntToString(std::vector<int> input);
// Tri un tableau de int dans l'ordre
std::vector<int> TrierInt(std::vector<int> t);
// Fonction swap
void swap(int &x, int &y);
// Retourne le nouveau type lors du regroupement de plusieurs états
t_type ChercherNouveauType(std::vector<ClassEtat> Etats, std::string e);
// Recherche d'un état à partir d'une liste de plusieurs états avec un booléen en résultat
bool RechercherEtat(std::vector<ClassEtat> liste, ClassEtat, bool verifType);
// Recherche d'une partition d'un état à partir d'une liste de plusieurs états avec un booléen en résultat
bool RechercherEtatParPartition(std::vector<ClassEtat> liste, char e);
// Recherche d'un état à partir d'une liste de plusieurs états avec un état en résultat
ClassEtat RetournerEtat(std::vector<ClassEtat> liste, std::string e);
// Recherche d'une partition d'un état à partir d'une liste de plusieurs états avec un état en résultat
ClassEtat RetournerEtatParPartition(std::vector<ClassEtat> liste, char e);
// Recherche d'une transition à partir d'une liste de transitions avec un booléen en résultat
bool RechercherTransition(std::vector<ClassTransition> liste, ClassTransition e);
// Recherche d'une transition à partir d'une liste de transitions avec une transition en résultat
ClassTransition RetournerTransition(std::vector<ClassTransition> liste, ClassTransition e);

// Retourne si un automate est standard ou non
bool isStandard(ClassAutomate Automate);
// Standardise un automate
ClassAutomate Standardiser(ClassAutomate Automate);
// Retourne si un automate est déterministe ou non
bool isDeterministe(ClassAutomate Automate);
// Déterminise un automate
ClassAutomate Determiniser(ClassAutomate Automate);
// Retourne si un automate est complet ou non
bool isComplet(ClassAutomate Automate);
// Complète un automate
ClassAutomate Completer(ClassAutomate Automate);
// Minimise un automate
ClassAutomate Minimiser(ClassAutomate Automate);
// Création de la partition 0 d'un automate
ClassAutomate CompleterPartition0(ClassAutomate Automate);
// Création d'une partition successive
ClassAutomate CompleterPartition(ClassAutomate Automate);
// Met à jour les transitions d'un automate en fonction des états
void MAJTransitions(std::vector<ClassTransition> &Transitions, std::vector<ClassEtat> Etats);
// Met à jour les transitions d'un automate en fonction des partitions des états
void MAJTransitionsPartitions(std::vector<ClassTransition> &Transitions, std::vector<ClassEtat> Etats);
// Compare les partitions de deux automates
bool ComparerAutomateMinimal(ClassAutomate Automate1, ClassAutomate Automate2);
// Simplifie un automate minimal en regroupant les partitions identiques
ClassAutomate SupprimerEtatsIdentiques(ClassAutomate Automate);
/*********************************************************/
// Renverse un automate
ClassAutomate Renverser(ClassAutomate Automate);

#endif // CLASSFONCTION_H
