#ifndef ARRET_H_INCLUDED
#define ARRET_H_INCLUDED

#include <string>

class Arret{
public:
    Arret(); //Pascaline
    /** Méthode qui renvoie la composante x de l'arret */
    int get_x()const; //Hugo
    /** Méthode qui renvoie la composante y de l'arret */
    int get_y()const; //Hugo
    /** Méthode qui renvoie le nom de l'arret */
    std::string get_nom()const; //Hugo
    /** Méthode qui renvoie la durée minimum à l'arret */
    int get_dureeMin()const; //Hugo
    /** Méthode qui renvoie la distance au prochaine arret (0 pour le dernier de la ligne) */
    int get_distProcArret() const; //Hugo
    /** Méthode qui permet de charger un arrêt depuis un fichier */
    void chargerArret(std::ifstream& fin); //Pascaline
    /** operator == */
    bool operator==(const Arret& arret) const; //Gana
    /** operator != */
    bool operator!=(const Arret& arret) const; //Gana

private:
    int d_x,d_y;
    std::string d_nom;
    int d_dureeMin;
    int d_distProcArret;
};

#endif // ARRET_H_INCLUDED
