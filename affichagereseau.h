#ifndef AFFICHAGERESEAU_H
#define AFFICHAGERESEAU_H

#include<QElapsedTimer>
#include <QWidget>
#include <Qpainter>
#include<QPaintEvent>
#include<QTimer>
#include <Classes/PartieTraitement/Entete/listechaine.h>
#include <Classes/PartieTraitement/Entete/Arret.h>
#include <Classes/PartieTraitement/Entete/tramway.h>

class AffichageReseau : public QWidget
{
    Q_OBJECT
    friend int main(int argc, char *argv[]);
public:
    const int SLEEP=1000;
    AffichageReseau(int temps,QWidget *parent = nullptr); 
    ~AffichageReseau();
public slots:
    void bouclePrincpale(); 
private:
    Ligne d_ligne;
    QTimer d_timer;
    QElapsedTimer d_chronoBoucle;
    int d_time;
    /** Méthode pour créer l'interface de la fenêtre graphique */
    void creeInterfaceTram();
    /** Methode pour gerer l'affichage , paint Event */
    void paintEvent(QPaintEvent*); 
    /** Méthode pour afficher un arret */
    void afficherArret(QPainter &painter, Arret arret); 
    /** Méthode pour afficher un tram */
    void afficherTram(QPainter &painter, Tramway tram ); 
    /** Méthode pour afficher une ligne */
    void afficherLigne(QPainter &painter, Arret arret1 , Arret arret2); 
    /** Méthode pour afficher tous les arrets */
    void afficherTousArret(QPainter &painter); 
    /** Méthode pour afficher tous les trams */
    void afficherTousTram(QPainter &painter); 
    /** Méthode pour afficher la ligne entiere */
    void afficherLigneEntiere(QPainter &painter); 
};
#endif // AFFICHAGERESEAU_H
