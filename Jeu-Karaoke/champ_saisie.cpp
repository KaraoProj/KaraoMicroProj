#include "champ_saisie.h"
#include <iostream>

using namespace std;

Champ_Saisie::Champ_Saisie(QWidget *parent/*, Panel_Texte* _parent*/) : QLineEdit(parent){

    //zone_texte_parent=_parent;

    QObject::connect(this,SIGNAL(returnPressed()), this, SLOT(validationMot()));

}

Champ_Saisie::~Champ_Saisie(){
}

void Champ_Saisie::validationMot(){

    cout << "Position curseur: " << this->cursorPosition() << endl;
    this->selectAll();
    cout << "Position curseur (après selection): " << this->cursorPosition() << endl;
    cout << "[Le mot tapé est: " << selectedText().toStdString() << "]" << endl;

    traiterSaisie(selectedText());
}

void Champ_Saisie::traiterSaisie(const QString & texte_saisi){


     /////////////////////////////////////
    // ICI faire la phase de traitement//
   /////////////////////////////////////


    emit ecrireMot(texte_saisi);
    //this->zone_texte_parent->ecrire_texte(texte_saisi);
}

