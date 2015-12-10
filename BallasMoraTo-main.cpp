#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "BallasMoraTo-structures.h"
#include "BallasMoraTo-ClassEtat.h"
#include "BallasMoraTo-ClassTransition.h"
#include "BallasMoraTo-ClassAutomate.h"
#include "BallasMoraTo-Fonctions.h"

using namespace std;

// Fonction de découpe d'une chaîne en un tableau par le biais d'un délimiteur
vector<string> cut(const string &chaine, const string &delimiteur)
{
    int lChaine(chaine.size()), lDelimiteur(delimiteur.size()), i(0), j(0), k;
    vector<string> tab;

    if(lDelimiteur == 0) return tab;

    while(i < lChaine)
    {
        k = 0;
        while ((i + k) < lChaine && k < lDelimiteur && chaine[i + k] == delimiteur[k]) k++;

        if(k == lDelimiteur)
        {
            tab.push_back(chaine.substr(j, i - j));
            i += lDelimiteur;
            j = i;
        }
        else
        {
            i++;
        }
    }
    tab.push_back(chaine.substr(j, i - j));
    return tab;
}

// Petmet de retourner OUI/NON en fonction d'un booléen
std::string BooleenFormat(bool a)
{
    if(a) return "OUI";
    else return "NON";
}

int main()
{
    while(1)
    {
        ClassAutomate Automate, AutomateStandard, AutomateDeterministe, AutomateComplet, AutomateMinimal;
        std::string fichier, mot;
        int ChoixAutomate, recommencer, reponse;

        cout << "\n-------------------------- Chargement d'un automate\n\nNumero de l'automate a charger : ";
        cin >> fichier;

        if(Automate.LireFichier("BallasMoraTo-Automates/BallasMoraTo-" + fichier + ".txt"))
        {
            cout << "\n-------------------------- Automate " << fichier << " Fini\n";
            Automate.Afficher("AF");

            cout << "\n\nStandard : " << BooleenFormat(isStandard(Automate));

            cout << "\n-------------------------- Automate " << fichier << " Standard\n";
            AutomateStandard = Standardiser(Automate);

            AutomateStandard.Afficher("AFS");

            cout << "\n\nDeterministe : " << BooleenFormat(isDeterministe(Automate));

            cout << "\n-------------------------- Automate " << fichier << " Deterministe\n";
            AutomateDeterministe = Determiniser(Automate);

            AutomateDeterministe.Afficher("AFD");

            cout << "\n\nComplet : " << BooleenFormat(isComplet(AutomateDeterministe));

            cout << "\n-------------------------- Automate " << fichier << " Deterministe Complet\n";
            AutomateComplet = Completer(AutomateDeterministe);

            AutomateComplet.Afficher("AFDC");

            cout << "\n-------------------------- Automate " << fichier << " Minimal (partitions)\n";
            AutomateMinimal = Minimiser(AutomateComplet);
            cout << "\n-------------------------- Automate " << fichier << " Minimal\n";
            // AutomateMinimal = SupprimerEtatsIdentiques(AutomateMinimal);
            AutomateMinimal.Afficher("AFDCM");
            cout << "\n\n";
            AutomateMinimal.AfficherPartitions(0);

            cout << "\n-------------------------- Reconnaissance de mots (automate " << fichier << ")\n";
            do
            {
                do
                {
                    cout << "\nReconnaissance de mots par l'automate :\n";
                    cout << "1. Automate Deterministe (AFD)\n";
                    cout << "2. Automate Deterministe Complet (AFDC)\n";
                    cout << "3. Automate Minimal (AFDCM)\n";
                    cout << "\nEntrez le numero correspondant : ";
                    cin >> ChoixAutomate;
                } while(ChoixAutomate < 1 || ChoixAutomate > 3);

                do
                {
                    switch(ChoixAutomate)
                    {
                        case 1:
                            cout << "\n----------- Reconnaissance de mots par AFD " << fichier << " \n";
                            break;
                        case 2:
                            cout << "\n----------- Reconnaissance de mots par AFDC " << fichier << " \n";
                            break;
                        case 3:
                            cout << "\n----------- Reconnaissance de mots par AFDCM " << fichier << " \n";
                            break;
                    }
                    cout << "\nSaisissez le mot (mot vide : . 'point') : ";
                    cin >> mot;

                    switch(ChoixAutomate)
                    {
                        case 1:
                            cout << "\nMot '" << mot << "' reconnu par AFD " << fichier << " : " << BooleenFormat(AutomateDeterministe.LectureMot(mot)) << endl;
                            break;
                        case 2:
                            cout << "\nMot '" << mot << "' reconnu par AFDC " << fichier << " : " << BooleenFormat(AutomateComplet.LectureMot(mot)) << endl;
                            break;
                        case 3:
                            cout << "\nMot '" << mot << "' reconnu par AFDCM " << fichier << " : " << BooleenFormat(AutomateMinimal.LectureMot(mot)) << endl;
                            break;
                    }

                    cout << "\nVoulez-vous saisir un autre mot ? (1. oui / 2. non) : ";
                    cin >> recommencer;
                } while(recommencer != 2);

                cout << "\nVoulez-vous tester la reconnaissance avec un autre automate ? (1. oui / 2. non) : ";
                cin >> reponse;
            } while(reponse != 2);
        }
    }
    return 0;
}
