#ifndef LISTETRAM_H_INCLUDED
#define LISTETRAM_H_INCLUDED

#include "tramway.h"
class Ligne;

class TramCS {
public:
     TramCS() : d_suiv{nullptr}{}
     Tramway d_tram;
     TramCS *d_suiv;
     TramCS *d_prec;
};


class LigneTram {
    friend class Tramway;
    friend class AffichageReseau;
    friend class Ligne;
public:
    LigneTram(); 
    ~LigneTram(); 
    /** Méthode qui charger la liste de tram des fichier (appelle une méthode de tram) */
    void chargerListeTram(Ligne* ligne); 
    /** Méthode qui permet de rajouter un tramway à l'indice idx */
    void ajouterTram(int idx, const Tramway& Tram); 
    /** Méthode qui supprime le tram à l'indice idx */
    void supprimerTram(int idx); 
    /** Méthode qui trouve un tram */
    TramCS* trouveTram(const Tramway& tram)const; 
    /** Méthode qui permet de tariter toute les trams de la liste */
    void TraitementListeTram(); 
private:
    TramCS *d_tete;
};

#endif // LISTETRAM_H_INCLUDED
