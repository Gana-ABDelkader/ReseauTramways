#include "../Entete/tramway.h"
#include <string>
#include <cmath>
#include "../Entete/Arret.h"
#include "../Entete/listechaine.h"

Tramway::Tramway():
    d_ligne{nullptr},
    d_vMax{15},
    d_EstArreter{true},
    d_DistMinProcTram{0},
    d_direction{true},
    d_tempsPourArret{0},
    d_tempsPasserArret{0},
    d_x{0},d_y{0},
    d_prochainArret{nullptr},
    d_idxTemp{0}
{}

void Tramway::chargerTramway(std::istream& input, Ligne* ligne)
{
    std::string temp;
    int idx;
    input>>temp>>d_vMax>>temp>>d_EstArreter>>temp>>d_DistMinProcTram>>temp
        >>d_direction>>temp>>d_tempsPourArret>>temp>>d_tempsPasserArret>>temp>>idx;

    d_ligne=ligne;
    d_idxTemp=idx;
}

Ligne* Tramway::get_Ligne()const
{
    return d_ligne;
}

double Tramway::get_VMax()const
{
    return d_vMax;
}

bool Tramway::get_estArreter()const
{
    return d_EstArreter;
}

double Tramway::get_distMinProcTram()const
{
    return d_DistMinProcTram;
}

bool Tramway::get_direction()const{
    return d_direction;
}

double Tramway::get_tempsProchainArret()const{
    return d_tempsPourArret;
}

double Tramway::get_tempPasserArret()const{
    return d_tempsPasserArret;
}

int Tramway::get_x()const{
    return d_x;
}

int Tramway::get_y()const{
    return d_y;
}

Arret* Tramway::get_prochainArret() const
{
    return d_prochainArret;
}

int Tramway::get_xArretTram() const
{
    return d_prochainArret->get_x();
}

int Tramway::get_yArretTram() const
{
    return d_prochainArret->get_y();
}
int Tramway::get_Idx() const{
    return d_idxTemp;
}
ArretCS *Tramway::get_adresseArret() const
{
    return d_ligne->trouveArret(*d_prochainArret);
}

void Tramway::mettreTramArret()
{
    d_EstArreter=true;
    d_x=d_prochainArret->get_x();
    d_y=d_prochainArret->get_y();
    d_tempsPasserArret=d_prochainArret->get_dureeMin()+d_tempsPourArret;
    d_tempsPourArret=0;
}

double Tramway::calculTempsProchainArret() const{
    return static_cast<double>(d_prochainArret->get_distProcArret())/d_vMax; //utilisation de la formule v=d/t
}

void Tramway::TramPartDeArret(){
    d_EstArreter=false;
    d_tempsPourArret=calculTempsProchainArret()+d_tempsPasserArret; //si il a passe un temps a l'arret plus que le temps necessaire
    d_prochainArret=d_ligne->passeArretSuivant(d_prochainArret,d_direction);//mise a jour de l'arret prochain et la direction
    d_tempsPasserArret=0;
}

void Tramway::Avance()
{
    Tramway* TProc;
    TramCS* tramTrouve = d_ligne->d_lTram.trouveTram(*this);

    if(tramTrouve == d_ligne->d_lTram.d_tete){
        TramCS* cur = d_ligne->d_lTram.d_tete;
        while (cur->d_suiv != nullptr) {
            cur = cur->d_suiv;
        }
        TProc = &cur->d_tram;
    }
    else {
        TProc = &tramTrouve->d_prec->d_tram;
    }

    if(distTramProc(*TProc)>d_DistMinProcTram){
        d_tempsPourArret-=RAFRAICHISSEMENT;
        if(d_tempsPourArret>1)
        {
            //Calcul des nouveaux coordonnées :
            int dx,dy;
            int x,y;
            x=d_prochainArret->get_x()-get_x();
            y=d_prochainArret->get_y()-get_y();
            dx=x/(d_tempsPourArret);
            dy=y/(d_tempsPourArret);
            d_x+=dx;
            d_y+=dy;
        }
        else
        {
            d_x=d_prochainArret->get_x();
            d_y=d_prochainArret->get_y();
        }
    }
    else if(TProc->get_direction() != get_direction())
    {
        d_x=d_prochainArret->get_x();
        d_y=d_prochainArret->get_y();
    }
}

double Tramway::coefDeLaVoie() const
{
    int distanceVoieEnKm = get_prochainArret()->get_distProcArret(); //la distance en km
    ArretCS *crt = get_adresseArret();
    double distanceVoieEcran;

    if(crt->d_suiv != nullptr)
        distanceVoieEcran = distance(get_prochainArret()->get_x(),get_prochainArret()->get_y(),
                crt->d_suiv->d_arret.get_x(),crt->d_suiv->d_arret.get_y()); //la distance à l'écran de la voie ou se trouve le tram1
    else
        distanceVoieEcran = distance(get_prochainArret()->get_x(),get_prochainArret()->get_y(),
                get_Ligne()->d_tete->d_arret.get_x(),get_Ligne()->d_tete->d_arret.get_y()); //la distance à l'écran de la voie ou se trouve le tram1
    return distanceVoieEnKm/distanceVoieEcran;
}

double distance(double x1,double y1,double x2,double y2)
{
    return std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));
}

double Tramway::distTramProc(const Tramway &tProchain) const
{
    double res = 0.0;
    double coef1 = coefDeLaVoie();

    if(get_prochainArret() != tProchain.get_prochainArret() || get_direction() != tProchain.get_direction())
    {
        double coef2 = tProchain.coefDeLaVoie();

        res = coef1 * distance(get_x(),get_y(),get_xArretTram(),get_yArretTram());
        res += coef2 * distance(get_xArretTram(),get_yArretTram(),tProchain.get_x(),tProchain.get_y());
    }
    else
        res = coef1*distance(get_x(),get_y(),tProchain.get_x(),tProchain.get_y());
    return res;
}

void Tramway::traitementTram()
{
    if(d_tempsPasserArret > 0){
        //decrementation du temps passe a l'arret
        d_tempsPasserArret-=RAFRAICHISSEMENT;
    }
    else if(d_tempsPourArret < 0){
        //mise a jour pour pouvoir arriver a l'arret
        mettreTramArret();
    }
    else if(d_tempsPourArret == 0){
        //mise a jour pour pouvoir partir de l'arret
        TramPartDeArret();
    }
    else Avance();
}

bool Tramway::operator==(const Tramway &t)
{
    if(this==&t)
        return true;
    return false;
}

bool Tramway::operator!=(const Tramway &tram)
{
    return !(*this==tram);
}

Tramway* Tramway::operator=(Tramway* t){

    return t;
}
