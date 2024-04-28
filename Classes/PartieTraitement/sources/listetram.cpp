#include "../Entete/listetram.h"
#include "Classes/PartieTraitement/Entete/listechaine.h"
#include <fstream>

LigneTram::LigneTram():
    d_tete{nullptr}
{}

LigneTram::~LigneTram()
{
    while (d_tete != nullptr)
    {
        TramCS* temp = d_tete;
        d_tete = d_tete->d_suiv;
        delete temp;
    }
}

void LigneTram::chargerListeTram(Ligne* ligne)
{
    std::ifstream input("../ReseauxDeTram/Tramway.txt");
    if (!input) {
        return;
    }

    TramCS* tete = nullptr;
    TramCS* dernier = nullptr;

    int cpt;
    input>>cpt;

    ArretCS *cur=ligne->d_tete;
    while(cur->d_suiv != 0){
        cur=cur->d_suiv;
    }

    while (cpt>0)
    {
        cpt--;
        TramCS* nouveauTram = new TramCS;
        (nouveauTram->d_tram).chargerTramway(input, ligne);
        nouveauTram->d_suiv = nullptr;
        if (tete == nullptr) {
            tete = nouveauTram;
            dernier = nouveauTram;
        } else {
            dernier->d_suiv = nouveauTram;
            nouveauTram->d_prec=dernier;
            dernier = dernier->d_suiv;
        }
    }
    input.close();
    d_tete = tete;
}

void LigneTram::ajouterTram(int idx, const Tramway& Tram)
{
    auto ajout = new TramCS;
    ajout->d_tram = Tram;
    ajout->d_suiv = nullptr;
    ajout->d_prec = nullptr;

    if (d_tete == nullptr) {
        // Si la liste est vide alors on ajoute en tete
        d_tete = ajout;
        return;
    }

    TramCS *c = d_tete;
    TramCS *prec = nullptr;

    // Parcours de la liste pour arriver a notre indice idx
    for (int i = 0; i < idx && c != nullptr; i++)
    {
        prec = c;
        c = c->d_suiv;
    }

    if (c == nullptr)
    {
        // Si c est nullptr, alors nous sommes à la fin de la liste
        prec->d_suiv = ajout;
        ajout->d_prec = prec;
    }
    else
    {
        // Ajouter le nouveau tram à l'indice spécifié ou au début de la liste
        if (prec != nullptr)
        {
            prec->d_suiv = ajout;
            ajout->d_prec = prec;
        }
        ajout->d_suiv = c;
        c->d_prec = ajout;
        if (idx == 0)
            d_tete = ajout;
    }
}

void LigneTram::supprimerTram(int idx){
    if(d_tete == nullptr){ //liste vide
        return;
    }
    if(idx == 0){ //suppresion au debut de la liste
        TramCS *cur=d_tete;
        d_tete=cur->d_suiv;
        if(d_tete != nullptr){
            d_tete->d_prec=nullptr;
        }
        delete cur;
        return;
    }
    //la suppression est au milieu ou la fin
    TramCS *cur=d_tete;
    int cpt=0;
    while(cur != nullptr && cpt<idx){//parcours pour arriver au tram a supprimer
        cur=cur->d_suiv;
        cpt++;
    }
    if(cpt != idx || cur == nullptr){ //si l'indice n'existe pas(atteindre fin de la liste)
        return;
    }
    cur->d_prec->d_suiv=cur->d_suiv;
    if(cur->d_suiv != nullptr){
        cur->d_suiv->d_prec=cur->d_prec;
    }
    delete cur;
}


TramCS* LigneTram::trouveTram(const Tramway& tram) const{
    if(d_tete == nullptr){
        return nullptr;
    }
    else{
        TramCS *cur=d_tete;
        while( cur != nullptr && cur->d_tram != tram){
            cur=cur->d_suiv;
        }
        return cur;
    }
}

void LigneTram::TraitementListeTram(){
    TramCS *cur=d_tete;
    while(cur){
        cur->d_tram.traitementTram();
        cur=cur->d_suiv;
    }
}
