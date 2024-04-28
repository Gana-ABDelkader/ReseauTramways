#include "../Entete/Arret.h"
#include <fstream>

Arret::Arret():
    d_x{0},
    d_y{0}
{}

int Arret::get_x() const
{
    return d_x;
}

int Arret::get_y() const
{
    return d_y;
}

std::string Arret::get_nom()const
{
    return d_nom;
}

int Arret::get_dureeMin()const
{
    return d_dureeMin;
}

int Arret::get_distProcArret() const{
    return d_distProcArret;
}

void Arret::chargerArret(std::ifstream& fin){

    fin>>d_nom>>d_dureeMin>>d_x>>d_y>>d_distProcArret;
}

bool Arret::operator==(const Arret& arret) const{
    return d_x == arret.d_x && d_y == arret.d_y && d_nom == arret.d_nom
        && d_dureeMin == arret.d_dureeMin && d_distProcArret == arret.d_distProcArret;
}

bool Arret::operator!=(const Arret& arret) const{
    return !(*this == arret);
}
