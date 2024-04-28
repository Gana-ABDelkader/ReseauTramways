#include "../Entete/listechaine.h"
#include <fstream>

Ligne::Ligne():
    d_tete{nullptr},
    d_lTram{},
    d_nom{"Ligne 1"}
{
    chargerLigne();
    d_lTram.chargerListeTram(this);
    lierArretTram();
}

Ligne::~Ligne()
{
    while (d_tete != nullptr)
    {
        ArretCS* temp = d_tete;
        d_tete = d_tete->d_suiv;
        delete temp;
    }
}

void Ligne::chargerLigne(){
    std::ifstream fin("../ReseauxDeTram/Arret.txt");
    if(!fin)
        return;
    int nbarret;
    fin>>nbarret;

    d_tete=new ArretCS ;
    d_tete->d_arret.chargerArret(fin);
    d_tete->d_prec=nullptr;

    ArretCS* t=d_tete;
    for(int i=1;i<nbarret;i++){
        ArretCS* temp=new ArretCS;
        temp->d_arret.chargerArret(fin);
        temp->d_prec=t;
        t->d_suiv=temp;
        temp->d_suiv=nullptr;
        t=temp;
    }
    fin.close();
}

void Ligne::lierArretTram() const{
    ArretCS *c1=d_tete;
    TramCS  *c2=d_lTram.d_tete;

    while(c1->d_suiv != 0){
        c1=c1->d_suiv;
    }
    while(c2){
        c2->d_tram.d_x=c1->d_arret.get_x();
        c2->d_tram.d_y=c1->d_arret.get_y();
        c2->d_tram.d_prochainArret=passeArretSuivant(&c1->d_arret,c2->d_tram.d_direction);

        c2->d_tram.d_EstArreter=0;
        c2->d_tram.d_tempsPourArret=c2->d_tram.calculTempsProchainArret();
        c2->d_tram.d_tempsPasserArret=0;
        c2=c2->d_suiv;
        c1=c1->d_prec;
    }
}

void Ligne::insererArret(Arret* arr,int idx){
    ArretCS* n=new ArretCS;
    n->d_arret= *arr;
    n->d_suiv=nullptr;
    n->d_prec=nullptr;

    if(d_tete==nullptr||idx==0){
        d_tete=n;
        return;
    }

    ArretCS* crt=d_tete;
    ArretCS* pr=nullptr;

    for (int i=0;i<idx&&crt!=nullptr;i++){
        pr = crt;
        crt = crt->d_suiv;
    }

    if(crt==nullptr){
        pr->d_suiv=n;
        n->d_prec=pr;
    }else{
        n->d_suiv=crt;
        n->d_prec=pr;
        crt->d_prec=n;
        if(pr!=nullptr)
            pr->d_suiv=n;
    }
}

void Ligne::supprimerArret(int idx)
{
    if(idx < 0)
        return;

    ArretCS *crt = d_tete;
    if(idx == 0 && d_tete != nullptr)
    {
        d_tete = d_tete->d_suiv;
        d_tete->d_prec = nullptr;
        delete crt;
    }
    else
    {
        for(int i=0; i<idx && crt!= nullptr; i++)
        {
            crt = crt->d_suiv;
        }
        if(crt != nullptr)
        {
            if(crt->d_suiv != nullptr)
                crt->d_suiv->d_prec = crt->d_prec;
            crt->d_prec->d_suiv = crt->d_suiv;
            delete crt;
        }
    }
}

ArretCS* Ligne::trouveArret(const Arret& arr) const{
    if(d_tete == nullptr){
        return nullptr;
    }
    else{
        ArretCS *cur=d_tete;
        while( cur != nullptr && cur->d_arret != arr){
            cur=cur->d_suiv;
        }
        return cur;
    }
}


Arret* Ligne::passeArretSuivant(const Arret* arr, bool& direction) const{
    ArretCS *monarret=trouveArret(*arr);
    if( monarret != nullptr ){
        if((!direction &&monarret->d_prec == nullptr) || (direction && monarret->d_suiv == nullptr))
        {//on est au bout de la liste et on doit changer de direction
            direction=!direction;
        }
        if(direction) return &monarret->d_suiv->d_arret;
        else return &monarret->d_prec->d_arret;
    }else{
        return nullptr;
    }
}

std::string Ligne::get_nom() const
{
    return d_nom;
}

LigneTram Ligne::get_listeTram()const
{
    return d_lTram;
}
