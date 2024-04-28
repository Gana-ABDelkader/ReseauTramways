#include "affichagereseau.h"
#include<Qpainter>
#include<QPaintEvent>
#include<qapplication.h>
#include<QElapsedTimer>

const int COTEARRET=10;
const int COTETRAM=20;
const int AJOUTNOMX=25;
const int AJOUTNOMY=8;


AffichageReseau::AffichageReseau(int temps,QWidget *parent)
    : QWidget{parent},d_ligne{},d_time{temps}
{
    creeInterfaceTram();
}

AffichageReseau::~AffichageReseau()
{}

void AffichageReseau::bouclePrincpale(){
    if (d_chronoBoucle.elapsed() >= d_time * 60000)//si on a depasse le temps totale
    {
        d_timer.stop(); //on arrete et on quit l'application
        qApp->quit();
    }
    else {
        d_ligne.d_lTram.TraitementListeTram();//traitement des trams
        update(); //reappelle le paintEvent
    }
}

void AffichageReseau::creeInterfaceTram(){
    setWindowTitle("Reseaux Tramway");
    resize(1200,600);
}

void AffichageReseau::paintEvent(QPaintEvent*){
    QPainter painter{this};
    afficherLigneEntiere(painter);
    afficherTousTram(painter);
    afficherTousArret(painter);
}

void AffichageReseau::afficherArret(QPainter& painter,Arret arret){
    //affiche arret
    painter.setBrush(Qt::blue);
    painter.drawEllipse(QRectF(arret.get_x(),arret.get_y(),COTEARRET,COTEARRET));

    //affiche son nom
    painter.drawText(arret.get_x()+AJOUTNOMX,arret.get_y()+AJOUTNOMY,QString::fromStdString(arret.get_nom()));
}

void AffichageReseau::afficherTram(QPainter& painter, Tramway tram){
    //le tram
    painter.setBrush(Qt::red);
    painter.drawRect(QRectF(tram.get_x(),tram.get_y(),COTETRAM,COTETRAM));

    //change la police
    QFont font = painter.font();
    font.setBold(true);
    painter.setFont(font);

    //affiche direction et indice du tram
    QPointF centre(tram.get_x() + COTETRAM / 2, tram.get_y() + COTETRAM / 2);
    painter.drawText(centre.x()-(COTETRAM/4) ,tram.get_y()+COTETRAM,QString::number(tram.get_Idx()));

    if(tram.get_direction()) painter.drawText(centre.x()-(COTETRAM/4),tram.get_y(),">");
    else painter.drawText(centre.x()-(COTETRAM/4),tram.get_y(),"<");
}

void AffichageReseau::afficherLigne(QPainter& painter, Arret arret1,Arret arret2){
    painter.setPen(Qt::black);

    QPointF centre1(arret1.get_x() + COTEARRET / 2,arret1.get_y() + COTEARRET / 2);
    QPointF centre2(arret2.get_x() + COTEARRET / 2,arret2.get_y() + COTEARRET / 2);

    painter.drawLine(QLineF(centre1.x(),centre1.y(),centre2.x(),centre2.y()));
}

void AffichageReseau::afficherTousArret(QPainter& painter){
    ArretCS *cur=d_ligne.d_tete;
    while(cur){
        afficherArret(painter,cur->d_arret);
        cur=cur->d_suiv;
    }
}

void AffichageReseau::afficherTousTram(QPainter& painter){
    TramCS *cur=d_ligne.d_lTram.d_tete;
    while(cur){
        afficherTram(painter,cur->d_tram);
        cur=cur->d_suiv;
    }
}

void AffichageReseau::afficherLigneEntiere(QPainter &painter){
    ArretCS *cur=d_ligne.d_tete;
    while(cur->d_suiv != nullptr){
        afficherLigne(painter,cur->d_arret,cur->d_suiv->d_arret);
        cur=cur->d_suiv;
    }
}
