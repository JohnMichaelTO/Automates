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

// Retourne l'indice correspondant � une transition parmi une liste
int RechercheCptTrans(std::vector<t_cptTrans> liste, t_cptTrans e);
// Formate une cha�ne pour avoir la r�f�rence des �tats dans l'ordre et supprime les doublons
std::string FormaterString(std::string input, std::string delimiteur);
// Conversion d'un tableau de string en tableau de int
std::vector<int> StringToInt(std::vector<std::string> input);
// Conversion d'un tableau de int en tableau de string
std::vector<std::string> IntToString(std::vector<int> input);
// Tri un tableau de int dans l'ordre
std::vector<int> TrierInt(std::vector<int> t);
// Fonction swap
void swap(int &x, int &y);
// Retourne le nouveau type lors du regroupement de plusieurs �tats
t_type ChercherNouveauType(std::vector<ClassEtat> Etats, std::string e);
// Recherche d'un �tat � partir d'une liste de plusieurs �tats avec un bool�en en r�sultat
bool RechercherEtat(std::vector<ClassEtat> liste, ClassEtat, bool verifType);
// Recherche d'une partition d'un �tat � partir d'une liste de plusieurs �tats avec un bool�en en r�sultat
bool RechercherEtatParPartition(std::vector<ClassEtat> liste, char e);
// Recherche d'un �tat � partir d'une liste de plusieurs �tats avec un �tat en r�sultat
ClassEtat RetournerEtat(std::vector<ClassEtat> liste, std::string e);
// Recherche d'une partition d'un �tat � partir d'une liste de plusieurs �tats avec un �tat en r�sultat
ClassEtat RetournerEtatParPartition(std::vector<ClassEtat> liste, char e);
// Recherche d'une transition � partir d'une liste de transitions avec un bool�en en r�sultat
bool RechercherTransition(std::vector<ClassTransition> liste, ClassTransition e);
// Recherche d'une transition � partir d'une liste de transitions avec une transition en r�sultat
ClassTransition RetournerTransition(std::vector<ClassTransition> liste, ClassTransition e);

// Retourne si un automate est standard ou non
bool isStandard(ClassAutomate Automate);
// Standardise un automate
ClassAutomate Standardiser(ClassAutomate Automate);
// Retourne si un automate est d�terministe ou non
bool isDeterministe(ClassAutomate Automate);
// D�terminise un automate
ClassAutomate Determiniser(ClassAutomate Automate);
// Retourne si un automate est complet ou non
bool isComplet(ClassAutomate Automate);
// Compl�te un automate
ClassAutomate Completer(ClassAutomate Automate);
// Minimise un automate
ClassAutomate Minimiser(ClassAutomate Automate);
// Cr�ation de la partition 0 d'un automate
ClassAutomate CompleterPartition0(ClassAutomate Automate);
// Cr�ation d'une partition successive
ClassAutomate CompleterPartition(ClassAutomate Automate);
// Met � jour les transitions d'un automate en fonction des �tats
void MAJTransitions(std::vector<ClassTransition> &Transitions, std::vector<ClassEtat> Etats);
// Met � jour les transitions d'un automate en fonction des partitions des �tats
void MAJTransitionsPartitions(std::vector<ClassTransition> &Transitions, std::vector<ClassEtat> Etats);
// Compare les partitions de deux automates
bool ComparerAutomateMinimal(ClassAutomate Automate1, ClassAutomate Automate2);
// Simplifie un automate minimal en regroupant les partitions identiques
ClassAutomate SupprimerEtatsIdentiques(ClassAutomate Automate);
/*********************************************************/
// Renverse un automate
ClassAutomate Renverser(ClassAutomate Automate);

#endif // CLASSFONCTION_H
