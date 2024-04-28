#ifndef LISTECHAINE_H_INCLUDED
#define LISTECHAINE_H_INCLUDED

#include "Arret.h"
#include "listetram.h"
#include <string>


class ArretCS {
public:
    ArretCS() : d_arret{}, d_suiv{nullptr},d_prec{nullptr} {}
    Arret d_arret;
    ArretCS *d_suiv;
    ArretCS *d_prec;
};


class Ligne {
    friend class AffichageReseau;
    friend class Tramway;
    friend class LigneTram;
public:
    Ligne(); //Ensemble
    ~Ligne(); //Hugo
    /** Charge la ligne enregistrer dans les fichiers (appelle plusieurs méthode de chargement */
    void chargerLigne(); //Pascaline
    /** lier arret tram */
    void lierArretTram()const; //Ensemble
    /** Insère l'Arret arr à l'indice idx */
    void insererArret(Arret* arr,int idx); //Pascaline
    /** Supprime l'arrêt à l'indice idx */
    void supprimerArret(int idx); //Vivien
    /** Renvoie un pointeur sur l'arret arr is trouve, nullptr sinon */
    ArretCS* trouveArret(const Arret& arr)const; //Gana
    /** Méthode qui permet a un tram de passer a l'arret suivant , sera utilise avec un tram */
    Arret* passeArretSuivant(const Arret *arr, bool& direction)const; //Gana
    /** Méthode qui permet de renvoyé le nom */
    std::string get_nom() const; //Hugo
    /** Méthode qui renvoie la liste des trams sur la Ligne */
    LigneTram get_listeTram()const; //Hugo
private:
     ArretCS *d_tete;
     LigneTram d_lTram;
     std::string d_nom;
};
#endif // LISTECHAINE_H_INCLUDED
