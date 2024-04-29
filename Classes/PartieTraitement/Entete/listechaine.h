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
    Ligne(); 
    ~Ligne(); 
    /** Charge la ligne enregistrer dans les fichiers (appelle plusieurs méthode de chargement */
    void chargerLigne(); 
    /** lier arret tram */
    void lierArretTram()const; 
    /** Insère l'Arret arr à l'indice idx */
    void insererArret(Arret* arr,int idx); 
    /** Supprime l'arrêt à l'indice idx */
    void supprimerArret(int idx); 
    /** Renvoie un pointeur sur l'arret arr is trouve, nullptr sinon */
    ArretCS* trouveArret(const Arret& arr)const; 
    /** Méthode qui permet a un tram de passer a l'arret suivant , sera utilise avec un tram */
    Arret* passeArretSuivant(const Arret *arr, bool& direction)const; 
    /** Méthode qui permet de renvoyé le nom */
    std::string get_nom() const; 
    /** Méthode qui renvoie la liste des trams sur la Ligne */
    LigneTram get_listeTram()const; 
private:
     ArretCS *d_tete;
     LigneTram d_lTram;
     std::string d_nom;
};
#endif // LISTECHAINE_H_INCLUDED
