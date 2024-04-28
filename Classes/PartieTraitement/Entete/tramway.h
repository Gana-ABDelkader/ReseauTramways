#ifndef TRAMWAY_H_INCLUDED
#define TRAMWAY_H_INCLUDED

#include <iostream>
class Ligne;
class Arret;
class ArretCS;
const double RAFRAICHISSEMENT=1;

class Tramway{
    friend class Ligne;
public:
    Tramway(); //Ensemble
    /** Méthode qui charge un tramway depuis le flux d'entrée input */
    void chargerTramway(std::istream& input, Ligne* ligne); //Hugo
    /** Méthode qui permet de renvoyé la ligne sur laquelle le tram circule */
    Ligne* get_Ligne()const; //Gana
    /** Méthode qui renvoie la vitesse max d'un tram */
    double get_VMax()const; //Gana
    /** Méthode qui renvoie si le tram est à l'arrêt ou non */
    bool get_estArreter()const; //Gana
    /** Méthode qui renvoie la distance minimale au prochain tram */
    double get_distMinProcTram()const; //Gana
    /** Méthode qui renvoie si le tram est à l'aller ou au retour */
    bool get_direction()const; //Gana
    /** Méthode qui renvoie le temps au prochain arret 0 si il est à l'arret */
    double get_tempsProchainArret()const; //Gana
    /** Méthode qui renvoie le temps passer à l'arret, 0 si il est en marche */
    double get_tempPasserArret()const; //Gana
    /** Méthode qui renvoie la composante en x de la position du tramway */
    int get_x()const; //Gana
    /** Méthode qui renvoie la composante en y de la position du tramway */
    int get_y()const; //Gana
    /** Méthode qui renvoie le prochain arrêt */
    Arret* get_prochainArret() const; //Vivien
    /** Renvoie la coordonnée x de l'arrêt du tram */
    int get_xArretTram() const; //Vivien
    /** Renvoie la coordonnée y de l'arrêt du tram */
    int get_yArretTram() const; //Vivien
    /** Renvoie l'indexe */
    int get_Idx() const; //Hugo
    /** Méthode qui renvoie l'adresse de larrêt du tram */
    ArretCS* get_adresseArret() const; //Vivien
    /** Méthode qui met le tram à l'arret */
    void mettreTramArret(); //Hugo
    /** calcul la distance entre le tram et le prochain arret*/
    double calculTempsProchainArret()const; //Gana
    /** mise a jour de donnees quand le tram part de l'arret */
    void TramPartDeArret(); //Gana
    /** Mise à jour des données quand le tram avance entre deux arrêt */
    void Avance(); //Pascaline
    /** Calcul le coeff de la voie par rapport à la distance réelle */
    double coefDeLaVoie() const; //Vivien
    /** Méthode qui renvoie la distance entre un tram et son prochain */
    double distTramProc(const Tramway &tProchain) const; //Vivien
    /** Méthode qui s'occupe de traiter les diffrents cas des trams */
    void traitementTram(); //Ensemble
    /** operator == */
    bool operator==(const Tramway& tram); //Pascaline
    /** operator != */
    bool operator!=(const Tramway& tram); //Pascaline
    /** affectation */
    Tramway* operator=(Tramway* t); //Pascaline
private:
    Ligne* d_ligne; // Nom correspondant à la ligne (ensemble des arrêts et tramways)
    double d_vMax; // Vitesse maximum du tram
    bool d_EstArreter; // A l'arret
    double d_DistMinProcTram; //Distance minimale avec le prochain tram
    bool d_direction; // Sens du tram
    double d_tempsPourArret; //Temps pour arriver au prochain Arret
    double d_tempsPasserArret; //Temps restant devant etre passer à l'arret
    int d_x,d_y; //Coordonnées du tram
    Arret* d_prochainArret; //Pointeur sur le prochain Arret
    int d_idxTemp;
};

//Calcul une distance
double distance(double,double,double,double); //Vivien


#endif // TRAMWAY_H_INCLUDED
