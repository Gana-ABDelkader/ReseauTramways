#include "affichagereseau.h"
#include <QApplication>
#include <QInputDialog>
#include <QWidget>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a{argc, argv};
    QWidget dialogTemps;
    int temps;
    bool choix=true;
    while(choix)
    {
        bool ok;
        temps=QInputDialog::getInt(&dialogTemps,"Entrée du temps","Entrez le temps du programme en minutes :",0, 0, 9999, 1, &ok);
        if(temps == 0 || !ok)
        {
            QMessageBox msg{QMessageBox::Critical, "Confirmation","Vouliez-vous vraiment mettre 0 en temps, \n cela ne vous permettra pas de visualiser correctement le réseau"
            ,QMessageBox::Yes|QMessageBox::No};
            if (msg.exec() == QMessageBox::Yes)
            {
                choix=false;
            }
        }
        else
        {
            choix=false;
        }
    }
    AffichageReseau w{temps};
    //Connexion du signal de l'objet Qtimer avec la methode de rappel
    QObject::connect(&w.d_timer, &QTimer::timeout, &w ,&AffichageReseau::bouclePrincpale);
    w.d_chronoBoucle.start();
    w.d_timer.start(w.SLEEP);
    w.show();
    return a.exec();
}
